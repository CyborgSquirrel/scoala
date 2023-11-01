from fa import FiniteAutomaton


with open("./fa/lab.txt") as f:
    fa = FiniteAutomaton.read_from_stream(f)


def test_matches(text: str):
    matches = fa.matches(text)
    symbol = "x" if matches else " "
    print(f"[{symbol}] {text}")


def test_longest_prefix_len(text: str):
    longest_prefix_len = fa.longest_prefix_len(text)
    before = text[:longest_prefix_len]
    after = text[longest_prefix_len:]
    print(f"[{before}]{after}")


test_matches("")
test_matches("a")
test_matches("b")
test_matches("ab")
test_matches("aaaaabbb")

test_matches("aabb")
test_matches("aaaaaaaaaaa")
test_matches("bbbbbbbbbbbbb")

test_matches("adfda")

test_longest_prefix_len("aabb")
test_longest_prefix_len("aaaaaaaaa")
test_longest_prefix_len("bbbbbbbb")
test_longest_prefix_len("aacb")
test_longest_prefix_len("c")
