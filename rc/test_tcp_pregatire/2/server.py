import socket
import threading
import random
import string


def play_game(id, client_socket_1: socket.socket, client_socket_2: socket.socket):
	client_socket_1.send(int.to_bytes(id, 4, "big"))
	client_socket_2.send(int.to_bytes(id, 4, "big"))
	
	letter_2 = random.choice(string.ascii_lowercase)
	client_socket_1.send(int.to_bytes(0, 4, "big"))
	client_socket_1.send(letter_2.encode())
	
	running = True
	
	while running:
		word_len_1 = int.from_bytes(client_socket_1.recv(4), "big")
		word_1 = client_socket_1.recv(word_len_1).decode()
		letter_1 = client_socket_1.recv(1).decode()
		
		cond_1 = letter_2 in word_1
		
		client_socket_2.send(int.to_bytes(word_len_1, 4, "big"))
		client_socket_2.send(word_1.encode())
		client_socket_2.send(letter_1.encode())
		
		word_len_2 = int.from_bytes(client_socket_2.recv(4), "big")
		word_2 = client_socket_2.recv(word_len_2).decode()
		letter_2 = client_socket_2.recv(1).decode()
		
		cond_2 = letter_1 in word_2
		
		if not cond_1 or not cond_2:
			running = False
			win = "mesaj de castig".encode()
			lose = "mesaj de pierdere".encode()
			if cond_1:
				client_socket_1.send(int.to_bytes(len(win), 4, "big"))
				client_socket_1.send(win)
			else:
				client_socket_1.send(int.to_bytes(len(lose), 4, "big"))
				client_socket_1.send(lose)
			if cond_2:
				client_socket_2.send(int.to_bytes(len(win), 4, "big"))
				client_socket_2.send(win)
			else:
				client_socket_2.send(int.to_bytes(len(lose), 4, "big"))
				client_socket_2.send(lose)
		else:
			cont = "Jocul continua!".encode()
			client_socket_1.send(int.to_bytes(len(cont), 4, "big"))
			client_socket_1.send(cont)
			client_socket_2.send(int.to_bytes(len(cont), 4, "big"))
			client_socket_2.send(cont)
			
			client_socket_1.send(int.to_bytes(word_len_2, 4, "big"))
			client_socket_1.send(word_2.encode())
			client_socket_1.send(letter_2.encode())
	
	client_socket_1.close()
	client_socket_2.close()


IP = "127.0.0.1"
PORT = 4100

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))
server_socket.listen(5)

last_id = 0

while True:
	client_socket_1, _ = server_socket.accept()
	client_socket_2, _ = server_socket.accept()
	game_thread = threading.Thread(target=play_game, args=(last_id, client_socket_1, client_socket_2))
	last_id += 1
	game_thread.start()
