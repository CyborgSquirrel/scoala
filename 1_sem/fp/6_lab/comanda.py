from ui import eroare
from ui import valideaza_suma, valideaza_tip, valideaza_data

import domain.apartamente as ap
import domain.cheltuiala as ch
import infrastructure as ir

''' COMANDA '''

def arg_next(arg):
	try:
		v = arg.pop(0)
		return v
	except IndexError:
		eroare("Prea putine argumente")
		return None

def arg_done(arg):
	if len(arg) != 0:
		eroare("Prea multe argumente")
		return False
	else:
		return True

def executa_comanda(comanda, arg, apartamente, operatii):
	if comanda == "add":
		indice_apartament = arg_next(arg)
		try:
			indice_apartament = int(indice_apartament)
		except (ValueError, TypeError):
			eroare("Valoare invalida indice apartament")
			return
		
		suma = valideaza_suma(arg_next(arg))
		if suma is None: return
		
		tip = valideaza_tip(arg_next(arg))
		if tip is None: return
		
		data = valideaza_data(arg_next(arg))
		if data is None: return
		
		if not arg_done(arg): return
		
		cheltuiala = ch.creeaza(suma, tip, data)
		ap.inceput_operatie(operatii, f"adauga cheltuiala {cheltuiala}")
		ap.adauga_cheltuiala(apartamente, operatii, indice_apartament, cheltuiala)
	
	elif comanda == "mod":
		indice_apartament = arg_next(arg)
		try:
			indice_apartament = int(indice_apartament)
			apartament = apartamente[indice_apartament]
		except (ValueError, TypeError):
			eroare("Valoare invalida indice apartament")
			return
		except KeyError:
			eroare("Indice apartament invalid")
			return
		
		indice_cheltuiala = arg_next(arg)
		try:
			indice_cheltuiala = int(indice_cheltuiala)
			cheltuiala = apartament[indice_cheltuiala]
		except (ValueError, TypeError):
			eroare("Valoare invalida indice cheltuiala")
			return
		except IndexError:
			eroare("Indice cheltuiala invalid")
			return
		
		ap.inceput_operatie(operatii, "modifica cheltuiala")
		
		suma = arg_next(arg)
		tip = arg_next(arg)
		data = arg_next(arg)
		
		if not arg_done(arg): return
		
		if suma != "-":
			suma = valideaza_suma(suma)
			if suma is None: return
			ap.modifica_cheltuiala_suma(apartamente, operatii, indice_apartament, indice_cheltuiala, suma)
		
		if tip != "-":
			tip = valideaza_tip(tip)
			if tip is None: return
			ap.modifica_cheltuiala_tip(apartamente, operatii, indice_apartament, indice_cheltuiala, tip)
		
		if data != "-":
			data = valideaza_data(data)
			if data is None: return
			ap.modifica_cheltuiala_data(apartamente, operatii, indice_apartament, indice_cheltuiala, data)
		
	elif comanda == "erase":
		erase_tip = arg_next(arg)
		if erase_tip == "apartment":
			indice_apartament = arg_next(arg)
			try:
				indice_apartament = int(indice_apartament)
				apartamente[indice_apartament]
			except (ValueError, TypeError):
				eroare("Valoare invalida indice apartament")
				return
			except KeyError:
				eroare("Indice apartament invalid")
				return
			
			if not arg_done(arg): return
			
			ap.inceput_operatie(operatii, f"sterge cheltuielile apartamentului {indice_apartament}")
			ir.sterge_cheltuieli_apartament(apartamente, operatii, indice_apartament)
		
	elif comanda == "report":
		report_tip = arg_next(arg)
		if report_tip == "type_sum":
			tip = valideaza_tip(arg_next(arg))
			if tip is None: return
			
			if not arg_done(arg): return
			
			suma_totala = ir.calculeaza_suma_totala_pe_tip(apartamente, tip)
			
			print(suma_totala)
	
	elif comanda == "undo":
		if not arg_done(arg): return
		
		text = ap.undo(apartamente, operatii)
		print(f"Ultima operatie ({text}) a fost refacuta")
		
	elif comanda == "print":
		if not arg_done(arg): return
		
		print(apartamente)
	
	else:
		eroare("Comanda invalida")