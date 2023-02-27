import socket

IP = "127.0.0.1"
PORT = 4100

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((IP, PORT))

while True:
	n1_b, addr = server_socket.recvfrom(4)
	n1 = int.from_bytes(n1_b, "big")
	print(n1)
	
	n2_b, addr = server_socket.recvfrom(4)
	n2 = int.from_bytes(n2_b, "big")
	print(n2)
	
	sum = n1+n2
	
	server_socket.sendto(int.to_bytes(sum, 4, "big"), addr)
