import argparse
import logging
import os.path
import pathlib
import re
import shutil
import subprocess
from tempfile import TemporaryDirectory
from zipfile import ZipFile

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

RE_DIR = re.compile("^(\\d+)")

argparser = argparse.ArgumentParser()
argparser.add_argument("curs_zip", type=pathlib.Path)
args = argparser.parse_args()

with TemporaryDirectory() as extracted_path:
    extracted_path = pathlib.Path(extracted_path)
    with ZipFile(args.curs_zip) as f:
        f.extractall(extracted_path)

    curs_dirs = []
    for dir in (extracted_path / "Curs").iterdir():
        match_ = RE_DIR.match(dir.name)
        if match_ is None:
            logger.info("skipped '%s'", str(dir))
            continue

        curs_no = int(match_.group(1))
        curs_dirs.append((curs_no, dir))
    
    curs_dirs.sort(key=lambda a: a[0])
    curs_dirs = [a[1] for a in curs_dirs]

    to_concat = []
    for dir in curs_dirs:
        for dir_path, dir_names, file_names in os.walk(dir):
            dir_to_concat = []
            for file_name in file_names:
                file_path = os.path.join(dir_path, file_name)

                _, ext = os.path.splitext(file_name)
                if ext == ".pdf" and file_name != "Biblio.pdf":
                    logger.info("added '%s'", file_path)
                    dir_to_concat.append((file_name, file_path))
            dir_to_concat.sort(key=lambda a: a[0])
            dir_to_concat = [a[1] for a in dir_to_concat]
            to_concat += dir_to_concat

    subprocess.run(
        ["pdftk"] + to_concat + ["cat", "output", "curs.pdf"]
    )
