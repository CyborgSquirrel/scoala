# 7. Pentru un n dat generați toate secvențele de paranteze care se închid corect. Exemplu: n=4 două soluții: (()) și ()().

def _recursive(answer, left, right):
	if left <= 0 and right <= 0:
		print(answer)
	else:
		if left > 0:
			_recursive(answer+"(", left-1, right)
		if left >= 0 and right > left:
			_recursive(answer+")", left, right-1)

def recursive(n):
	assert n % 2 == 0
	_recursive("", n//2, n//2)

def iterative(n):
	assert n % 2 == 0
	finished = False
	erasing = False
	left = n//2
	right = n//2
	answer = ""
	while not finished:
		if not erasing:
			if left > 0:
				answer += "("
				left -= 1
			else:
				if right > 0:
					answer += ")"
					right -= 1
				else:
					erasing = True
					print(answer)
		else:
			if len(answer) == 0:
				finished = True
			else:
				last = answer[-1]
				answer = answer[:-1]
				if last == "(":
					left += 1
					if left >= 0 and right > left:
						erasing = False
						answer += ")"
						right -= 1
				elif last == ")":
					right += 1
				else: assert False

recursive(10)
# iterative(10)