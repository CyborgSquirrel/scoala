import domain.apartamente as ap
import domain.cheltuiala as ch
import infrastructure as ir
from datetime import date

''' INTERFATA '''

''' FUNCTII UTILE '''

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

''' FUNCTII MENIU '''

def afiseaza_tot(apartamente, operatii):
	print(apartamente)

def adauga_cheltuiala(apartamente, operatii):
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
	
	ap.inceput_operatie(operatii, "adauga cheltuiala")
	cheltuiala = ch.creeaza(suma, tip, data)
	ap.adauga_cheltuiala(apartamente, operatii, indice_apartament, cheltuiala)
	
	print(f"Cheltuiala {cheltuiala} a fost adaugata")

def modifica_cheltuiala(apartamente, operatii):
	mesaj_indice_apartament(apartamente)
	indice_apartament = input("indice apartament = ")
	try:
		indice_apartament = int(indice_apartament)
		apartament = apartamente[indice_apartament]
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	except KeyError:
		eroare("Indice apartament invalid")
		return
	
	mesaj_indice_cheltuiala(apartament)
	indice_cheltuiala = input("indice cheltuiala = ")
	try:
		indice_cheltuiala = int(indice_cheltuiala)
		cheltuiala = apartament[indice_cheltuiala]
	except ValueError:
		eroare("Valoare invalida indice cheltuiala")
		return
	except IndexError:
		eroare("Indice cheltuiala invalid")
		return
		
	ap.inceput_operatie(operatii, "modifica cheltuiala")
	
	suma = input(f"suma (daca nu introduceti nimic ramane {ch.get_suma(cheltuiala)}) = ")
	if suma != "":
		suma = valideaza_suma(suma)
		if suma is None: return
		ap.modifica_cheltuiala_suma(apartamente, operatii, indice_apartament, indice_cheltuiala, suma)
	
	mesaj_tip()
	tip = input(f"tip (daca nu introduceti nimic ramane '{ch.get_tip(cheltuiala)}') = ")
	if tip != "":
		tip = valideaza_tip(tip)
		if tip is None: return
		ap.modifica_cheltuiala_tip(apartamente, operatii, indice_apartament, indice_cheltuiala, tip)
	
	mesaj_data()
	data = input(f"data (daca nu introduceti nimic ramane {ch.get_data(cheltuiala)}) = ")
	if data != "":
		data = valideaza_data(data)
		if data is None: return
		ap.modifica_cheltuiala_data(apartamente, operatii, indice_apartament, indice_cheltuiala, data)
		
	print(f"Cheltuiala {cheltuiala} a fost modificata")

def sterge_cheltuieli_apartament(apartamente, operatii):
	mesaj_indice_apartament(apartamente)
	indice_apartament = input("indice apartament = ")
	try:
		indice_apartament = int(indice_apartament)
		apartamente[indice_apartament]
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	except KeyError:
		eroare("Indice apartament invalid")
		return
	
	ap.inceput_operatie(operatii, "sterge cheltuieli apartament")
	ir.sterge_cheltuieli_apartament(apartamente, operatii, indice_apartament)
	
	print(f"Cheltuielile apartamentului {indice_apartament} au fost sterse")

def sterge_cheltuieli_apartamente_consecutive(apartamente, operatii):
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
	
	ap.inceput_operatie(operatii, "sterge cheltuieli apartamente consecutive")
	ir.sterge_cheltuieli_apartamente_consecutive(apartamente, operatii, indice_primul_apartament, indice_ultimul_apartament)
	
	print(f"Cheltuielile tuturor apartamentelor intre {indice_primul_apartament} si {indice_ultimul_apartament} au fost sterse")

def sterge_cheltuieli_dupa_tip(apartamente, operatii):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	ap.inceput_operatie(operatii, "sterge cheltuieli dupa tip")
	ir.sterge_cheltuieli_dupa_tip(apartamente, operatii, tip)
	
	print(f"Cheltuielile de tip '{tip}' au fost sterse")

def cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, operatii):
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	apartamentele_cautate = ir.cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, suma)
	
	print(f"Apartamentele cautate sunt: {apartamentele_cautate}")

def cauta_cheltuieli_de_tip(apartamente, operatii):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	cheltuielile_cautate = ir.cauta_cheltuieli_de_tip(apartamente, tip)
	
	print(f"Cheltuielile cautate sunt: {cheltuielile_cautate}")

def cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma(apartamente, operatii):
	data = valideaza_data(input("data = "))
	if data is None: return
	
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	cheltuielile_cautate = ir.cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma(apartamente, data, suma)
	
	print(f"Cheltuielile cautate sunt: {cheltuielile_cautate}")

