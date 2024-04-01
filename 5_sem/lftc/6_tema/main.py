import argparse
import pathlib
import subprocess
import tempfile

file = pathlib.Path(__file__)
dir = file.parent

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=pathlib.Path)
    parser.add_argument("output", type=pathlib.Path)
    parser.add_argument("--run", action="store_true", default=False)
    args = parser.parse_args()

    subprocess.run(
        ["make", "target/analyzer"],
        cwd=dir,
        check=True,
    )

    with tempfile.TemporaryDirectory() as tmp_dir:
        tmp_dir = pathlib.Path(tmp_dir)

        subprocess.run([
            str(dir / "target" / "analyzer"),
            str(args.source),
            str(tmp_dir / "output.asm"),
        ], check=True)

        subprocess.run([
            "nasm",
            "-felf32",
            str(tmp_dir / "output.asm"),
            "-o", str(tmp_dir / "output.o"),
        ], check=True)

        subprocess.run([
            "gcc",
            "-m32",
            str(tmp_dir / "output.o"),
            "-o", str(args.output),
        ])

        if args.run:
            subprocess.run([
                str(args.output.absolute()),
            ])
