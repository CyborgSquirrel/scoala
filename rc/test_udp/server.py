import socket
import sys
import collections

ip = sys.argv[1]
port = int(sys.argv[2])

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((ip, port))

while True:
	data, client_addr = server_socket.recvfrom(4)
	numbers_len = int.from_bytes(data, "big")
	
	numbers = []
	for _ in range(numbers_len):
		data, _ = server_socket.recvfrom(4)
		number = int.from_bytes(data, "big")
		assert number >= 10
		numbers.append(number)
	
	divisors_list = []
	for number in numbers:
		current_divisors = []
		i = 1
		while i*i <= number:
			if number % i == 0:
				current_divisors.append(i)
				if number // i != i:
					current_divisors.append(number // i)
			i += 1
		
		# is not prime
		if len(current_divisors) != 2:
			for divisor in current_divisors:
				if divisor != 1 and divisor != number:
					divisors_list.append(divisor)
	
	divisors = collections.defaultdict(lambda: 0)
	for divisor in divisors_list:
		divisors[divisor] += 1
	
	divisors_sorted = list(divisors.items())
	divisors_sorted.sort(key=lambda a: a[1], reverse=True)
	print(divisors_sorted)
	
	divisors_sorted = [a[0] for a in divisors_sorted]
	divisors_top = set(divisors_sorted[:3])
	print(divisors_top)
	
	new_port = int(input("new_port = "))
	assert 45000 <= new_port <= 55000
	
	game_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	game_socket.bind((ip, new_port))
	
	message = b"start joc"
	game_socket.sendto(int.to_bytes(len(message), 4, "big"), client_addr)
	game_socket.sendto(message, client_addr)
	
	for _ in range(5):
		data, _ = game_socket.recvfrom(4)
		answer = int.from_bytes(data, "big")
		if answer in divisors_top:
			message = b"corect"
		else:
			message = b"incorect"
		game_socket.sendto(int.to_bytes(len(message), 4, "big"), client_addr)
		game_socket.sendto(message, client_addr)
	game_socket.close()

server_socket.close()
