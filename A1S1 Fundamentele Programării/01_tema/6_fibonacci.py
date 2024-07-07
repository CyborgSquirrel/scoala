a = 1
b = 1
n = int(input('n = '))
while a <= n:
    aux = a+b
    b = a
    a = aux

print(f'm = {a}')