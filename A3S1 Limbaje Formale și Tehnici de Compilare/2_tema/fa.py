"""
EBNF:

```
fsa = { regula }.

regula =
      regula_stare_initiala
    | regula_stare_finala
    | regula_tranzitie
.

regula_stare_start = ".s" stare.
regula_stare_finala ".f" stare.
regula_tranzitie = ".t" stare tranzitie_char stare.

stare = stare_char { stare_char }.
stare_char =
     alfa_mic
    |alfa_maj
    |cifra
.

tranzitie_char =
     alfa_mic
    |alfa_maj
    |cifra
    |"."|"_"
.

alfa_mic = "a"|"b"|...|"z".
alfa_maj = "A"|"B"|...|"Z".
cifra = "1"|"2"|...|"9".
```
"""

import argparse
import dataclasses
import io
import itertools
import sys
import typing

from putback import PutbackReader


@dataclasses.dataclass(frozen=True)
class FiniteAutomaton:
    is_deterministic: bool
    alphabet: typing.Set[str]
    states: typing.Set[str]

    start_state: str
    final_states: typing.Set[str]
    transitions: typing.Dict[str, typing.Dict[str, typing.Set[str]]]

    @staticmethod
    def read_from_file(path: str) -> typing.Self:
        with open(path) as f:
            return FiniteAutomaton.read_from_stream(f)

    @staticmethod
    def read_from_stream(stream: io.TextIOBase) -> typing.Self:
        source = stream.read()
        tokens = source.split()

        is_deterministic = True
        alphabet = set()
        states = set()

        start_state = None
        final_states = set()
        transitions = dict()

        index = 0
        while index < len(tokens):
            command = tokens[index]
            index += 1
            match command:
                case ".s":
                    if start_state is not None:
                        raise ValueError("Multiple start states")

                    state = tokens[index]
                    index += 1
                    states.add(state)

                    start_state = state
                case ".f":
                    state = tokens[index]
                    index += 1
                    states.add(state)

                    if state in final_states:
                        print(f"State '{state}' already declared as final")
                    final_states.add(state)
                case ".t":
                    from_state = tokens[index]
                    index += 1
                    states.add(from_state)

                    transition_char = tokens[index]
                    index += 1
                    if len(transition_char) != 1:
                        raise ValueError(f"Invalid transition character {transition_char}")

                    alphabet.add(transition_char)
                    
                    to_state = tokens[index]
                    index += 1
                    states.add(to_state)

                    if from_state not in transitions:
                        transitions[from_state] = dict()
                    if transition_char not in transitions[from_state]:
                        transitions[from_state][transition_char] = set()

                    if to_state in transitions[from_state][transition_char]:
                        print(f"There already exists a transition '.t {from_state} {transition_char} {to_state}'")

                    transitions[from_state][transition_char].add(to_state)

                    if len(transitions[from_state][transition_char]) > 1:
                        is_deterministic = False
                case _:
                    raise ValueError("Invalid command")

        if start_state is None:
            raise ValueError("Missing start state")

        return FiniteAutomaton(
            is_deterministic=is_deterministic,
            alphabet=alphabet,
            states=states,

            start_state=start_state,
            final_states=final_states,
            transitions=transitions,
        )

    def matches(self, text: typing.Union[str, io.IOBase]) -> bool:
        return self.longest_prefix(text) == text

    def longest_prefix(self, text: typing.Union[str, io.IOBase]) -> typing.Optional[str]:
        assert self.is_deterministic

        if isinstance(text, str):
            text = io.StringIO(text)

        buf = []
        longest_len = 0
        state = self.start_state
        for i in itertools.count():
            char = text.read(1)
            if char == "":
                break

            buf.append(char)
            
            transitions = self.transitions
            if (chars := transitions.get(state)) is None:
                break
            if (new_states := chars.get(char)) is None:
                break
            
            # Because the finite automaton is deterministic, this should always
            # return a single state.
            state = next(iter(new_states))
            if state in self.final_states:
                longest_len = i+1

        buf = "".join(buf)
        if isinstance(text, PutbackReader):
            text.putback(buf[longest_len:])
        
        if longest_len == 0:
            if self.start_state in self.final_states:
                return ""
            else:
                return None
        else:
            return buf[:longest_len]


def main():
    argparser = argparse.ArgumentParser()
    argparser.add_argument("fa_file")
    args = argparser.parse_args()

    if args.fa_file == "-":
        fa = FiniteAutomaton.read_from_stream(sys.stdin)
    else:
        with open(args.fa_file) as f:
            fa = FiniteAutomaton.read_from_stream(f)

    if fa.is_deterministic:
        print("Finite automaton is deterministic")
    else:
        print("Finite automaton is nondeterministic")
    print()

    print("=== multimea starilor ===")
    states = ", ".join(fa.states)
    print(states)
    print()

    print("=== multimea starilor finale ===")
    final_states = ", ".join(fa.final_states)
    print(final_states)
    print()

    print("=== alfabetul ===")
    states = ", ".join(sorted(fa.alphabet))
    print(states)
    print()

    print("=== tranzitiile ===")
    states = "\n".join(
        itertools.chain.from_iterable(
            itertools.chain.from_iterable(
                (
                    f"{from_state} {char} {to_state}"
                    for to_state in to_states
                )
                for char, to_states in chars.items()
            )
            for from_state, chars in fa.transitions.items()
        )
    )
    print(states)


if __name__ == "__main__":
    main()
    
