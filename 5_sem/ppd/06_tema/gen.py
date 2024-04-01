import argparse
import os
import pathlib
import random
import shutil

parser = argparse.ArgumentParser()
parser.add_argument("dest_dir", type=pathlib.Path)
args = parser.parse_args()

dest_dir: pathlib.Path = args.dest_dir
if dest_dir.exists():
    shutil.rmtree(dest_dir)
os.makedirs(args.dest_dir)

last_id = 0
for country_i in range(0, 5):
    country_participants_no = random.randint(80, 100)
    
    for problem_i in range(0, 10):
        with (dest_dir / f"RezultateC{country_i+1}_P{problem_i+1}.txt").open("w") as f:
            for participant_id in range(last_id, last_id+country_participants_no):
                score = random.randint(0, 10)
                if random.random() <= 0.02:
                    score = -1
                if score == 0:
                    continue
                
                f.write(f"{participant_id},{score}\n")

    last_id += country_participants_no
