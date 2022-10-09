import socket

IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((IP, PORT))
s.listen(1)

while True:
	connection, address = s.accept()
	data = connection.recv(10)
	n = int(data)
	sum = 0
	for _ in range(n):
		data = connection.recv(10)
		sum += int(data)
	connection.send(str(sum).encode())
