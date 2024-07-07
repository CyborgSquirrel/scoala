import domain.cheltuiala as ch
import domain.apartamente as ap

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
			if ch.get_tip(cheltuiala) != tip:
				cheltuielile_filtrate.append(cheltuiala)
	return cheltuielile_filtrate

def filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, suma):
	'''Returneaza toate cheltuielile cu suma mai mica decat suma furnizata.
	input: apartamente -- dictionar cu apartamente
	       suma -- float sau int
	output: cheltuielile_filtrate -- lista cu cheltuielile filtrate
	'''
	cheltuielile_filtrate = []
	for apartament in apartamente.values():
		for cheltuiala in apartament:
			if ch.get_suma(cheltuiala) < suma:
				cheltuielile_filtrate.append(cheltuiala)
	return cheltuielile_filtrate