def calculeaza_suma_totala_pe_tip(apartamente, operatii):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	suma_totala = ir.calculeaza_suma_totala_pe_tip(apartamente, tip)
	
	print(f"Suma totala pe tipul '{tip}' este: {suma_totala}")

def sorteaza_apartamentele_dupa_suma_pe_tip(apartamente, operatii):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	apartamentele_sortate = ir.sorteaza_apartamentele_dupa_suma_pe_tip(apartamente, tip)
	
	print(f"Apartamentele sortate sunt: {apartamentele_sortate}")

def calculeaza_suma_totala_pe_apartament(apartamente, operatii):
	mesaj_indice_apartament(apartamente)
	indice_apartament = input("indice apartament = ")
	try:
		indice_apartament = int(indice_apartament)
		apartamente[indice_apartament]
	except ValueError:
		eroare("Valoare invalida indice apartament")
		return
	except KeyError:
		eroare("Indice apartament invalid")
		return
	
	suma_totala = ir.calculeaza_suma_totala_pe_apartament(apartamente, indice_apartament)
	
	print(f"Suma totala a cheltuielilor la apartamentul {indice_apartament} este: {suma_totala}")

def filtreaza_cheltuieli_diferite_de_tip(apartamente, operatii):
	mesaj_tip()
	tip = valideaza_tip(input("tip = "))
	if tip is None: return
	
	cheltuielile_filtrate = ir.filtreaza_cheltuieli_diferite_de_tip(apartamente, tip)
	
	print(f"Cheltuielile filtrate sunt: {cheltuielile_filtrate}")

def filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, operatii):
	suma = valideaza_suma(input("suma = "))
	if suma is None: return
	
	cheltuielile_filtrate = ir.filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, suma)
	
	print(f"Cheltuielile mai mici decat suma sunt: {cheltuielile_filtrate}")

def undo(apartamente, operatii):
	if len(operatii) == 0:
		eroare("Nu mai sunt operatii care pot fi date inapoi")
		return
	
	text = ap.undo(apartamente, operatii)
	print(f"Ultima operatie ({text}) a fost refacuta")

date_meniu = [
	"Adaugare",
	(adauga_cheltuiala, "Adauga cheltuiala"),
	(modifica_cheltuiala, "Modifica cheltuiala"),
	"Stergere",
	(sterge_cheltuieli_apartament, "Sterge toate cheltuielile unui apartament"),
	(sterge_cheltuieli_apartamente_consecutive, "Sterge cheltuielile de la apartamente consecutive"),
	(sterge_cheltuieli_dupa_tip, "Sterge cheltuielile de un anumit tip de la toate apartamentele"),
	"Cautare",
	(cauta_apartamente_cu_cheltuieli_mai_mari, "Tipareste toate apartamentele care au cheltuielile mai mari decat o suma"),
	(cauta_cheltuieli_de_tip, "Tipareste cheltuielile de un anumit tip de la toate apartamentele"),
	(cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma, "Cauta cheltuieli efectuate inainte de o zi si mai mari decat o suma"),
	"Raportare",
	(afiseaza_tot, "Tipareste toate cheltuielile de la toate apartamentele"),
	(calculeaza_suma_totala_pe_tip, "Tipareste suma totala pentru un tip de cheltuiala"),
	(sorteaza_apartamentele_dupa_suma_pe_tip, "Tipareste toate apartamentele sortate dupa un tip de cheltuiala"),
	(calculeaza_suma_totala_pe_apartament, "Tipareste totalul de cheltuieli pentru un apartament dat"),
	"Filtrare",
	(filtreaza_cheltuieli_diferite_de_tip, "Filtreaza cheltuielile cu tip diferit"),
	(filtreaza_cheltuieli_mai_mici_decat_suma, "Filtreaza cheltuielile cu suma mai mica"),
	"Undo",
	(undo, "Undo"),
]

def creeaza_meniu(date_meniu):
	meniu = {}
	
	indice_1 = 0
	indice_2 = 0
	for data in date_meniu:
		if type(data) == str:
			indice_1 += 1
			indice_2 = 0
			meniu[f"{indice_1}"] = (None, data)
		elif type(data) == tuple:
			indice_2 += 1
			assert callable(data[0])
			assert type(data[1]) == str
			meniu[f"{indice_1}.{indice_2}"] = (data[0], data[1])
	
	return meniu

meniu = creeaza_meniu(date_meniu)