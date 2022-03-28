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
