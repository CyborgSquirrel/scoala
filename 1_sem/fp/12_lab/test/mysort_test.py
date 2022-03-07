import unittest
import mysort
import copy

class TestSelectionSort(unittest.TestCase):
	def test_sort(self):
		arr = [6, 9, 3, 9, 5, 4, 2, 1, 4]
		arr_copy = copy.copy(arr)
		
		mysort.selection_sort(arr)
		arr_copy.sort()
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_key(self):
		arr = [6, -9, 3, 9, 5, -4, 2, -1, 4]
		arr_copy = copy.copy(arr)
		
		def key(a):
			return a*a
		
		mysort.selection_sort(arr, key=key)
		arr_copy.sort(key=key)
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_reverse(self):
		arr = [6, 9, 3, 9, 5, 4, 2, 1, 4]
		arr_copy = copy.copy(arr)
		
		mysort.selection_sort(arr, reverse=True)
		arr_copy.sort(reverse=True)
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_key_reverse(self):
		arr = [6, -9, 3, 9, 5, -4, 2, -1, 4]
		arr_copy = copy.copy(arr)
		
		def key(a):
			return a*a
		
		mysort.selection_sort(arr, key=key, reverse=True)
		arr_copy.sort(key=key, reverse=True)
		
		self.assertEqual(arr, arr_copy)

class TestShakeSort(unittest.TestCase):
	def test_sort(self):
		arr = [6, 9, 3, 9, 5, 4, 2, 1, 4]
		arr_copy = copy.copy(arr)
		
		mysort.shake_sort(arr)
		arr_copy.sort()
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_key(self):
		arr = [6, -9, 3, 9, 5, -4, 2, -1, 4]
		arr_copy = copy.copy(arr)
		
		def key(a):
			return a*a
		
		mysort.shake_sort(arr, key=key)
		arr_copy.sort(key=key)
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_reverse(self):
		arr = [6, 9, 3, 9, 5, 4, 2, 1, 4]
		arr_copy = copy.copy(arr)
		
		mysort.shake_sort(arr, reverse=True)
		arr_copy.sort(reverse=True)
		
		self.assertEqual(arr, arr_copy)
	
	def test_sort_key_reverse(self):
		arr = [6, -9, 3, 9, 5, -4, 2, -1, 4]
		arr_copy = copy.copy(arr)
		
		def key(a):
			return a*a
		
		mysort.shake_sort(arr, key=key, reverse=True)
		arr_copy.sort(key=key, reverse=True)
		
		self.assertEqual(arr, arr_copy)