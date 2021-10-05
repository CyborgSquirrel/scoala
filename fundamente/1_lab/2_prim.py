n = int(input('n = '))
assert n >= 0, 'n nu poate sa fie < 0'

i = 2
prime = True
while i*i <= n and prime:
    prime &= (n % i != 0)
    i += 1

if prime:
    print(f'{n} este prim')
else:
    print(f'{n} nu este prim')

