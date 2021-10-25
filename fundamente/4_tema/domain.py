import math, collections
from datetime import date

''' CHELTUIALA '''

def creeaza_cheltuiala(suma, tip, data):
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
	
	return {
		"suma": suma,
		"tip": tip,
		"data": data,
	}

def creeaza_cheltuiala_azi(suma, tip):
	'''Creeaza o cheltuiala, a carei data este setata la ziua de azi.
	input: suma -- float sau int
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuiala -- cheltuiala
	'''
	return creeaza_cheltuiala(suma, tip, date.today())

def get_suma(cheltuiala):
	'''Obtine suma unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: suma -- float
	'''
	return cheltuiala["suma"]

def get_tip(cheltuiala):
	'''Obtine tipul unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	return cheltuiala["tip"]

def get_data(cheltuiala):
	'''Obtine tipul unei cheltuieli.
	input: cheltuiala -- cheltuiala
	output: data -- date
	'''
	return cheltuiala["data"]

def test_creeaza_cheltuiala():
	cheltuiala = creeaza_cheltuiala(123, "apa", date(2021, 11, 11))
	assert math.isclose(get_suma(cheltuiala), 123)
	assert get_tip(cheltuiala) == "apa"
	assert get_data(cheltuiala) == date(2021, 11, 11)
	
	cheltuiala = creeaza_cheltuiala(13.37, "canal", date(1999, 12, 12))
	assert math.isclose(get_suma(cheltuiala), 13.37)
	assert get_tip(cheltuiala) == "canal"
	assert get_data(cheltuiala) ==  date(1999, 12, 12)
	
	try:
		cheltuiala = creeaza_cheltuiala_azi("7", "canal")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"
	
	try:
		cheltuiala = creeaza_cheltuiala_azi(7, 0)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		cheltuiala = creeaza_cheltuiala_azi(7, "caal")
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
	cheltuiala["suma"] = float(suma)

def test_set_suma():
	cheltuiala = creeaza_cheltuiala_azi(12, "apa")
	
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
	
	cheltuiala["tip"] = tip

def test_set_tip():
	cheltuiala = creeaza_cheltuiala_azi(83, "apa")
	
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
	cheltuiala["data"] = data

def test_set_data():
	cheltuiala = creeaza_cheltuiala_azi(83, "apa")
	
	set_data(cheltuiala, date(2021, 11, 10))
	assert get_data(cheltuiala) == date(2021, 11, 10)
	
	set_data(cheltuiala, date(1990, 5, 5))
	assert get_data(cheltuiala) == date(1990, 5, 5)
	
	set_data(cheltuiala, date(2017, 1, 1))
	assert get_data(cheltuiala) == date(2017, 1, 1)

''' APARTAMENTE '''

''' ADAUGARE '''

def adauga_cheltuiala(apartamente, operatii, indice_apartament, cheltuiala):
	'''Adauga cheltuiala la un apartament, din dictionarul de apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       cheltuiala -- cheltuiala
	'''
	if not indice_apartament in apartamente:
		apartamente[indice_apartament] = []
	operatii.append({"nume":"adauga", "indice_apartament":indice_apartament, "indice_cheltuiala":len(apartamente[indice_apartament])})
	apartamente[indice_apartament].append(cheltuiala)

def test_adauga_cheltuiala():
	apartamente = {}
	
	cheltuieli = [
		creeaza_cheltuiala_azi(6.5756, "gaz"),
		creeaza_cheltuiala_azi(456, "apa"),
		creeaza_cheltuiala_azi(0.0003, "altele"),
		creeaza_cheltuiala_azi(45646, "canal"),
		creeaza_cheltuiala_azi(76557, "incalzire"),
	]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli[0])
	
	assert apartamente[1][0] == cheltuieli[0]
	
	adauga_cheltuiala(apartamente, 2, cheltuieli[1])
	adauga_cheltuiala(apartamente, 2, cheltuieli[2])
	adauga_cheltuiala(apartamente, 2, cheltuieli[3])
	
	assert apartamente[2] == [cheltuieli[1], cheltuieli[2], cheltuieli[3]]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli[4])
	
	assert apartamente[1][1] == cheltuieli[4]

def sterge_cheltuiala(apartamente, operatii, indice_apartament, indice_cheltuiala):
	'''Adauga cheltuiala la un apartament, din dictionarul de apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       indice_cheltuiala -- int
	'''
	pass

def test_sterge_cheltuiala():
	apartamente = {}
	# operatii = []
	
	cheltuieli = [
		creeaza_cheltuiala_azi(456, "apa"),
		creeaza_cheltuiala_azi(0.0003, "altele"),
		creeaza_cheltuiala_azi(45646, "canal"),
		creeaza_cheltuiala_azi(76557, "incalzire"),
	]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli[0])
	sterge_cheltuiala(apartamente, 1, 0)
	assert len(apartamente[1] == 0)
	
	adauga_cheltuiala(apartamente, 2, cheltuieli[1])
	adauga_cheltuiala(apartamente, 2, cheltuieli[2])
	adauga_cheltuiala(apartamente, 2, cheltuieli[3])
	
	sterge_cheltuiala(apartamente, 2, 2)
	assert len(apartamente[2] == 2)
	sterge_cheltuiala(apartamente, 2, 0)
	assert len(apartamente[2] == 1)
	sterge_cheltuiala(apartamente, 2, 0)
	assert len(apartamente[2] == 0)

''' STERGERE '''

def sterge_cheltuieli_apartamente_consecutive(apartamente, indice_primul_apartament, indice_ultimul_apartament):
	'''Sterge toate cheltuielile apartamentelor, ale calor indice se afla intre indice_primul_apartament si indice_ultimul_apartament.
	input: apartamente -- dictionar cu apartamente
	       indice_primul_apartament -- int
	       indice_ultimul_apartament -- cheltuiala
	'''
	for i in range(indice_primul_apartament, indice_ultimul_apartament+1):
		try:
			del apartamente[i]
		except KeyError:
			pass

def test_sterge_cheltuieli_apartamente_consecutive():
	apartamente = {}
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 4, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 100, creeaza_cheltuiala_azi(100, 'apa'))
	
	sterge_cheltuieli_apartamente_consecutive(apartamente, 2, 3)
	
	assert len(apartamente) == 3
	
	assert 1 in apartamente
	assert not 2 in apartamente
	assert not 3 in apartamente
	assert 4 in apartamente
	assert 100 in apartamente

def sterge_cheltuieli_dupa_tip(apartamente, tip):
	'''Sterge toate cheltuielile ale caror tip este egal cu tipul furnizat.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	for indice in list(apartamente):
		apartament = apartamente[indice]
		i = 0
		while i < len(apartament):
			if get_tip(apartament[i]) == tip:
				del apartament[i]
			else:
				i += 1
		if len(apartament) == 0:
			del apartamente[indice]

