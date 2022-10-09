import socket
import collections

IP = "127.0.0.1"
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind((IP, PORT))
s.listen(1)

while True:
	connection, address = s.accept()
	
	data = connection.recv(4)
	len1 = int.from_bytes(data, "big")
	
	data = connection.recv(len1)
	str1 = data.decode("utf-8")
	
	data = connection.recv(4)
	len2 = int.from_bytes(data, "big")
	
	data = connection.recv(len2)
	str2 = data.decode("utf-8")
	
	print(str1, str2)
	
	fre = collections.defaultdict(lambda: 0)
	for i in range(1, len(str1)):
		if str1[i-1] == str1[i]:
			fre[str1[i]] += 1
	for i in range(1, len(str2)):
		if str2[i-1] == str2[i]:
			fre[str2[i]] += 1
	result = max(fre.items(), key=lambda a: a[1])
	
	result_char = result[0].encode()
	result_char_len = len(result_char).to_bytes(4, "big")
	result_amount = result[1].to_bytes(4, "big")
	
	connection.send(result_char_len)
	connection.send(result_char)
	connection.send(result_amount)
