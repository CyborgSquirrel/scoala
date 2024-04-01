import io


class AnalyzingError(ValueError):
    def __init__(self, line: int, message: str):
        self.line = line
        self.message = message

    def __str__(self):
        return f"{self.line+1}: {self.message}"


class PutbackReader:
    def __init__(self, f: io.TextIOWrapper):
        self.f = f
        self.putback_buffer = ""
        self.index = 0
        self.line = 0

    def read(self, size: int) -> str:
        out = ""

        putback_size = min(size, len(self.putback_buffer))
        out += self.putback_buffer[:putback_size]
        self.putback_buffer = self.putback_buffer[putback_size:]
        size -= putback_size

        out += self.f.read(size)

        self.index += len(out)

        self.line += sum(int(char == "\n") for char in out)

        return out

    def putback(self, value: str):
        self.putback_buffer = value + self.putback_buffer
        self.index -= len(value)
        self.line -= sum(int(char == "\n") for char in value)

    def make_analyzing_error(self, message: str) -> AnalyzingError:
        return AnalyzingError(self.line, message)