def test_sterge_cheltuieli_dupa_tip():
	apartamente = {}
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala_azi(100, 'canal'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala_azi(100, 'altele'))
	adauga_cheltuiala(apartamente, 4, creeaza_cheltuiala_azi(100, 'apa'))
	adauga_cheltuiala(apartamente, 100, creeaza_cheltuiala_azi(100, 'gaz'))
	adauga_cheltuiala(apartamente, 101, creeaza_cheltuiala_azi(100, 'apa'))
	
	sterge_cheltuieli_dupa_tip(apartamente, "incalzire")
	
	assert 1 in apartamente and len(apartamente[1]) == 3
	assert 2 in apartamente and len(apartamente[2]) == 2
	assert 3 in apartamente and len(apartamente[3]) == 3
	assert 4 in apartamente and len(apartamente[4]) == 1
	assert 100 in apartamente and len(apartamente[100]) == 1
	assert 101 in apartamente and len(apartamente[101]) == 1
	
	sterge_cheltuieli_dupa_tip(apartamente, "apa")
	
	assert 1 in apartamente and len(apartamente[1]) == 1
	assert 2 not in apartamente
	assert 3 in apartamente and len(apartamente[3]) == 2
	assert not 4 in apartamente
	assert 100 in apartamente and len(apartamente[100]) == 1
	assert not 101 in apartamente

''' CAUTARE '''

def cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, suma):
	'''Cauta toate apartamentele care au cheltuieli mai mari decat suma furnizata.
	input: apartamente -- dictionar cu apartamente
	       suma -- float sau int
	output: apartamentele_cautate -- lista cu indicii apartamentelor cautate
	'''
	apartamentele_cautate = []
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if get_suma(cheltuiala) > suma:
				apartamentele_cautate.append(indice)
				break
	return apartamentele_cautate

