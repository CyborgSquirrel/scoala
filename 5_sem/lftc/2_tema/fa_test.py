from fa import FiniteAutomaton


with open("./fa/lit_int.txt") as f:
    fa = FiniteAutomaton.read_from_stream(f)


def test_matches(text: str):
    matches = fa.matches(text)
    symbol = "x" if matches else " "
    print(f"[{symbol}] {text}")


def test_longest_prefix_len(text: str):
    longest_prefix_len = len(fa.longest_prefix(text))
    before = text[:longest_prefix_len]
    after = text[longest_prefix_len:]
    print(f"[{before}]{after}")


test_matches("0x123")
test_matches("0o154")
test_matches("0b010010")
test_matches("12343")
test_matches("1")
test_matches("0")

test_matches("0o1239")
test_matches("0b123")
test_matches("0542FSD")

print("==========")

test_longest_prefix_len("0x123 + 123")
test_longest_prefix_len("0o154 + 123")
test_longest_prefix_len("0b010010 + 123")
test_longest_prefix_len("12343 + 123")
test_longest_prefix_len("1 + 123")
test_longest_prefix_len("0 + 123")

test_longest_prefix_len("lalalalal")
