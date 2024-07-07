import abc
import enum
import io

import fip.analyze as fiplib
from grammar import Nonterminal, Symbel, Terminal

WHITESPACE = set(" \n\t")


class AnalyzerState(enum.Enum):
    FORWARD = enum.auto()
    BACKWARD = enum.auto()
    FINISHED = enum.auto()
    ERROR = enum.auto()

    def _to_str(self):
        if self == self.FORWARD:
            return "q"
        elif self == self.BACKWARD:
            return "r"
        elif self == self.FINISHED:
            return "t"
        elif self == self.ERROR:
            return "e"
        else:
            assert False


# input
class Input(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def matches(self, index: int, value: str) -> bool:
        pass


class StrInput:
    def __init__(self, value: str):
        self.value = value

    def matches(self, index: int, value: str) -> bool:
        return self.value[index:index+len(value)] == value

    def __len__(self) -> int:
        return len(self.value)


class FipInput:
    def __init__(self, source: str):
        program = fiplib.Program()
        fiplib.analyze(program, fiplib.PutbackReader(io.StringIO(source)))
        self.fip = program.fip

    def matches(self, index: int, value: str) -> bool:
        print(fiplib.ATOMS[self.fip[index].atom_code], " ", value)
        return fiplib.ATOMS[self.fip[index].atom_code] == value

    def __len__(self) -> int:
        return len(self.fip)


class Kowalski:
    def __init__(
        self,
        rules: dict[Nonterminal, list[list[Symbel]]],
        input: Input,
    ):
        self.rules = rules
        self.input = input

        self.start_symbel = next(iter(rules.keys()))

        self.state = AnalyzerState.FORWARD
        self.index = 0
        self.work_stack = []
        self.input_stack = [self.start_symbel]

    def _to_str(self) -> str:
        if len(self.work_stack) <= 0:
            work_stack = "ε"
        else:
            work_stack = str(self.work_stack)

        if len(self.input_stack) <= 0:
            input_stack = "ε"
        else:
            input_stack = str(self.input_stack)
        
        state = self.state._to_str()
        
        return f"({state}, {self.index}, {work_stack}, {input_stack})"
    
    def analysis(self):
        while (
                self.state != AnalyzerState.FINISHED
            and self.state != AnalyzerState.ERROR
        ):
            print(self._to_str())
            # input()
            if self.state == AnalyzerState.FORWARD:
                if self.index >= len(self.input):
                    if len(self.input_stack) <= 0:
                        self.state = AnalyzerState.FINISHED
                    else:
                        self.state = AnalyzerState.ERROR
                else:
                    if len(self.input_stack) <= 0:
                        self.state = AnalyzerState.BACKWARD
                    else:
                        input_stack_item = self.input_stack[-1]
                        if isinstance(input_stack_item, Nonterminal):
                            rule = self.rules[input_stack_item][0]
                            self.work_stack.append((input_stack_item, 0))

                            self.input_stack.pop()
                            self.input_stack += reversed(rule)
                        elif isinstance(input_stack_item, Terminal):
                            value = input_stack_item.value
                            if self.input.matches(self.index, value):
                                if isinstance(self.input, StrInput):
                                    self.index += len(value)
                                elif isinstance(self.input, FipInput):
                                    self.index += 1
                                else:
                                    assert False
                                self.work_stack.append(input_stack_item)
                                self.input_stack.pop()
                            else:
                                self.state = AnalyzerState.BACKWARD
                        else:
                            assert False
            elif self.state == AnalyzerState.BACKWARD:
                work_stack_item = self.work_stack[-1]
                if isinstance(work_stack_item, tuple):
                    symbel, rule_index = work_stack_item

                    input_stack_pop_no = len(self.rules[symbel][rule_index])
                    for _ in range(input_stack_pop_no):
                        self.input_stack.pop()

                    if rule_index+1 < len(self.rules[symbel]):
                        self.state = AnalyzerState.FORWARD

                        self.input_stack += reversed(self.rules[symbel][rule_index+1])
                        
                        self.work_stack.pop()
                        self.work_stack.append((symbel, rule_index+1))
                    else:
                        if self.index == 0 and symbel == self.start_symbel:
                            self.state = AnalyzerState.ERROR

                        self.work_stack.pop()
                        self.input_stack.append(symbel)
                if isinstance(work_stack_item, Terminal):
                    symbel = work_stack_item
                    if isinstance(self.input, StrInput):
                        self.index -= len(symbel.value)
                    elif isinstance(self.input, FipInput):
                        self.index -= 1
                    else:
                        assert False
                    self.input_stack.append(symbel)
                    self.work_stack.pop()
        print(self._to_str())
