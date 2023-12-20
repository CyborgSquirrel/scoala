import argparse
import pathlib

import grammar
from kowalski import FipInput, Kowalski, StrInput

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("input", choices=["str", "fip"])
    parser.add_argument("grammar", type=pathlib.Path)
    parser.add_argument("source", type=pathlib.Path, nargs="?", default=None)
    args = parser.parse_args()

    match args.input:
        case "str":
            input_ = StrInput
        case "fip":
            input_ = FipInput
        case _:
            assert False
    
    rules = grammar.parse_rules(args.grammar)

    if args.source is not None:
        with args.source.open() as f:
            source = f.read()
        kowalski = Kowalski(rules, input_(source))
        kowalski.analysis()
    else:
        while True:
            source = input("secventa = ")
            kowalski = Kowalski(rules, input_(source))
            kowalski.analysis()
            print()
