import argparse
import os.path
import shutil
import subprocess
from tempfile import TemporaryDirectory
from zipfile import ZipFile

argparser = argparse.ArgumentParser()
argparser.add_argument("curs_zip")
args = argparser.parse_args()

with TemporaryDirectory() as extracted_path:
    with ZipFile(args.curs_zip) as f:
        f.extractall(extracted_path)

    to_concat = []
    for dir_path, dir_names, file_names in os.walk(extracted_path):
        for file_name in file_names:
            file_path = os.path.join(dir_path, file_name)

            _, ext = os.path.splitext(file_name)
            if ext == ".pdf" and file_name != "Biblio.pdf":
                to_concat.append(file_path)

    subprocess.run(
        ["pdftk"] + to_concat + ["cat", "output", "curs.pdf"]
    )
