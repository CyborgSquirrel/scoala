''' TESTE:
in: 2113 323121 out: True
in: 12345 67890 out: False
in: 777 123     out: False
in: 170 7101    out: True
'''

def create_digit_vector(n):
	d = [False] * 10
	for c in n:
		d[int(c)] = True
	return d

n1 = input('n1 = ')
n1 = str(int(n1))
n2 = input('n2 = ')
n2 = str(int(n2))

d1 = create_digit_vector(n1)
d2 = create_digit_vector(n2)

p_property = True
for i in range(10):
	p_property &= d1[i] == d2[i]

if p_property:
	print(f'Numerele {n1} si {n2} au proprietatea P')
else:
	print(f'Numerele {n1} si {n2} nu au proprietatea P')
