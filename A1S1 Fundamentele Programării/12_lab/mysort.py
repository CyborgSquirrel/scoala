def key(a):
	return a

def selection_sort(arr, key=key, reverse=False):
	''' Sorts arr using selection sort.
	input: arr -- list
	       key -- function (optional)
	       reverse -- bool (optional)
	'''
	it = 0
	for i in range(len(arr)):
		idx = i
		for j in range(i+1, len(arr)):
			it += 1
			a, b = key(arr[idx]), key(arr[j])
			if (not reverse and a > b) or (reverse and a < b):
				idx = j
		arr[i], arr[idx] = arr[idx], arr[i]

def shake_sort(arr, key=key, reverse=False):
	''' Sorts arr using shake sort.
	input: arr -- list
	       key -- function (optional)
	       reverse -- bool (optional)
	'''
	is_sorted = False
	step = 1
	left = 0
	right = len(arr)
	while not is_sorted:
		is_sorted = True
		
		if step == 1:
			right -= 1
			the_range = range(left, right, step)
		if step == -1:
			left += 1
			the_range = range(right-1, left-1, step)
		
		for i in the_range:
			if step == 1:
				a, b = key(arr[i]), key(arr[i+step])
			if step == -1:
				a, b = key(arr[i+step]), key(arr[i])
				
			if (not reverse and a > b) or (reverse and a < b):
				arr[i], arr[i+step] = arr[i+step], arr[i]
				is_sorted = False
		
		step *= -1