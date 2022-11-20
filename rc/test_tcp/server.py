import socket
import threading
import random


def print_mat(mat):
	for line in mat:
		for column in line:
			print(column, end="")
		print()


def play_game(client_socket: socket.socket):
	mat_size = int.from_bytes(client_socket.recv(4), "big")
	mat = []
	for _ in range(mat_size):
		mat.append([])
		for _ in range(mat_size):
			mat[-1].append(0)
	
	planes_left = 0
	
	for _ in range(mat_size):
		line = random.randint(0, mat_size-1)
		column = random.randint(0, mat_size-1)
		if mat[line][column] == 0:
			mat[line][column] = 1
			planes_left += 1
	
	print(client_socket.getpeername())
	print_mat(mat)
	
	start_message = "jocul a inceput".encode()
	start_message_len = len(start_message)
	client_socket.send(int.to_bytes(start_message_len, 4, "big"))
	client_socket.send(start_message)
	
	running = True
	mistakes = 0
	while running:
		line = int.from_bytes(client_socket.recv(4), "big")
		column = int.from_bytes(client_socket.recv(4), "big")
		
		if mat[line][column] == 1:
			mat[line][column] = 0
			planes_left -= 1
			client_socket.send("DA".encode())
		else:
			mistakes += 1
			client_socket.send("NU".encode())
		
		print(client_socket.getpeername())
		print_mat(mat)
		
		client_socket.send(int.to_bytes(mistakes, 4, "big"))
		client_socket.send(int.to_bytes(planes_left, 4, "big"))
		
		if mistakes >= 5:
			running = False
			lose_message = "ai pierdut".encode()
			lose_message_len = len(lose_message)
			client_socket.send(int.to_bytes(lose_message_len, 4, "big"))
			client_socket.send(lose_message)
		elif planes_left == 0:
			running = False
			win_message = "ai castigat".encode()
			win_message_len = len(win_message)
			client_socket.send(int.to_bytes(win_message_len, 4, "big"))
			client_socket.send(win_message)
		else:
			client_socket.send(int.to_bytes(0, 4, "big"))
	
	client_socket.close()


IP = "127.0.0.1"
PORT = 4100

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))
server_socket.listen(5)

while True:
	client_socket, _ = server_socket.accept()
	game_thread = threading.Thread(target=play_game, args=(client_socket,))
	game_thread.start()
