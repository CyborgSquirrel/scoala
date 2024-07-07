"""
Analizorul lexical accepta la intrare un fisier text reprezentand un program
sursa si intocmeste ca date de iesire tabelele:

- FIP: forma interna a programului sursa
    - cod atom
    - pozitie in TS (daca e id sau lit)
- TS: tabelui de simboluri

In plus, programul va trebui sa semnaleze erorile lexicale si locul in care
apar.
"""

import argparse
import traceback
import typing
import itertools
import dataclasses
import io
import string as stringlib
import pprint
from tabulate import tabulate


class MyHashMap:
    def __init__(self):
        self.size = 1000
        self.entries = [
            [] for _ in range(self.size)
        ]

    def __hash(self, key: typing.Any):
        return hash(key) % self.size

    def __getitem__(self, key: typing.Any) -> typing.Any:
        h = self.__hash(key)
        for e_key, e_value in self.entries[h]:
            if key == e_key:
                value = e_value
                break

        try:
            return value
        except UnboundLocalError as ex:
            raise KeyError from ex

    def __setitem__(self, key: typing.Any, value: typing.Any):
        h = self.__hash(key)
        for i, (e_key, e_value) in enumerate(self.entries[h]):
            if key == e_key:
                self.entries[h].pop(i)
                break

        self.entries[h].append((key, value))

    def __contains__(self, key: typing.Any) -> bool:
        h = self.__hash(key)
        for e_key, e_value in self.entries[h]:
            if key == e_key:
                return True
                break

        return False

    def items(self):
        return itertools.chain.from_iterable(self.entries)


WHITESPACE_CHAR = set(list(" \t\n"))
STR_LIT_CHAR = set(
      stringlib.ascii_lowercase
    + stringlib.ascii_uppercase
    + stringlib.digits
    + "{}= "
)

SPECIAL_ATOMS = [
    "id",
    "lit",
]
NUMBER_LIT_START_CHAR = set(stringlib.digits)
NUMBER_LIT_PREFIX = set(["0b", "0o", "0x"])
ID_START = set(
      stringlib.ascii_lowercase
    + stringlib.ascii_uppercase
)
ID_CONTINUE = set(
      stringlib.ascii_lowercase
    + stringlib.ascii_uppercase
    + stringlib.digits
    + "_"
)

WORD_ATOMS = [
    "fn",
    "main",
    "if",
    "while",
    "struct",
    "let",
    "mut",
    "println!",
]
WORD_ATOM_START_CHAR = set(
      stringlib.ascii_lowercase
    + stringlib.ascii_uppercase
    + "_"
)
WORD_ATOM_CHAR = set(
      stringlib.ascii_lowercase
    + stringlib.ascii_uppercase
    + stringlib.digits
    + "_" + "!"
)

SYMBOL_ATOMS = [
    ";", "{", "}", "(", ")", "::", ":", ".", ",",
    "+", "-", "*", "/", "%", "<=", ">=", "<", ">", "==", "!=", "!", "=",
    "&mut", "&",
]
SYMBOL_ATOM_START_CHAR = set(atom[0] for atom in SYMBOL_ATOMS)

ATOMS = SPECIAL_ATOMS + WORD_ATOMS + SYMBOL_ATOMS

ATOM_TO_CODE = {
    atom: code
    for code, atom in zip(itertools.count(), ATOMS)
}


@dataclasses.dataclass(frozen=True)
class FipEntry:
    atom_code: int
    ts_id_code: typing.Optional[int] = dataclasses.field(default=None, kw_only=True)
    ts_lit_code: typing.Optional[int] = dataclasses.field(default=None, kw_only=True)


@dataclasses.dataclass
class Program:
    fip: list[FipEntry] = dataclasses.field(default_factory=list, init=False)

    ts_id_code: int = dataclasses.field(default=0, init=False)
    ts_id: dict[str, int] = dataclasses.field(default_factory=dict, init=False)
    # ts_id: MyHashMap = dataclasses.field(default_factory=MyHashMap, init=False)

    ts_lit_code: int = dataclasses.field(default=0, init=False)
    ts_lit: dict[str, int] = dataclasses.field(default_factory=dict, init=False)
    # ts_lit: MyHashMap = dataclasses.field(default_factory=MyHashMap, init=False)

    def get_ts_id_code(self, value: str) -> int:
        if value not in self.ts_id:
            self.ts_id[value] = self.ts_id_code
            self.ts_id_code += 1
        return self.ts_id[value]

    def get_ts_lit_code(self, value: str) -> int:
        if value not in self.ts_lit:
            self.ts_lit[value] = self.ts_lit_code
            self.ts_lit_code += 1
        return self.ts_lit[value]


class AnalyzingError(ValueError):
    def __init__(self, index: int, message: str):
        self.index = index
        self.message = message

    def __str__(self):
        return f"{self.index}: {self.message}"


class PutbackReader:
    def __init__(self, f: io.TextIOWrapper):
        self.f = f
        self.putback_buffer = ""
        self.index = 0

    def read(self, size: int) -> str:
        out = ""

        putback_size = min(size, len(self.putback_buffer))
        out += self.putback_buffer[:putback_size]
        self.putback_buffer = self.putback_buffer[putback_size:]
        size -= putback_size

        out += self.f.read(size)

        self.index += len(out)

        return out

    def putback(self, value: str):
        self.putback_buffer = value + self.putback_buffer
        self.index -= len(value)

    def make_analyzing_error(self, message: str) -> AnalyzingError:
        return AnalyzingError(self.index, message)


