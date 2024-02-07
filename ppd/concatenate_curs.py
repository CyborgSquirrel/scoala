import argparse
import logging
import os.path
import pathlib
import re
import subprocess
from tempfile import TemporaryDirectory
from zipfile import ZipFile

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

RE_DIR = re.compile("^(C|c)(\\d+)")

argparser = argparse.ArgumentParser()
argparser.add_argument("curs_zip", type=pathlib.Path)
args = argparser.parse_args()

with TemporaryDirectory() as extracted_path:
    extracted_path = pathlib.Path(extracted_path)
    with ZipFile(args.curs_zip) as f:
        f.extractall(extracted_path)

    curs_dirs = []
    for file in (extracted_path / "Cursuri").iterdir():
        match_ = RE_DIR.match(file.name)
        if match_ is None:
            logger.info("skipped '%s'", str(file))
            continue

        curs_no = int(match_.group(2))
        curs_dirs.append((curs_no, file))
    
    curs_dirs.sort(key=lambda a: a[0])
    to_concat = [a[1] for a in curs_dirs]

    subprocess.run(
        ["pdftk"] + to_concat + ["cat", "output", "curs.pdf"]
    )
