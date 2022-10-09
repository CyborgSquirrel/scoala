import socket

IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

n = input("n = ")
s.send(n.encode())
for i in range(int(n)):
	a = input(f"a[{i}] = ")
	s.send(a.encode())

sum = s.recv(10)
sum = sum.decode("utf-8")
print(f"Suma finala {sum}")
