import socket

IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

string = input("s = ")
i = int(input("i = "))
l = int(input("l = "))

string_bytes = string.encode()
s.send(len(string_bytes).to_bytes(4, "big"))
s.send(string_bytes)
s.send(i.to_bytes(4, "big"))
s.send(l.to_bytes(4, "big"))

substring_len = int.from_bytes(s.recv(4), "big")
substring = s.recv(substring_len).decode("utf-8")

print(substring)