def test_cauta_apartamente_cu_cheltuieli_mai_mari():
	apartamente = {}
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(1, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(15, 'canal'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(10, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(5, 'gaz'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(15, 'apa'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(999, 'canal'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(1000, 'altele'))
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 0)
	assert apartamentele_cautate == [1, 2, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 10)
	assert apartamentele_cautate == [1, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 99)
	assert apartamentele_cautate == [1, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 999)
	assert apartamentele_cautate == [10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 1000)
	assert apartamentele_cautate == []

def cauta_cheltuieli_de_tip(apartamente, tip):
	'''Cauta toate apartamentele care au cheltuieli mai mari decat suma furnizata.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuielile_cautate -- lista cu cheltuielile cautate
	'''
	cheltuielile_cautate = []
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if get_tip(cheltuiala) == tip:
				cheltuielile_cautate.append(cheltuiala)
	return cheltuielile_cautate

def test_cauta_cheltuieli_de_tip():
	apartamente = {}
	
	cheltuieli_apa = [creeaza_cheltuiala_azi(1, 'apa'), creeaza_cheltuiala_azi(10, 'apa'), creeaza_cheltuiala_azi(15, 'apa')]
	cheltuieli_gaz = [creeaza_cheltuiala_azi(100, 'gaz'), creeaza_cheltuiala_azi(5, 'gaz')]
	cheltuieli_canal = [creeaza_cheltuiala_azi(15, 'canal'), creeaza_cheltuiala_azi(999, 'canal')]
	cheltuieli_altele = [creeaza_cheltuiala_azi(1000, 'altele')]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli_apa[0])
	adauga_cheltuiala(apartamente, 1, cheltuieli_canal[0])
	adauga_cheltuiala(apartamente, 1, cheltuieli_gaz[0])
	adauga_cheltuiala(apartamente, 2, cheltuieli_apa[1])
	adauga_cheltuiala(apartamente, 2, cheltuieli_gaz[1])
	adauga_cheltuiala(apartamente, 10, cheltuieli_apa[2])
	adauga_cheltuiala(apartamente, 10, cheltuieli_canal[1])
	adauga_cheltuiala(apartamente, 10, cheltuieli_altele[0])
	
	def my_sorted(iterable):
		def my_key(a):
			return str(get_suma(a)) + get_tip(a)
		return sorted(iterable, key=my_key)
	
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'apa')) == my_sorted(cheltuieli_apa)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'gaz')) == my_sorted(cheltuieli_gaz)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'canal')) == my_sorted(cheltuieli_canal)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'altele')) == my_sorted(cheltuieli_altele)
	assert cauta_cheltuieli_de_tip(apartamente, 'incalzire') == []

''' RAPORTARE '''

def calculeaza_suma_totala_pe_tip(apartamente, tip):
	'''Calculeaza suma totala pentru un tip de cheltuiala.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuielile_cautate -- lista cu cheltuielile cautate
	'''
	suma_totala = 0
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if get_tip(cheltuiala) == tip:
				suma_totala += get_suma(cheltuiala)
	return suma_totala

def test_calculeaza_suma_totala_pe_tip():
	apartamente = {}
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(1, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(10, 'apa'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(15, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(15, 'canal'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(999, 'canal'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala_azi(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala_azi(5, 'gaz'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala_azi(1000, 'altele'))
	
	assert calculeaza_suma_totala_pe_tip(apartamente, 'apa') == 1+10+15
	assert calculeaza_suma_totala_pe_tip(apartamente, 'canal') == 15+999
	assert calculeaza_suma_totala_pe_tip(apartamente, 'gaz') == 100+5
	assert calculeaza_suma_totala_pe_tip(apartamente, 'altele') == 1000
	assert calculeaza_suma_totala_pe_tip(apartamente, 'incalzire') == 0

''' FILTRARE '''

def filtreaza_cheltuieli_diferite_de_tip(apartamente, tip):
	'''Returneaza toate cheltuielile diferite de tipul furnizat.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuielile_filtrate -- lista cu cheltuielile filtrate
	'''
	cheltuielile_filtrate = []
	for apartament in apartamente.values():
		for cheltuiala in apartament:
			if get_tip(cheltuiala) != tip:
				cheltuielile_filtrate.append(cheltuiala)
	return cheltuielile_filtrate

def test_filtreaza_cheltuieli_diferite_de_tip():
	apartamente = {}
	
	cheltuieli_apa = [creeaza_cheltuiala_azi(5, 'apa'), creeaza_cheltuiala_azi(15, 'apa')]
	cheltuieli_canal = [creeaza_cheltuiala_azi(20, 'canal')]
	cheltuieli_gaz = [creeaza_cheltuiala_azi(5, 'gaz'), creeaza_cheltuiala_azi(123, 'gaz')]
	cheltuieli_incalzire = [creeaza_cheltuiala_azi(777, 'incalzire'), creeaza_cheltuiala_azi(222, 'incalzire')]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli_apa[0])
	adauga_cheltuiala(apartamente, 1, cheltuieli_apa[1])
	adauga_cheltuiala(apartamente, 1, cheltuieli_canal[0])
	adauga_cheltuiala(apartamente, 2, cheltuieli_gaz[0])
	adauga_cheltuiala(apartamente, 3, cheltuieli_gaz[1])
	adauga_cheltuiala(apartamente, 12, cheltuieli_incalzire[0])
	adauga_cheltuiala(apartamente, 13, cheltuieli_incalzire[1])
	
	def my_sorted(iterable):
		def my_key(a):
			return str(get_suma(a)) + get_tip(a)
		return sorted(iterable, key=my_key)
	
	assert my_sorted(cheltuieli_canal+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'apa'))
	assert my_sorted(cheltuieli_apa+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'canal'))
	assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'gaz'))
	assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_gaz) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'incalzire'))

def filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, suma):
	'''Returneaza toate cheltuielile diferite de tipul furnizat.
	input: apartamente -- dictionar cu apartamente
	       suma -- float sau int
	output: cheltuielile_filtrate -- lista cu cheltuielile filtrate
	'''
	cheltuielile_filtrate = []
	for apartament in apartamente.values():
		for cheltuiala in apartament:
			if get_suma(cheltuiala) < suma:
				cheltuielile_filtrate.append(cheltuiala)
	return cheltuielile_filtrate

def test_filtreaza_cheltuieli_mai_mici_decat_suma():
	cheltuieli_sub_100 = [creeaza_cheltuiala_azi(5, 'apa'), creeaza_cheltuiala_azi(25, 'gaz'), creeaza_cheltuiala_azi(55, 'incalzire')]
	cheltuieli_sub_1000 = [creeaza_cheltuiala_azi(565, 'canal'), creeaza_cheltuiala_azi(465, 'incalzire'), creeaza_cheltuiala_azi(742, 'incalzire')]
	cheltuieli_sub_5000 = [creeaza_cheltuiala_azi(3468, 'gaz'), creeaza_cheltuiala_azi(2222, 'altele'), creeaza_cheltuiala_azi(2021, 'gaz')]
	
	apartamente = {}
	
	adauga_cheltuiala(apartamente, 1, cheltuieli_sub_100[0])
	adauga_cheltuiala(apartamente, 7, cheltuieli_sub_100[1])
	adauga_cheltuiala(apartamente, 3, cheltuieli_sub_100[2])
	adauga_cheltuiala(apartamente, 12, cheltuieli_sub_1000[0])
	adauga_cheltuiala(apartamente, 4, cheltuieli_sub_1000[1])
	adauga_cheltuiala(apartamente, 7, cheltuieli_sub_1000[2])
	adauga_cheltuiala(apartamente, 4, cheltuieli_sub_5000[0])
	adauga_cheltuiala(apartamente, 9, cheltuieli_sub_5000[1])
	adauga_cheltuiala(apartamente, 4, cheltuieli_sub_5000[2])
	
	def my_sorted(iterable):
		def my_key(a):
			return str(get_suma(a)) + get_tip(a)
		return sorted(iterable, key=my_key)
	
	assert my_sorted(cheltuieli_sub_100) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 100))
	assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 1000))
	assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000+cheltuieli_sub_5000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 5000))

def ruleaza_teste():
	test_creeaza_cheltuiala()
	test_set_suma()
	test_set_tip()
	test_set_data()
	
	test_adauga_cheltuiala()
	test_sterge_cheltuiala()
	
	test_sterge_cheltuieli_apartamente_consecutive()
	test_sterge_cheltuieli_dupa_tip()
	
	test_cauta_apartamente_cu_cheltuieli_mai_mari()
	test_cauta_cheltuieli_de_tip()
	
	test_calculeaza_suma_totala_pe_tip()
	
	test_filtreaza_cheltuieli_diferite_de_tip()
	test_filtreaza_cheltuieli_mai_mici_decat_suma()

ruleaza_teste()