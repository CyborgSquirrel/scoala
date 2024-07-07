import dataclasses
import pathlib
import string
import typing

NONTERMINAL_CHARS = set(string.ascii_letters + "_")
WHITESPACE = set(string.whitespace)


# symbel
class Symbel:
    pass


@dataclasses.dataclass(frozen=True)
class Nonterminal(Symbel):
    name: str

    def __repr__(self):
        return self.name


@dataclasses.dataclass(frozen=True)
class Terminal(Symbel):
    value: str

    def __repr__(self):
        return f"\"{self.value}\""


# states
class State:
    pass


@dataclasses.dataclass
class Start(State):
    pass


@dataclasses.dataclass
class ReadingNonterminal(State):
    name: list[str] = dataclasses.field(default_factory=list)


@dataclasses.dataclass
class ReadingTerminal(State):
    value: list[str] = dataclasses.field(default_factory=list)
    escape_next: bool = False


# other state
class OtherState:
    pass


class OtherStart(OtherState):
    pass


@dataclasses.dataclass
class ReadingSrc(OtherState):
    src: typing.Optional[Symbel] = None


@dataclasses.dataclass
class ReadingDst(OtherState):
    src: typing.Optional[Symbel] = None
    current_rule: list[Symbel] = dataclasses.field(default_factory=list)
    rules: list[Symbel] = dataclasses.field(default_factory=list)


def parse_rules(
    source: str | pathlib.Path
) -> dict[Symbel, list[list[Symbel]]]:
    # source
    if isinstance(source, str):
        source = pathlib.Path(source)
    with source.open() as f:
        source = f.read()
    
    rules = dict()
    state = Start()
    other_state = ReadingSrc()
    for c in source:
        while True:
            if isinstance(state, Start):
                if c in NONTERMINAL_CHARS:
                    state = ReadingNonterminal()
                    state.name = [c]
                    break
                elif c == "=":
                    if isinstance(other_state, ReadingSrc):
                        prev_other_state = other_state
                        other_state = ReadingDst()
                        other_state.src = prev_other_state.src
                    else:
                        assert False
                    break
                elif c == "|":
                    if isinstance(other_state, ReadingDst):
                        other_state.rules.append(other_state.current_rule)
                        other_state.current_rule = []
                    else:
                        assert False
                    break
                elif c == ".":
                    if isinstance(other_state, ReadingDst):
                        other_state.rules.append(other_state.current_rule)
                        other_state.current_rule = []

                        if other_state.src not in rules:
                            rules[other_state.src] = []
                        rules[other_state.src] += other_state.rules
                        other_state = ReadingSrc()
                    else:
                        assert False
                    break
                elif c == "\"":
                    state = ReadingTerminal()
                    state.value = []
                    break
                elif c in WHITESPACE:
                    break
                else:
                    print(f"Unexpected character: '{c}'.")
                    exit(0)
            elif isinstance(state, ReadingNonterminal):
                if c in NONTERMINAL_CHARS:
                    state.name.append(c)
                    break
                else:
                    nonterminal = Nonterminal("".join(state.name))

                    if isinstance(other_state, ReadingSrc):
                        other_state.src = nonterminal
                    elif isinstance(other_state, ReadingDst):
                        other_state.current_rule.append(nonterminal)
                    else:
                        assert False

                    state = Start()
            elif isinstance(state, ReadingTerminal):
                if c == "\\":
                    state.escape_next = True
                    break
                elif c == "\"" and not state.escape_next:
                    terminal = Terminal("".join(state.value))
                    if isinstance(other_state, ReadingDst):
                        other_state.current_rule.append(terminal)
                    else:
                        assert False

                    state = Start()
                    break
                else:
                    state.escape_next = False
                    state.value.append(c)
                    break
            else:
                assert False
    return rules
