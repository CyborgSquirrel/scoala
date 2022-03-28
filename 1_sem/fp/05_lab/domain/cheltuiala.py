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

def test_creeaza():
	cheltuiala = creeaza(123, "apa", date(2021, 11, 11))
	assert math.isclose(get_suma(cheltuiala), 123)
	assert get_tip(cheltuiala) == "apa"
	assert get_data(cheltuiala) == date(2021, 11, 11)
	
	cheltuiala = creeaza(13.37, "canal", date(1999, 12, 12))
	assert math.isclose(get_suma(cheltuiala), 13.37)
	assert get_tip(cheltuiala) == "canal"
	assert get_data(cheltuiala) ==  date(1999, 12, 12)
	
	try:
		cheltuiala = creeaza_azi("7", "canal")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"
	
	try:
		cheltuiala = creeaza_azi(7, 0)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		cheltuiala = creeaza_azi(7, "caal")
		assert False
	except ValueError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"

def set_suma(cheltuiala, suma):
	'''Seteaza suma unei cheltuieli.
	input: cheltuiala -- cheltuiala
	       suma -- float sau int
	'''
	tip_suma = type(suma)
	if tip_suma not in [int, float]:
		raise TypeError(f"suma must be a float, or an int, not '{tip_suma.__name__}'")
	cheltuiala[0] = float(suma)

def test_set_suma():
	cheltuiala = creeaza_azi(12, "apa")
	
	set_suma(cheltuiala, 12.001)
	assert math.isclose(get_suma(cheltuiala), 12.001)
	
	set_suma(cheltuiala, 495)
	assert math.isclose(get_suma(cheltuiala), 495)
	
	try:
		set_suma(cheltuiala, "o suta de parale si o duzina de carboave")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"

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

def test_set_tip():
	cheltuiala = creeaza_azi(83, "apa")
	
	set_tip(cheltuiala, "canal")
	assert get_tip(cheltuiala) == "canal"
	
	set_tip(cheltuiala, "incalzire")
	assert get_tip(cheltuiala) == "incalzire"
	
	set_tip(cheltuiala, "gaz")
	assert get_tip(cheltuiala) == "gaz"
	
	set_tip(cheltuiala, "altele")
	assert get_tip(cheltuiala) == "altele"
	
	set_tip(cheltuiala, "apa")
	assert get_tip(cheltuiala) == "apa"
	
	try:
		set_tip(cheltuiala, 121)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		set_tip(cheltuiala, "secret")
		assert False
	except ValueError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"

def set_data(cheltuiala, data):
	'''Seteaza data unei cheltuieli.
	input: cheltuiala -- cheltuiala
	       data -- data
	'''
	cheltuiala[2] = data

def test_set_data():
	cheltuiala = creeaza_azi(83, "apa")
	
	set_data(cheltuiala, date(2021, 11, 10))
	assert get_data(cheltuiala) == date(2021, 11, 10)
	
	set_data(cheltuiala, date(1990, 5, 5))
	assert get_data(cheltuiala) == date(1990, 5, 5)
	
	set_data(cheltuiala, date(2017, 1, 1))
	assert get_data(cheltuiala) == date(2017, 1, 1)

def ruleaza_teste():
	test_creeaza()
	test_set_suma()
	test_set_tip()
	test_set_data()

ruleaza_teste()