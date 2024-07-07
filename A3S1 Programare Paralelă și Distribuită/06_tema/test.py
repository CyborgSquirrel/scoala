import asyncio
import csv
import dataclasses
import itertools
import pathlib
import shutil
import subprocess
import tempfile
import time as timelib

# TRIALS = 1000
# TRIALS = 10
TRIALS = 1

CHUNK_SIZE = 20
# CHUNK_SIZE = 500

DATA_DIR = pathlib.Path("data")
PROJECT_PATH = pathlib.Path("code")
CLASS_PATH = PROJECT_PATH / "src" / "build" / "classes" / "java" / "main"

CORRECT_PATH = pathlib.Path("competitors-correct.txt")

# run gravel
subprocess.run(
    ["./gradlew", "build"],
    cwd=str(PROJECT_PATH),
)


@dataclasses.dataclass
class Test:
    runner: str
    p_r: int
    p_w: int
    delta_x: int
    delta_t: float


@dataclasses.dataclass
class Result:
    test: Test
    time: float
    passed_check: bool


port_generator = itertools.count(4096)


async def run_java(test: Test) -> Result:
    port = next(port_generator)
    with tempfile.TemporaryDirectory() as tmp_dir:
    # if True:
        tmp_dir = pathlib.Path(tmp_dir)

        # tmp_dir = pathlib.Path("./tmp")
        # if tmp_dir.exists():
        #     shutil.rmtree(tmp_dir)
        # tmp_dir.mkdir(parents=True)

        competitor_leaderboard_path = tmp_dir / "competitors.txt"
        country_leaderboard_path = tmp_dir / "countries.txt"

        log_path = pathlib.Path(".") / "log.txt"
        with log_path.open("w") as f:
            processes = []

            time_start = timelib.time()
            
            process = await asyncio.create_subprocess_exec(
                "java",
                "-cp", str(CLASS_PATH),
                "server.Main",
                str(test.p_r),
                str(test.p_w),
                str(test.delta_t),
                str(competitor_leaderboard_path),
                str(country_leaderboard_path),
                str(port),
                stdout=f, stderr=f,
            )
            processes.append(process)

            timelib.sleep(0.5)

            for country_i in range(5):
                process = await asyncio.create_subprocess_exec(
                    "java",
                    "-cp", str(CLASS_PATH),
                    "client.Main",
                    str(country_i+1),
                    str(test.delta_x),
                    str(DATA_DIR),
                    str(CHUNK_SIZE),
                    str(port),
                    stdout=f, stderr=f,
                )
                processes.append(process)

            for process in processes:
                await process.wait()

            time_end = timelib.time()
            time_elapsed = time_end - time_start

            with competitor_leaderboard_path.open() as f:
                competitors_content = f.read()
            with CORRECT_PATH.open() as f:
                competitors_content_correct = f.read()

        passed_check = (competitors_content == competitors_content_correct)

        if not passed_check:
            print("Failed the check. Darnit -_-.")
            assert False

        return Result(
            test,
            time_elapsed,
            passed_check,
        )


runners = dict(
    java=run_java,
)
ALL_RUNNERS = list(runners.keys())

tests = itertools.chain.from_iterable(
    [[("java", 2, 4, 1, 0.001)]]

    # itertools.product(
    #     ["java"],
    #     [p_r], [p_w],
    #     [1, 2],
    #     [0.001, 0.002, 0.004],
    # )
    # for p_r, p_w
    # in [
    #     (4, 4),
    #     (2, 2),
    #     (4, 2),
    #     (4, 8),
    # ]
)

tests = [
    Test(*test) for test in tests
]


async def main():
    with open("data.csv", "w") as f:
        fc = csv.writer(f)
        fc.writerow(
              [field.name for field in dataclasses.fields(Test)]
            + ["time"]
        )

        semaphore = asyncio.Semaphore(80)
        async with asyncio.TaskGroup() as group:
            for test in tests:
                print(test)

                runner = runners[test.runner]

                async def run_trial():
                    result = await runner(test)
                    fc.writerow(
                        dataclasses.astuple(result.test) + (result.time,)
                    )
                    f.flush()
                    semaphore.release()

                for trial_index in range(TRIALS):
                    await semaphore.acquire()
                    group.create_task(run_trial())
                    await asyncio.sleep(1)


if __name__ == "__main__":
    asyncio.run(main())
