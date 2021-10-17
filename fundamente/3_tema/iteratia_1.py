# https://docs.google.com/document/d/1EVePCa2MI6Y7PdsyDmHdHDaJtGRqTJTT6aIls84jwtk/edit?usp=sharing

import math, collections

''' CHELTUIALA '''

def creeaza_cheltuiala(suma, tip):
	'''Creeaza o cheltuiala
	input: suma -- float sau int
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
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
	}

def get_suma(cheltuiala):
	'''Obtine suma unei cheltuieli
	input: cheltuiala -- cheltuiala
	output: suma -- float
	'''
	return cheltuiala["suma"]

def get_tip(cheltuiala):
	'''Obtine tipul unei cheltuieli
	input: cheltuiala -- cheltuiala
	output: tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	return cheltuiala["tip"]

def test_creeaza_cheltuiala():
	cheltuiala = creeaza_cheltuiala(123, "apa")
	assert get_suma(cheltuiala) == 123
	assert get_tip(cheltuiala) == "apa"
	
	cheltuiala = creeaza_cheltuiala(13.37, "canal")
	assert math.isclose(get_suma(cheltuiala), 13.37)
	assert get_tip(cheltuiala) == "canal"
	
	try:
		cheltuiala = creeaza_cheltuiala("7", "canal")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"
	
	try:
		cheltuiala = creeaza_cheltuiala(7, 0)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		cheltuiala = creeaza_cheltuiala(7, "caal")
		assert False
	except ValueError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"

def set_suma(cheltuiala, suma):
	'''Obtine suma unei cheltuieli
	input: cheltuiala -- cheltuiala
	       suma -- float sau int
	'''
	tip_suma = type(suma)
	if tip_suma not in [int, float]:
		raise TypeError(f"suma must be a float, or an int, not '{tip_suma.__name__}'")
	cheltuiala["suma"] = float(suma)

