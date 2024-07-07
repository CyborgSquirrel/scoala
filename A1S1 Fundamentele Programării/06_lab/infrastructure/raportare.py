import domain.cheltuiala as ch
import domain.apartamente as ap

''' RAPORTARE '''

def calculeaza_suma_totala_pe_tip(apartamente, tip):
	'''Calculeaza suma totala pentru un tip de cheltuiala.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: suma_totala -- float
	'''
	suma_totala = 0
	for indice,apartament in apartamente.items():
		for cheltuiala in apartament:
			if ch.get_tip(cheltuiala) == tip:
				suma_totala += ch.get_suma(cheltuiala)
	return suma_totala

def sorteaza_apartamentele_dupa_suma_pe_tip(apartamente, tip):
	'''Sorteaza apartamentele dupa suma pe tipul furnizat de cheltuiala.
	input: apartamente -- dictionar cu apartamente
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	output: apartamentele_sortate -- lista cu apartamente
	'''
	suma_pe_tip = {}
	for indice,apartament in apartamente.items():
		suma_pe_tip[indice] = 0
		for cheltuiala in apartament:
			if ch.get_tip(cheltuiala) == tip:
				suma_pe_tip[indice] += ch.get_suma(cheltuiala)
	
	def my_key(a):
		return suma_pe_tip[a]
	
	apartamentele_sortate = sorted(
		list(apartamente.keys()),
		key=my_key, reverse=True
	)
	return apartamentele_sortate

def calculeaza_suma_totala_pe_apartament(apartamente, indice_apartament):
	'''Calculeaza suma totala pentru un tip de cheltuiala.
	input: apartamente -- dictionar cu apartamente
	       indice_apartament -- int
	output: suma_totala -- float
	'''
	suma_totala = 0
	for cheltuiala in apartamente[indice_apartament]:
		suma_totala += ch.get_suma(cheltuiala)
	return suma_totala