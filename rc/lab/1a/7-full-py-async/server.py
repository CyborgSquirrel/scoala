import os
import socket
import sys


def serve_client(s: socket.socket):
	# Receive
	string_len = int.from_bytes(s.recv(4), "big")
	string = s.recv(string_len).decode("utf-8")
	i = int.from_bytes(s.recv(4), "big")
	l = int.from_bytes(s.recv(4), "big")
	
	# Respond
	substring = string[i:i+l]
	substring_bytes = substring.encode()
	s.send(len(substring_bytes).to_bytes(4, "big"))
	s.send(substring_bytes)


IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((IP, PORT))
s.listen(5)

while True:
	cs, addr = s.accept()
	pid = os.fork()
	if pid == 0:
		serve_client(cs)
		sys.exit(0)
	else:
		pass