def test_set_suma():
	cheltuiala = creeaza_cheltuiala(12, "apa")
	
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
	'''Obtine suma unei cheltuieli
	input: cheltuiala -- cheltuiala
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	
	if type(tip) != str:
		raise TypeError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	elif tip not in ['apa', 'canal', 'incalzire', 'gaz', 'altele']:
		raise ValueError(f"tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'")
	
	cheltuiala["tip"] = tip

def test_set_tip():
	cheltuiala = creeaza_cheltuiala(83, "apa")
	
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

test_creeaza_cheltuiala()
test_set_suma()
test_set_tip()

''' APARTAMENTE '''

def adauga_cheltuiala(apartamente, indice_apartament, cheltuiala):
	'''Adauga cheltuiala la un apartament, din dictionarul de apartamente.
	input: apartamente -- dictionar cu apartamente
	       indice_apartament -- int
	       cheltuiala -- cheltuiala
	'''
	if not indice_apartament in apartamente:
		apartamente[indice_apartament] = []
	apartamente[indice_apartament].append(cheltuiala)

def test_adauga_cheltuiala():
	apartamente = {}
	
	cheltuieli = [
		creeaza_cheltuiala(6.5756, "gaz"),
		creeaza_cheltuiala(456, "apa"),
		creeaza_cheltuiala(0.0003, "altele"),
		creeaza_cheltuiala(45646, "canal"),
		creeaza_cheltuiala(76557, "incalzire"),
	]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli[0])
	
	assert apartamente[1][0] == cheltuieli[0]
	
	adauga_cheltuiala(apartamente, 2, cheltuieli[1])
	adauga_cheltuiala(apartamente, 2, cheltuieli[2])
	adauga_cheltuiala(apartamente, 2, cheltuieli[3])
	
	assert apartamente[2] == [cheltuieli[1], cheltuieli[2], cheltuieli[3]]
	
	adauga_cheltuiala(apartamente, 1, cheltuieli[4])
	
	assert apartamente[1][1] == cheltuieli[4]

test_adauga_cheltuiala()

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
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 4, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 100, creeaza_cheltuiala(100, 'apa'))
	
	sterge_cheltuieli_apartamente_consecutive(apartamente, 2, 3)
	
	assert len(apartamente) == 3
	
	assert 1 in apartamente
	assert not 2 in apartamente
	assert not 3 in apartamente
	assert 4 in apartamente
	assert 100 in apartamente

test_sterge_cheltuieli_apartamente_consecutive()

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
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala(100, 'canal'))
	adauga_cheltuiala(apartamente, 3, creeaza_cheltuiala(100, 'altele'))
	adauga_cheltuiala(apartamente, 4, creeaza_cheltuiala(100, 'apa'))
	adauga_cheltuiala(apartamente, 100, creeaza_cheltuiala(100, 'gaz'))
	adauga_cheltuiala(apartamente, 101, creeaza_cheltuiala(100, 'apa'))
	
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

test_sterge_cheltuieli_dupa_tip()

def cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, suma):
	'''Cauta toate apartamentele care au cheltuieli mai mari decat suma furnizata.
	input: apartamente -- dictionar cu apartamente
	       suma -- int
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
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(1, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(15, 'canal'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(10, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(5, 'gaz'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(15, 'apa'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(999, 'canal'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(1000, 'altele'))
	
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

test_cauta_apartamente_cu_cheltuieli_mai_mari()

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
	
	cheltuieli_apa = [creeaza_cheltuiala(1, 'apa'), creeaza_cheltuiala(10, 'apa'), creeaza_cheltuiala(15, 'apa')]
	cheltuieli_gaz = [creeaza_cheltuiala(100, 'gaz'), creeaza_cheltuiala(5, 'gaz')]
	cheltuieli_canal = [creeaza_cheltuiala(15, 'canal'), creeaza_cheltuiala(999, 'canal')]
	cheltuieli_altele = [creeaza_cheltuiala(1000, 'altele')]
	
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

test_cauta_cheltuieli_de_tip()

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
	
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(1, 'apa'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(15, 'canal'))
	adauga_cheltuiala(apartamente, 1, creeaza_cheltuiala(100, 'gaz'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(10, 'apa'))
	adauga_cheltuiala(apartamente, 2, creeaza_cheltuiala(5, 'gaz'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(15, 'apa'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(999, 'canal'))
	adauga_cheltuiala(apartamente, 10, creeaza_cheltuiala(1000, 'altele'))
	
	assert calculeaza_suma_totala_pe_tip(apartamente, 'apa') == 1+10+15
	assert calculeaza_suma_totala_pe_tip(apartamente, 'canal') == 15+999
	assert calculeaza_suma_totala_pe_tip(apartamente, 'gaz') == 5+100
	assert calculeaza_suma_totala_pe_tip(apartamente, 'altele') == 1000
	assert calculeaza_suma_totala_pe_tip(apartamente, 'incalzire') == 0

test_calculeaza_suma_totala_pe_tip()

''' INTERFATA '''

def eroare(mesaj):
	print(f"Eroare: {mesaj}")

def hint(mesaj):
	print(f"Hint: {mesaj}")

def valideaza_suma(suma):
	try:
		return float(suma)
	except (TypeError, ValueError):
		eroare("Valoare invalida suma")
		return None

def valideaza_tip(tip):
	if tip in ['apa', 'canal', 'incalzire', 'gaz', 'altele']:
		return tip
	else:
		eroare("Valoare invalida tip")
		return None

def mesaj_tip():
	hint("tip poate fi una dintre 'apa', 'canal', 'incalzire', 'gaz', 'altele'")

def mesaj_indice_apartament(apartamente):
	hint(f"indice apartament poate fi unul dintre: {list(apartamente.keys())}")

def mesaj_indice_cheltuiala(apartament):
	hint(f"indice cheltuiala poate fi in intervalul [0;{len(apartament)-1}]")

def ui_adauga_cheltuiala(apartamente):
	indice_apartament = input("indice apartament = ")
	try:
		indice_apartament = int(indice_apartament)
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	
	suma = valideaza_suma(input("suma = "))
	if not suma: return
	
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if not tip: return
	
	adauga_cheltuiala(apartamente, indice_apartament, creeaza_cheltuiala(suma, tip))

def ui_modifica_cheltuiala(apartamente):
	mesaj_indice_apartament(apartamente)
	indice_apartament = input("indice apartament = ")
	try:
		apartament = apartamente[int(indice_apartament)]
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	except KeyError:
		eroare("Indice apartament invalid")
		return
	
	mesaj_indice_cheltuiala(apartament)
	indice_cheltuiala = input("indice cheltuiala = ")
	try:
		cheltuiala = apartament[int(indice_cheltuiala)]
	except ValueError:
		eroare("Valoare invalida indice cheltuiala")
		return
	except IndexError:
		eroare("Indice cheltuiala invalid")
		return
	
	suma = input(f"suma (daca nu introduceti nimic ramane {get_suma(cheltuiala)}) = ")
	if suma != "":
		suma = valideaza_suma(suma)
		if not suma: return
		set_suma(cheltuiala, suma)
	
	mesaj_tip()
	tip = input(f"tip (daca nu introduceti nimic ramane '{get_tip(cheltuiala)}') = ")
	if tip != "":
		tip = valideaza_tip(tip)
		if not tip: return
		set_tip(cheltuiala, tip)

def ui_sterge_cheltuieli_apartament(apartamente):
	mesaj_indice_apartament(apartamente)
	indice_apartament = input("indice apartament = ")
	try:
		del apartamente[int(indice_apartament)]
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	except KeyError:
		eroare("Indice apartament invalid")
		return

def ui_sterge_cheltuieli_apartamente_consecutive(apartamente):
	indice_primul_apartament = input("indice primul apartament = ")
	try:
		indice_primul_apartament = int(indice_primul_apartament)
	except ValueError:
		eroare("Valoare invalida indice primul apartament")
		return
	
	indice_ultimul_apartament = input("indice ultimul apartament = ")
	try:
		indice_ultimul_apartament = int(indice_ultimul_apartament)
	except ValueError:
		eroare("Valoare invalida indice ultimul apartament")
		return
	
	if indice_primul_apartament > indice_ultimul_apartament:
		eroare("Indicele primului apartament este mai mare decat indicele ultimului apartament")
		return
	
	sterge_cheltuieli_apartamente_consecutive(apartamente, indice_primul_apartament, indice_ultimul_apartament)

def ui_sterge_cheltuieli_dupa_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if not tip: return
	
	sterge_cheltuieli_dupa_tip(apartamente, tip)

def ui_cauta_apartamente_cu_cheltuieli_mai_mari(apartamente):
	suma = valideaza_suma(input("suma = "))
	if not suma: return
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, suma)
	
	print(apartamentele_cautate)

def ui_cauta_cheltuieli_de_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if not tip: return
	
	cheltuielile_cautate = cauta_cheltuieli_de_tip(apartamente, tip)
	
	print(cheltuielile_cautate)

def ui_calculeaza_suma_totala_pe_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if not tip: return
	
	suma_totala = calculeaza_suma_totala_pe_tip(apartamente, tip)
	
	print(suma_totala)

meniu = [
	# Adaugare
	(ui_adauga_cheltuiala, "Adauga cheltuiala"),
	(ui_modifica_cheltuiala, "Modifica cheltuiala"),
	# Stergere
	(ui_sterge_cheltuieli_apartament, "Sterge toate cheltuielile unui apartament"),
	(ui_sterge_cheltuieli_apartamente_consecutive, "Sterge cheltuielile de la apartamente consecutive"),
	(ui_sterge_cheltuieli_dupa_tip, "Sterge cheltuielile de un anumit tip de la toate apartamentele"),
	# Cautare
	(ui_cauta_apartamente_cu_cheltuieli_mai_mari, "Tipareste toate apartamentele care au cheltuielile mai mari decat o suma"),
	(ui_cauta_cheltuieli_de_tip, "Tipareste cheltuielile de un anumit tip de la toate apartamentele"),
	# Raportare
	(ui_calculeaza_suma_totala_pe_tip, "Tipareste suma totala pentru un tip de cheltuiala"),
]

# Tipărește toate cheltuielile efectuate înainte de o zi și mai mari decât o sumă (se dă suma și ziua)
# Intrebare: trebuie sa retinem si ziua intr-o cheltuiala?
# In specificatie zice ca o cheltuiala este suma si tipul cheltuielii.

apartamente = {}
# apartamente = {1: [{'suma': 1231.0, 'tip': 'apa'}, {'suma': 4343.0, 'tip': 'gaz'}], 4: [{'suma': 143123.0, 'tip': 'apa'}, {'suma': 123.0, 'tip': 'incalzire'}, {'suma': 14.0, 'tip': 'apa'}], 100: [{'suma': 3434.0, 'tip': 'canal'}]}

while True:
	# print(apartamente)
	for i,v in enumerate(meniu):
		print(f"{i+1}. {v[1]}")
	
	alegere = input()
	try:
		meniu[int(alegere)-1][0](apartamente)
	except (ValueError, IndexError):
		eroare("Alegere invalida")
		continue