import socket

IP = "172.30.113.147"
PORT = 42069

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))

numbers = input("numbers = ")
s.send(numbers.encode())

sum = s.recv(10)
sum = sum.decode("utf-8")
print(f"Suma finala {sum}")
