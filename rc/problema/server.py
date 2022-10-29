import threading
import socket
import random


def handle_client(client_socket: socket.socket):
	word_bytes_len = int.from_bytes(client_socket.recv(4), "big")
	word = client_socket.recv(word_bytes_len).decode()
	
	p3 = random.randint(2, len(word)-1)
	p2 = random.randint(1, p3-1)
	p1 = random.randint(0, p2-1)
	thesum = ord(word[p1]) + ord(word[p2]) + ord(word[p3])
	
	print(thesum)
	
	for attempts in range(5):
		guess = int.from_bytes(client_socket.recv(4), "big")
		if guess == thesum:
			client_socket.send(int.to_bytes(attempts+1, 4, "big"))
			break
		else:
			client_socket.send(int.to_bytes(-1, 4, "big", signed=True))
			keep_going = int.from_bytes(client_socket.recv(1), "big")
			if keep_going == 0:
				client_socket.send(int.to_bytes(attempts+1, 4, "big"))
				break
	
	client_socket.close()


IP = "127.0.0.1"
PORT = 8000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))
server_socket.listen(5)

while True:
	client_socket, _ = server_socket.accept()
	thread = threading.Thread(target=handle_client, args=(client_socket,))
	thread.start()
