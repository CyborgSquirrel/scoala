import domain as dm
from datetime import date

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

def valideaza_data(data):
	try:
		return date.fromisoformat(data)
	except (TypeError, ValueError):
		eroare("Valoare invalida data")
		return None

def mesaj_tip():
	hint("tip poate fi una dintre 'apa', 'canal', 'incalzire', 'gaz', 'altele'")

def mesaj_data():
	hint("data se da in formatul YYYY-MM-DD")

def mesaj_indice_apartament(apartamente):
	hint(f"indice apartament poate fi unul dintre: {list(apartamente.keys())}")

def mesaj_indice_cheltuiala(apartament):
	hint(f"indice cheltuiala poate fi in intervalul [0;{len(apartament)-1}]")

def adauga_cheltuiala(apartamente):
	indice_apartament = input("indice apartament = ")
	try:
		indice_apartament = int(indice_apartament)
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	mesaj_data()
	azi = date.today()
	data = input(f"data (daca nu introduceti nimic va fi data de azi {azi}) = ")
	if data == "":
		data = azi
	else:
		data = valideaza_data(data)
	
	dm.adauga_cheltuiala(apartamente, indice_apartament, dm.creeaza_cheltuiala(suma, tip, data))

def modifica_cheltuiala(apartamente):
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
	
	suma = input(f"suma (daca nu introduceti nimic ramane {dm.get_suma(cheltuiala)}) = ")
	if suma != "":
		suma = valideaza_suma(suma)
		if suma is None: return
		dm.set_suma(cheltuiala, suma)
	
	mesaj_tip()
	tip = input(f"tip (daca nu introduceti nimic ramane '{dm.get_tip(cheltuiala)}') = ")
	if tip != "":
		tip = valideaza_tip(tip)
		if tip is None: return
		dm.set_tip(cheltuiala, tip)
	
	mesaj_data()
	data = input(f"data (daca nu introduceti nimic ramane {dm.get_data(cheltuiala)}) = ")
	if data != "":
		data = valideaza_data(data)
		if data is None: return
		dm.set_data(cheltuiala, data)

def sterge_cheltuieli_apartament(apartamente):
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

def sterge_cheltuieli_apartamente_consecutive(apartamente):
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
	
	dm.sterge_cheltuieli_apartamente_consecutive(apartamente, indice_primul_apartament, indice_ultimul_apartament)

def sterge_cheltuieli_dupa_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	dm.sterge_cheltuieli_dupa_tip(apartamente, tip)

def cauta_apartamente_cu_cheltuieli_mai_mari(apartamente):
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	apartamentele_cautate = dm.cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, suma)
	
	print(apartamentele_cautate)

def cauta_cheltuieli_de_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	cheltuielile_cautate = dm.cauta_cheltuieli_de_tip(apartamente, tip)
	
	print(cheltuielile_cautate)

def calculeaza_suma_totala_pe_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	suma_totala = dm.calculeaza_suma_totala_pe_tip(apartamente, tip)
	
	print(suma_totala)

def filtreaza_cheltuieli_diferite_de_tip(apartamente):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	cheltuielile_filtrate = dm.filtreaza_cheltuieli_diferite_de_tip(apartamente, tip)
	
	print(cheltuielile_filtrate)

def filtreaza_cheltuieli_mai_mici_decat_suma(apartamente):
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	cheltuielile_filtrate = dm.filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, suma)
	
	print(cheltuielile_filtrate)

meniu = [
	# Adaugare
	(adauga_cheltuiala, "Adauga cheltuiala"),
	(modifica_cheltuiala, "Modifica cheltuiala"),
	# Stergere
	(sterge_cheltuieli_apartament, "Sterge toate cheltuielile unui apartament"),
	(sterge_cheltuieli_apartamente_consecutive, "Sterge cheltuielile de la apartamente consecutive"),
	(sterge_cheltuieli_dupa_tip, "Sterge cheltuielile de un anumit tip de la toate apartamentele"),
	# Cautare
	(cauta_apartamente_cu_cheltuieli_mai_mari, "Tipareste toate apartamentele care au cheltuielile mai mari decat o suma"),
	(cauta_cheltuieli_de_tip, "Tipareste cheltuielile de un anumit tip de la toate apartamentele"),
	# Raportare
	(calculeaza_suma_totala_pe_tip, "Tipareste suma totala pentru un tip de cheltuiala"),
	# Filtrare
	(filtreaza_cheltuieli_diferite_de_tip, "Filtreaza cheltuielile cu tip diferit"),
	(filtreaza_cheltuieli_mai_mici_decat_suma, "Filtreaza cheltuielile cu suma mai mica"),
]