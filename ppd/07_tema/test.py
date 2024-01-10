import csv
import dataclasses
import itertools
import os.path
import pathlib
import subprocess
import tempfile

import numpy as np

TRIALS = 10
# TRIALS = 2
# TRIALS = 1

MAT_PATH = "./data/mat.dat"
CONV_PATH = "./data/conv.dat"
RESULT_PATH = "./target/result.dat"


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
    elapsed: float
    passed_check: bool


def run_cuda(test: Test) -> Result:
    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)

        elapsed_path = tmp_dir / "elapsed.txt"
        
        completed = subprocess.run([
            # "valgrind", "--leak-check=full", "--",
            # "compute-sanitizer",
            "conv-cu",
            str(test.p),
            str(test.mat_row_no),
            str(test.mat_col_no),
            MAT_PATH,
            CONV_PATH,
            RESULT_PATH,
            str(elapsed_path),
        ])

        with elapsed_path.open() as f:
            elapsed = float(f.read().strip())

        check_result_path = os.path.join(
            "check", "cpp",
            f"{test.mat_row_no}-{test.mat_col_no}.dat",
        )

        result = np.fromfile(RESULT_PATH)
        check_result = np.fromfile(check_result_path)
        passed_check = np.allclose(result, check_result)

        if not passed_check:
            print("Failed the check. Darnit -_-.")

    return Result(
        test,
        elapsed,
        passed_check,
    )


runners = dict(
    cuda=run_cuda,
)
ALL_RUNNERS = list(runners.keys())
ALL_RUNNERS = ["cuda"]

# 1) N=M=10 si n=m=3; p=2 + executie secventiala
# 2) N=M=1000 si n=m=3; p=2,4,8,16 + executie secventiala
# 3) N=10000 M=10000 si n=m=3; p=2,4,8,16 + executie secventiala
tests = itertools.chain.from_iterable([
    # itertools.product([10], [10], [3], [3], [4], ALL_RUNNERS),
    # itertools.product([1000], [1000], [3], [3], [4], ALL_RUNNERS),

    itertools.product([10], [10], [3], [3], [2], ALL_RUNNERS),
    itertools.product([1000], [1000], [3], [3], [2,4,8,16], ALL_RUNNERS),
    itertools.product([10000], [10000], [3], [3], [2,4,8,16], ALL_RUNNERS),
])

tests = [
    Test(*test) for test in tests
]


# results = []
with open("data.csv", "w") as f:
    fc = csv.writer(f)
    fc.writerow(
          [field.name for field in dataclasses.fields(Test)]
        + ["elapsed"]
    )

    for test in tests:
        print(test)

        runner = runners[test.runner]

        for trial_index in range(TRIALS):
            result = runner(test)
            fc.writerow(
                dataclasses.astuple(result.test) + (result.elapsed,)
            )
            f.flush()
