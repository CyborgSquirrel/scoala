import itertools
import subprocess
import dataclasses
import time
import csv


TRIALS = 10
# TRIALS = 2

MAT_PATH = "./data/mat.txt"
CONV_PATH = "./data/mat.txt"

ALL_METHODS = ["block", "row", "col"]


@dataclasses.dataclass
class Test:
    mat_row_no: int
    mat_col_no: int
    conv_row_no: int
    conv_col_no: int
    p: int
    method: str
    runner: str


@dataclasses.dataclass
class Result:
    test: Test
    elapsed_average: float


def run_java(test: Test):
    subprocess.run([
        "java", "conv.java",
        str(test.p),
        test.method,
        str(test.mat_row_no),
        str(test.mat_col_no),
        MAT_PATH,
        str(test.conv_row_no),
        str(test.conv_col_no),
        CONV_PATH,
    ])


def run_cpp_dynamic(test: Test):
    subprocess.run([
        "./target/conv-dynamic",
        str(test.p),
        test.method,
        str(test.mat_row_no),
        str(test.mat_col_no),
        MAT_PATH,
        str(test.conv_row_no),
        str(test.conv_col_no),
        CONV_PATH,
    ])

    
def run_cpp_static(test: Test):
    subprocess.run([
        "./target/conv-static",
        str(test.p),
        test.method,
        str(test.mat_row_no),
        str(test.mat_col_no),
        MAT_PATH,
        str(test.conv_row_no),
        str(test.conv_col_no),
        CONV_PATH,
    ])


runners = dict(
    java=run_java,
    cpp_static=run_cpp_static,
    cpp_dynamic=run_cpp_dynamic,
)
ALL_RUNNERS = list(runners.keys())
# ALL_RUNNERS = ["cpp_static"]

# 1) N=M=10 si n=m=3; p=4;
# 2) N=M=1000 si n=m=5; p=2,4,8,16
# 3) N=10 M=10000 si n=m=5; p=2,4,8,16
# 4) N=10000 M=10 si n=m=5; p=2,4,8,16
tests = itertools.chain.from_iterable([
    # itertools.product([100], [100], [5], [5], [4], ALL_METHODS, ALL_RUNNERS),
    # itertools.product([100], [100], [5], [5], [4], ["block"], ALL_RUNNERS),

    itertools.product([10], [10], [3], [3], [4], ALL_METHODS, ALL_RUNNERS),
    itertools.product([1000], [1000], [5], [5], [2, 4, 8, 16], ALL_METHODS, ALL_RUNNERS),
    itertools.product([10], [10000], [5], [5], [2, 4, 8, 16], ALL_METHODS, ALL_RUNNERS),
    itertools.product([10000], [10], [5], [5], [2, 4, 8, 16], ALL_METHODS, ALL_RUNNERS),
])

tests = [
    Test(*test) for test in tests
]

results = []

for test in tests:
    print(test)

    runner = runners[test.runner]

    elapseds = []
    for trial_index in range(TRIALS):
        start = time.time()
        runner(test)
        stop = time.time()

        elapsed = stop - start
        elapseds.append(elapsed)
    
    elapsed_average = sum(elapseds) / len(elapseds)
    results.append(Result(test, elapsed_average))


with open("data.csv", "w") as f:
    f = csv.writer(f)
    f.writerow(
          [field.name for field in dataclasses.fields(Test)]
        + ["elapsed_average"]
    )
    f.writerows(
        dataclasses.astuple(result.test) + (result.elapsed_average,)
        for result in results
    )
