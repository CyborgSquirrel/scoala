import math, collections
from datetime import date

''' CHELTUIALA '''

def creeaza(suma, tip, data):
	'''Creeaza o cheltuiala.
	input: suma -- float sau int
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	       data -- date
	output: cheltuiala -- cheltuiala
	'''
	
	tip_suma = type(suma)
	if tip_suma not in [int, float]:
		raise TypeError(f"suma must be a float, or an int, not '{tip_suma.__name__}'")
	suma = float(suma)
	
	if type(tip) != str:
		raise TypeError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	elif tip not in ['apa', 'canal', 'incalzire', 'gaz', 'altele']:
		raise ValueError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	
	return [suma, tip, data]

def creeaza_azi(suma, tip):
	'''Creeaza o cheltuiala, a carei data este setata la ziua de azi.
	input: suma -- float sau int
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuiala -- cheltuiala
	'''
	return creeaza(suma, tip, date.today())

def get_suma(cheltuiala):
	'''Obtine suma unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: suma -- float
	'''
	return cheltuiala[0]

def get_tip(cheltuiala):
	'''Obtine tipul unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	return cheltuiala[1]

def get_data(cheltuiala):
	'''Obtine tipul unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: data -- date
	'''
	return cheltuiala[2]

def set_suma(cheltuiala, suma):
	'''Seteaza suma unei cheltuieli.
	input: cheltuiala -- cheltuiala
	       suma -- float sau int
	'''
	tip_suma = type(suma)
	if tip_suma not in [int, float]:
		raise TypeError(f"suma must be a float, or an int, not '{tip_suma.__name__}'")
	cheltuiala[0] = float(suma)

def set_tip(cheltuiala, tip):
	'''Seteaza tipul unei cheltuieli.
	input: cheltuiala -- cheltuiala
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	if type(tip) != str:
		raise TypeError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	elif tip not in ['apa', 'canal', 'incalzire', 'gaz', 'altele']:
		raise ValueError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	
	cheltuiala[1] = tip

def set_data(cheltuiala, data):
	'''Seteaza data unei cheltuieli.
	input: cheltuiala -- cheltuiala
	       data -- data
	'''
	cheltuiala[2] = data