import string


ID_START = (
      string.ascii_lowercase
    + string.ascii_uppercase
)
ID_CONTINUE = (
      string.ascii_lowercase
    + string.ascii_uppercase
    + string.digits
    + "_"
)


with open("./fa/id.txt", "w") as f:
    def write(line: str):
        f.write(line + "\n")

    write(".s Start")

    for i in range(1, 250+1):
        write(f".f F{i}")
    
    for char in ID_START:
        write(f".t Start {char} F1")

    write(".t Start _ Underscore")

    for char in ID_CONTINUE:
        write(f".t Underscore {char} F2")

    for i in range(2, 250+1):
        for char in ID_CONTINUE:
            write(f".t F{i-1} {char} F{i}")
