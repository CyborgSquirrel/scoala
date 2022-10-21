import socket

IP = "172.30.113.147"
PORT = 42069

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

a = int(input("a = "))
a_b = a.to_bytes(4, "big")
s.send(a_b)

divisors_len_b = s.recv(4)
divisors_len = int.from_bytes(divisors_len_b, "big")
divisors = []
for _ in range(divisors_len):
	divisor_b = s.recv(4)
	divisor = int.from_bytes(divisor_b, "big")
	divisors.append(divisor)

print(divisors)
