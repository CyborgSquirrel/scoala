import socket

IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

str1 = input("str1 = ").encode()
str2 = input("str2 = ").encode()

s.send(len(str1).to_bytes(4, "big"))
s.send(str1)

s.send(len(str2).to_bytes(4, "big"))
s.send(str2)

result_char_len = int.from_bytes(s.recv(4), "big")
result_char = s.recv(result_char_len).decode("utf-8")
result_amount = int.from_bytes(s.recv(4), "big")

print(f"Caracterul '{result_char}' de {result_amount} ori.")
