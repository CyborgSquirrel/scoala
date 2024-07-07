import dataclasses
import pathlib
import typing


@dataclasses.dataclass
class Grammar:
    rules: dict[str, list[str]]

    @staticmethod
    def from_file(path: pathlib.Path) -> typing.Self:
        rules = dict()
        with path.open() as f:
            for line in f:
                src, dst = line.split("->")
                src = src.strip()
                dst = dst.strip()
                if src not in rules:
                    rules[src] = []
                rules[src].append(dst)
        return Grammar(rules)

    def get_terminals(self) -> set[str]:
        terminals = set()
        for dst_list in self.rules.values():
            for dst in dst_list:
                for c in dst:
                    if c.islower():
                        terminals.add(c)
        return terminals


path = pathlib.Path("grammar.txt")

grammar = Grammar.from_file(path)

print("Lista terminalelor gramaticii:")
terminals = grammar.get_terminals()
for terminal in terminals:
    print(terminal)