def read_id(f: PutbackReader):
    found_id = ""

    c = f.read(1)
    if len(c) <= 0:
        assert False
    found_id += c
    
    if c in ID_START:
        while True:
            c = f.read(1)
            if c in ID_CONTINUE:
                found_id += c
            else:
                f.putback(c)
                break
    elif c == "_":
        c = f.read(1)
        if c in ID_CONTINUE:
            found_id += c
        else:
            if len(c) == 0 or c in SYMBOL_ATOMS:
                raise f.make_analyzing_error("id may not consist of only '_'")
            else:
                raise f.make_analyzing_error(f"id starting with '_' may not be followed by '{c}'")

        while True:
            c = f.read(1)
            if c in ID_CONTINUE:
                found_id += c
            else:
                f.putback(c)
                break
    else:
        assert False

    if len(found_id) > 250:
        raise f.make_analyzing_error("id may not be longer than 250 characters")
    
    return found_id


def analyze(program: Program, f: PutbackReader):
    while True:
        c = f.read(1)

        if len(c) == 0:
            break
        
        if c == "\"":
            found_string = ""

            while True:
                c = f.read(1)
                if c == "\"":
                    break
                elif c in STR_LIT_CHAR:
                    found_string += c
                else:
                    if len(c) <= 0:
                        raise f.make_analyzing_error("string is missing terminator")
                    else:
                        raise f.make_analyzing_error(f"invalid character in string '{c}'")

            found_string = "\"" + found_string
            code = program.get_ts_lit_code(found_string)
            program.fip.append(FipEntry(ATOM_TO_CODE["lit"], ts_lit_code=code))
        elif c in WHITESPACE_CHAR:
            pass
        elif c in SYMBOL_ATOM_START_CHAR:
            f.putback(c)
            found_atom = None

            for symbol_atom in SYMBOL_ATOMS:
                read = f.read(len(symbol_atom))
                if read == symbol_atom:
                    found_atom = symbol_atom
                    break
                else:
                    f.putback(read)

            if found_atom is None:
                # There is really no way for this to happen I think.
                assert False

            program.fip.append(FipEntry(ATOM_TO_CODE[found_atom]))
        elif c in NUMBER_LIT_START_CHAR:
            f.putback(c)
            found_atom = ""

            # prefix
            if (prefix := f.read(2)) in NUMBER_LIT_PREFIX:
                found_atom += prefix
            else:
                f.putback(prefix)
                prefix = None

            if prefix == "0b":
                accepted_char = set("01")
            elif prefix == "0o":
                accepted_char = set(stringlib.octdigits)
            elif prefix == "0x":
                accepted_char = set(stringlib.hexdigits)
            else:
                accepted_char = set(stringlib.digits)
            
            # number
            while True:
                c = f.read(1)
                if c in accepted_char:
                    found_atom += c
                else:
                    f.putback(c)
                    break

            # float decimal part
            if prefix is None:
                c = f.read(1)
                if c == ".":
                    found_atom += c
                    while True:
                        c = f.read(1)
                        if c in accepted_char:
                            found_atom += c
                        else:
                            f.putback(c)
                            break
                else:
                    f.putback(c)

            code = program.get_ts_lit_code(found_atom)
            program.fip.append(FipEntry(ATOM_TO_CODE["lit"], ts_lit_code=code))
        elif c in WORD_ATOM_START_CHAR:
            f.putback(c)
            found_atom = ""
            
            while True:
                c = f.read(1)
                if c in WORD_ATOM_CHAR:
                    found_atom += c
                else:
                    f.putback(c)
                    break

            if found_atom in WORD_ATOMS:
                program.fip.append(FipEntry(ATOM_TO_CODE[found_atom]))
            else:
                f.putback(found_atom)
                found_id = read_id(f)
                code = program.get_ts_id_code(found_id)
                program.fip.append(FipEntry(ATOM_TO_CODE["id"], ts_id_code=code))
        else:
            raise f.make_analyzing_error(f"unexpected character '{c}'")


def main():
    parser = argparse.ArgumentParser(
        prog="analizor lexical",
    )
    parser.add_argument("sursa")
    args = parser.parse_args()

    source_path = args.sursa
    with open(source_path) as f:
        f = PutbackReader(f)
        program = Program()
        try:
            analyze(program, f)
        except AnalyzingError as ex:
            traceback.print_exc()

    print(tabulate(
          (
              (
                  entry.atom_code,
                  ATOMS[entry.atom_code],
                  entry.ts_id_code if entry.ts_id_code is not None else "",
                  entry.ts_lit_code if entry.ts_lit_code is not None else "",
              )
              for entry in program.fip
          ),
          headers=[
              "cod atom", "atom", "cod ts id", "cod ts lit"
          ],
          tablefmt="github",
    ))
    print()

    print(tabulate(
          (
              (
                  cod,
                  id,
              )
              for id, cod in
              sorted(program.ts_id.items(), key=lambda a: a[1])
          ),
          headers=[
              "cod", "id",
          ],
          tablefmt="github",
    ))
    print()

    print(tabulate(
          (
              (
                  cod,
                  lit,
              )
              for lit, cod
              in sorted(program.ts_lit.items(), key=lambda a: a[1])
          ),
          headers=[
              "cod", "lit",
          ],
          tablefmt="github",
    ))
    print()
    

if __name__ == "__main__":
    main()
