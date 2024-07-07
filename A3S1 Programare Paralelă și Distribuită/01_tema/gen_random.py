import argparse
import numpy as np
import os.path


argparser = argparse.ArgumentParser()
argparser.add_argument("n", type=int)
argparser.add_argument("path")
args = argparser.parse_args()

if os.path.exists(args.path):
    print(f"File at '{args.path}' already exists.")
    exit(1)

matrix = np.random.uniform(-10, 10, size=args.n)

with open(args.path, "w") as f:
    for number in matrix:
        f.write(str(number))
        f.write(" ")
