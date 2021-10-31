import domain.cheltuiala as ch
import domain.apartamente as ap

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
			if ch.get_suma(cheltuiala) > suma:
				apartamentele_cautate.append(indice)
				break
	return apartamentele_cautate

def cauta_cheltuieli_de_tip(apartamente, tip):
	'''Cauta toate apartamentele care au tipul egal cu tipul furnizat.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: cheltuielile_cautate -- lista cu cheltuielile cautate
	'''
	cheltuielile_cautate = []
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if ch.get_tip(cheltuiala) == tip:
				cheltuielile_cautate.append(cheltuiala)
	return cheltuielile_cautate

def cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma(apartamente, data, suma):
	'''Cauta toate cheltuielile efectuate inainte de data, mai mari decat suma.
	input: apartamente -- dictionar cu apartamente
	       data -- date
	       suma -- float sau int
	output: cheltuielile_cautate -- lista cu cheltuielile cautate
	'''
	cheltuielile_cautate = []
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if ch.get_data(cheltuiala) < data and ch.get_suma(cheltuiala) > suma:
				cheltuielile_cautate.append(cheltuiala)
	return cheltuielile_cautate