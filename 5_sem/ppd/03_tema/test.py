import csv
import dataclasses
import itertools
import os.path
import subprocess
import numpy as np
import tempfile


TRIALS = 10
# TRIALS = 1

MAT_PATH = "./data/mat.dat"
CONV_PATH = "./data/conv.dat"


@dataclasses.dataclass
class Test:
    mat_row_no: int
    mat_col_no: int
    conv_row_no: int
    conv_col_no: int
    p: int
    runner: str


@dataclasses.dataclass
class Result:
    test: Test
    t1: float
    t2: float
    passed_check: bool


def run_mpi(executable_path: str, test: Test) -> Result:
    with tempfile.TemporaryDirectory() as tmpdir:
        result_path = os.path.join(tmpdir, "result.dat")
        t1_path = os.path.join(tmpdir, "t1.txt")
        t2_path = os.path.join(tmpdir, "t2.txt")
        completed = subprocess.run([
            "mpirun", "--oversubscribe", "-n", str(test.p),
            executable_path,
            str(test.mat_row_no),
            str(test.mat_col_no),
            MAT_PATH,
            CONV_PATH,
            result_path,
            t1_path,
            t2_path,
        ])

        with open(t1_path) as f:
            t1 = float(f.read().strip())
        with open(t2_path) as f:
            t2 = float(f.read().strip())

        check_result_path = os.path.join(
            "check", "mpi",
            f"{test.mat_row_no}-{test.mat_col_no}.dat",
        )

        result = np.fromfile(result_path)
        check_result = np.fromfile(check_result_path)
        passed_check = np.allclose(result, check_result)

        if not passed_check:
            print("Failed the check. Darnit -_-.")

        return Result(
            test,
            t1,
            t2,
            passed_check,
        )


runners = dict(
    mpi_v1=lambda test: run_mpi("./target/mpi-v1", test),
    mpi_v2=lambda test: run_mpi("./target/mpi-v2", test),
)
ALL_RUNNERS = list(runners.keys())
ALL_RUNNERS = ["mpi_v1", "mpi_v2"]
# ALL_RUNNERS = ["mpi_v1"]
# ALL_RUNNERS = ["mpi_v2"]

tests = itertools.chain.from_iterable([
    # itertools.product([1000], [1000], [3], [3], [4], ALL_RUNNERS),

    # itertools.product([1000], [1000], [3], [3], [5,9,17], ["mpi_v1"]),
    # itertools.product([10000], [10000], [3], [3], [5,9,17], ["mpi_v1"]),

    itertools.product([1000], [1000], [3], [3], [4,8,16], ["mpi_v2"]),
    itertools.product([10000], [10000], [3], [3], [4,8,16], ["mpi_v2"]),
])

tests = [
    Test(*test) for test in tests
]


# results = []
with open("data.csv", "w") as f:
    fc = csv.writer(f)
    fc.writerow(
          [field.name for field in dataclasses.fields(Test)]
        + ["t1", "t2"]
    )

    for test in tests:
        print(test)

        runner = runners[test.runner]

        for trial_index in range(TRIALS):
            result = runner(test)
            fc.writerow(
                dataclasses.astuple(result.test) + (result.t1, result.t2)
            )
            f.flush()
            # results.append(result)
