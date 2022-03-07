# 7. Pentru un n dat generați toate secvențele de paranteze care se închid corect. Exemplu: n=4 două soluții: (()) și ()().

def consistent(x):
	left = 0
	right = 0
	for v in x:
		if v == '(':
			left += 1
			if left > N//2:
				return False
		elif v == ')':
			right += 1
			if right > N//2:
				return False
		else:
			return False
	return right <= left

def solution(x):
	left = 0
	right = 0
	for v in x:
		if v == '(': left += 1
		elif v == ')': right += 1
		else: return False
	return left == N//2 and right == N//2	

def first(x):
	return '('

def next(x):
	if x[-1] == '(': return ')'
	elif x[-1] == ')': return None

def output_solution(x):
	print(''.join(x))

def _recursive(x):
	el = first(x)
	x.append(el)
	while el != None:
		x[-1] = el
		if consistent(x):
			if solution(x):
				output_solution(x)
			_recursive(x[:])
		el = next(x)

def recursive():
	_recursive([])

def iterative():
	popped = False
	x = []
	x.append(first(x))
	while len(x) > 0:
		if popped:
			chosen = False
			popped = False
		else:
			chosen = consistent(x)
		
		while not chosen and x[-1] != None:
			x[-1] = next(x)
			chosen = consistent(x)
		if chosen:
			if solution(x):
				output_solution(x)
			x.append(first(x))
		else:
			x.pop()
			popped = True

N = 10
iterative()
# recursive()