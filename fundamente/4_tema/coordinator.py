# https://docs.google.com/document/d/1EVePCa2MI6Y7PdsyDmHdHDaJtGRqTJTT6aIls84jwtk/edit?usp=sharing

from ui import meniu

apartamente = {}
operatii = []

# adauga cheltuiala -> indice apartament, indice cheltuiala
# set_suma -> indice apartament, indice cheltuiala, valoare precedenta
# set_tip -> indice apartament, indice cheltuiala, valoare precedenta
# set_data -> indice apartament, indice cheltuiala, valoare precedenta
# sterge cheltuiala -> indice apartament, indice cheltuiala, valoare

while True:
	print(apartamente)
	
	for i,v in enumerate(meniu):
		print(f"{i+1}. {v[1]}")
	
	alegere = input()
	try:
		meniu[int(alegere)-1][0](apartamente)
	except (ValueError, IndexError):
		eroare("Alegere invalida")
		continue