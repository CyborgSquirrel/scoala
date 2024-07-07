import socket
import threading

IP = "127.0.0.1"
PORT = 4100

def client_thread(addr):
	thread_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	thread_socket.bind((IP, 0)) # pick a random port
	
	thread_socket.sendto(b"", addr)
	
	data, _ = thread_socket.recvfrom(4)
	string_len = int.from_bytes(data, "big")
	
	data, _ = thread_socket.recvfrom(string_len)
	string = data.decode()
	
	data, _ = thread_socket.recvfrom(1)
	character = data.decode()
	
	positions = []
	for i in range(len(string)):
		if string[i] == character:
			positions.append(i)
	
	thread_socket.sendto(int.to_bytes(len(positions), 4, "big"), addr)
	for position in positions:
		thread_socket.sendto(int.to_bytes(position, 4, "big"), addr)


server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))

while True:
	_, addr = server_socket.recvfrom(0)
	thread = threading.Thread(target=client_thread, args=(addr,))
	thread.start()
