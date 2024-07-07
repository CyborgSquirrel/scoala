import csv
import dataclasses
import itertools
import pathlib
import subprocess
import tempfile

# TRIALS = 1000
TRIALS = 10
# TRIALS = 1

DATA_DIR = "./data"


@dataclasses.dataclass
class Test:
    p_r: int
    p_w: int
    runner: str


@dataclasses.dataclass
class Result:
    test: Test
    time: float
    passed_check: bool


def run_cpp(test: Test) -> Result:
    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)
        result_path = tmp_dir / "result.txt"
        time_path = tmp_dir / "time.txt"
        if test.p_r == 0 and test.p_w == 0:
            subprocess.run([
                "./target/sequential",
                DATA_DIR,
                str(result_path),
                str(time_path),
            ])
        else:
            subprocess.run([
                "./target/threaded",
                DATA_DIR,
                str(result_path),
                str(time_path),
                str(test.p_r),
                str(test.p_w),
            ])

        with time_path.open() as f:
            time = float(f.read().strip())

        check_path = pathlib.Path("check") / "result.txt"
        with (
            check_path.open() as check_file,
            result_path.open() as result_file,
        ):
            check_content = check_file.read()
            result_content = result_file.read()

        passed_check = check_content == result_content

        if not passed_check:
            print("Failed the check. Darnit -_-.")
            assert False

        return Result(
            test,
            time,
            passed_check,
        )


runners = dict(
    cpp=run_cpp,
)
ALL_RUNNERS = list(runners.keys())

tests = itertools.chain.from_iterable([
    itertools.product([0], [0], ["cpp"]),
    itertools.product([4], [2, 4, 12], ["cpp"]),
])

tests = [
    Test(*test) for test in tests
]


with open("data.csv", "w") as f:
    fc = csv.writer(f)
    fc.writerow(
          [field.name for field in dataclasses.fields(Test)]
        + ["time"]
    )

    for test in tests:
        print(test)

        runner = runners[test.runner]

        for trial_index in range(TRIALS):
            result = runner(test)
            fc.writerow(
                dataclasses.astuple(result.test) + (result.time,)
            )
            f.flush()
