import argparse
import numpy as np
import os.path


argparser = argparse.ArgumentParser()
argparser.add_argument("n", type=int)
argparser.add_argument("m", type=int)
argparser.add_argument("path")
argparser.add_argument("--force", action="store_true")
args = argparser.parse_args()

if os.path.exists(args.path):
    if args.force:
        os.remove(args.path)
    else:
        print(f"File at '{args.path}' already exists.")
        exit(1)

matrix = np.random.uniform(-10, 10, size=(args.n, args.m))

# np.savetxt(args.path, matrix, fmt="%.6f", delimiter=" ")
matrix.tofile(args.path)
