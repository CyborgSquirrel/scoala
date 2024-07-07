import itertools
import json
import logging
import os
import pathlib
import re
import shutil
import stat
import subprocess
import tempfile
import typing

logger = logging.getLogger(__name__)
src_path = pathlib.Path(__file__)

TARGET_PATH = src_path.parent / "target"

BIN_PATH = src_path.parent / "bin"
BIN_PATHS = (BIN_PATH / str(i) for i in itertools.count())

JAVA_PATH = BIN_PATH / "java"
JAVA_PATHS = (JAVA_PATH / (str(i) + ".java") for i in itertools.count())

RE_CODE_FENCE = re.compile("```[^\n]*\\n(.*)```", re.DOTALL)
RE_RUN_SPEC = re.compile("// run (.*)")

code_fence_test = """
```c
// run {"compiler": "c"}
#include <stdlib.h>
int main() {
    printf("hello\n");
}
```
"""
assert len(RE_CODE_FENCE.findall(code_fence_test)) == 1


def compile_mpi(name: str, source: str, args: typing.Dict):
    bin_path = next(BIN_PATHS)

    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)
        source_path = tmp_dir / "source.c"
        source_path.write_text(source)
        subprocess.run([
            "mpicc",
            # "-g",
            "-lm",  # add math.h
            str(source_path),
            "-o",
            bin_path,
        ], check=True)

    processes_arg = ""
    if "processes_no" in args:
        processes_arg = "-np " + str(args["processes_no"])
    
    target_path = TARGET_PATH / name
    target_path.write_text(
        "#!/usr/bin/env sh\n"
        f"mpiexec {processes_arg} \"{bin_path}\" \"$@\"\n",
    )
    target_path.chmod(
          stat.S_IRUSR
        | stat.S_IWUSR
        | stat.S_IRGRP
        | stat.S_IROTH
        | stat.S_IEXEC
    )


def compile_java(name: str, source: str, args: typing.Dict):
    java_path = next(JAVA_PATHS)
    java_path.write_text(source)
    
    target_path = TARGET_PATH / name
    target_path.write_text(
        "#!/usr/bin/env sh\n"
        f"java \"{java_path}\" \"$@\"\n",
    )
    target_path.chmod(
          stat.S_IRUSR
        | stat.S_IWUSR
        | stat.S_IRGRP
        | stat.S_IROTH
        | stat.S_IEXEC
    )


def compile_omp(name: str, source: str, args: typing.Dict):
    target_path = TARGET_PATH / name
    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)
        source_path = tmp_dir / "source.c"
        source_path.write_text(source)
        subprocess.run([
            "gcc",
            "-fopenmp",
            # "-g",
            str(source_path),
            "-o",
            str(target_path),
        ], check=True)


def compile_cpp(name: str, source: str, args: typing.Dict):
    target_path = TARGET_PATH / name
    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)
        source_path = tmp_dir / "source.cpp"
        source_path.write_text(source)
        subprocess.run([
            "g++",
            # "-g",
            str(source_path),
            "-o",
            str(target_path),
        ], check=True)


compilers = {
    "mpi": compile_mpi,
    "java": compile_java,
    "omp": compile_omp,
    "cpp": compile_cpp,
}


if TARGET_PATH.exists():
    shutil.rmtree(TARGET_PATH)
TARGET_PATH.mkdir(parents=True)

if BIN_PATH.exists():
    shutil.rmtree(BIN_PATH)
BIN_PATH.mkdir(parents=True)

JAVA_PATH.mkdir(parents=True)

if __name__ == "__main__":
    for dir_path, dir_names, file_names in os.walk(src_path.parent):
        file_paths = [pathlib.Path(os.path.join(dir_path, file_name)) for file_name in file_names]
        for file_path in file_paths:
            if file_path.suffix != ".md":
                continue

            for i, source in enumerate(RE_CODE_FENCE.findall(file_path.read_text())):
                name = f"{file_path.name}.{i}"
                
                run = source.splitlines(False)[0].strip()
                match = RE_RUN_SPEC.fullmatch(run)
                if match is None:
                    logging.warning("run string '%s' didn't match", run)
                    continue

                run = json.loads(match.group(1).strip())
                if run["compiler"] in compilers:
                    compilers[run["compiler"]](name, source, run.get("args", {}))
                else:
                    logging.warning("unknown compiler '%s'", run["compiler"])
