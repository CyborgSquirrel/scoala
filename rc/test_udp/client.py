import socket
import sys

ip = sys.argv[1]
port = int(sys.argv[2])

server_addr = (ip, port)

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

numbers_len = int(input("numbers_len = "))
client_socket.sendto(int.to_bytes(numbers_len, 4, "big"), server_addr)
for i in range(numbers_len):
	number = int(input(f"numbers[{i}] = "))
	client_socket.sendto(int.to_bytes(number, 4, "big"), server_addr)

data, server_addr = client_socket.recvfrom(4)
message_len = int.from_bytes(data, "big")

data, _ = client_socket.recvfrom(message_len)
message = data.decode()

print(message)

for _ in range(5):
	answer = int(input("answer = "))
	client_socket.sendto(int.to_bytes(answer, 4, "big"), server_addr)
	
	data, server_addr = client_socket.recvfrom(4)
	message_len = int.from_bytes(data, "big")
	
	data, _ = client_socket.recvfrom(message_len)
	message = data.decode()
	
	print(message)

client_socket.close()
