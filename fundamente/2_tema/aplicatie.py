'''

documentatia:
https://docs.google.com/spreadsheets/d/1VMHF_AUbA3-UA-PBqw3UMrchYcuvuchTdvw27CtZ7sM/edit?usp=sharing

'''

from collections import deque

def read_sequence():
	print('Introduceti elementele sirului, separate prin tasta enter. Atunci cand ati terminat sa le introduceti, scrieti exit.')
	s = []
	while True:
		a = input()
		if a == 'exit':
			break
		a = int(a)
		s.append(a)
	return s

def longest_distinct_sequence(s):
	answer = []
	d = deque()
	f = {}
	for a in s:
		while a in f:
			b = d.popleft()
			del f[b]
		d.append(a)
		f[a] = True
		
		if len(d) > len(answer):
			answer = list(d)
	return answer

def longest_maxsum_sequence(s):
	answer = []
	answer_sum = 0
	
	index = 0
	my_sum = 0
	for i,a in enumerate(s):
		if my_sum < 0:
			my_sum = 0
			index = i
		my_sum += a
		
		if my_sum > answer_sum or (my_sum == answer_sum and i-index+1 > len(answer)):
			answer = s[index:i+1]
			answer_sum = my_sum
	return answer

s = []

while True:
	menu = '''1. Citeste un sir de numere intregi
2. Gaseste secventa de lungime maxima in care toate elementele sunt distincte intre ele
3. Gaseste secventa de lungime maxima cu suma maxima
4. Iesi din aplicatie'''
	
	print(menu)

	choice = input()

	if choice == '1':
		s = read_sequence()
	elif choice == '2':
		print(longest_distinct_sequence(s))
	elif choice == '3':
		print(longest_maxsum_sequence(s))
	elif choice == '4':
		break
	else:
		print('Alegere invalida')
