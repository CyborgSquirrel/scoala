import subprocess
import itertools


for p, d1, d2 in itertools.product(
    [1, 2, 4],
    ["is_static", "is_dynamic"],
    ["is_seq", "is_cycle"],
):
    print(p, d1, d2)
    elapseds = []
    subprocess.run(
        [
            "g++",
            "-O3",
            f"-DP={p}",
            f"-D{d1}",
            f"-D{d2}",
            "code.cpp",
            "-o", "code",
        ]
    )
    for _ in range(10):
        output = subprocess.run(
            ["./code"],
            capture_output=True,
        )
        elapsed = float(output.stdout)
        elapseds.append(elapsed)
    print(sum(elapseds) / len(elapseds))
