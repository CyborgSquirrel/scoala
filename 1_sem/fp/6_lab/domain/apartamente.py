import domain.cheltuiala as ch
from datetime import date

''' APARTAMENTE '''

''' OPERATII '''

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

def modifica_cheltuiala_suma(apartamente, operatii, indice_apartament, indice_cheltuiala, suma):
	'''Modifica suma unei cheltuieli din apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       indice_cheltuiala -- int
	       suma -- float sau int
	'''
	cheltuiala = apartamente[indice_apartament][indice_cheltuiala]
	operatii.append({"nume":"set_suma", "indice_apartament":indice_apartament, "indice_cheltuiala":indice_cheltuiala, "suma":ch.get_suma(cheltuiala)})
	ch.set_suma(cheltuiala, suma)

def modifica_cheltuiala_tip(apartamente, operatii, indice_apartament, indice_cheltuiala, tip):
	'''Modifica tipul unei cheltuieli din apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       indice_cheltuiala -- int
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	cheltuiala = apartamente[indice_apartament][indice_cheltuiala]
	operatii.append({"nume":"set_tip", "indice_apartament":indice_apartament, "indice_cheltuiala":indice_cheltuiala, "tip":ch.get_tip(cheltuiala)})
	ch.set_tip(cheltuiala, tip)

def modifica_cheltuiala_data(apartamente, operatii, indice_apartament, indice_cheltuiala, data):
	'''Modifica data unei cheltuieli din apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       indice_cheltuiala -- int
	       data -- date
	'''
	cheltuiala = apartamente[indice_apartament][indice_cheltuiala]
	operatii.append({"nume":"set_data", "indice_apartament":indice_apartament, "indice_cheltuiala":indice_cheltuiala, "data":ch.get_data(cheltuiala)})
	ch.set_data(cheltuiala, data)

def sterge_cheltuiala(apartamente, operatii, indice_apartament, indice_cheltuiala):
	'''Sterge o cheltuiala de la un apartament, din dictionarul de apartamente.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	       indice_cheltuiala -- int
	'''
	cheltuiala = apartamente[indice_apartament].pop(indice_cheltuiala)
	if len(apartamente[indice_apartament]) == 0:
		del apartamente[indice_apartament]
	operatii.append({"nume":"sterge", "indice_apartament":indice_apartament, "indice_cheltuiala":indice_cheltuiala, "cheltuiala":cheltuiala})

def inceput_operatie(operatii, text):
	'''Adauga inceputul unei operatii.
	input: operatii -- lista de operatii
	       text -- string
	'''
	operatii.append({"nume":"inceput", "text": text})

''' UNDO '''

def undo(apartamente, operatii):
	'''Reface ultima operatie.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	'''
	operatie = operatii.pop()
	while operatie["nume"] != "inceput":
		nume = operatie["nume"]
		
		indice_apartament = operatie["indice_apartament"]
		indice_cheltuiala = operatie["indice_cheltuiala"]
		if nume == "sterge":
			if not indice_apartament in apartamente:
				apartamente[indice_apartament] = []
			apartamente[indice_apartament].insert(indice_cheltuiala, operatie["cheltuiala"])
		else:
			apartament = apartamente[indice_apartament]
			
			if nume == "adauga":
				del apartament[indice_cheltuiala]
				if len(apartament) == 0:
					del apartamente[indice_apartament]
			else:
				cheltuiala = apartament[indice_cheltuiala]
				if nume == "set_suma":
					ch.set_suma(cheltuiala, operatie["suma"])
				elif nume == "set_tip":
					ch.set_tip(cheltuiala, operatie["tip"])
				elif nume == "set_data":
					ch.set_data(cheltuiala, operatie["data"])
		operatie = operatii.pop()
	return operatie["text"]