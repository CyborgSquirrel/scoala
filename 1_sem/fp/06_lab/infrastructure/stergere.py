import domain.cheltuiala as ch
import domain.apartamente as ap

''' STERGERE '''

def sterge_cheltuieli_apartament(apartamente, operatii, indice_apartament):
	'''Sterge toate cheltuielile apartamentului aflat la indice_apartament.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_apartament -- int
	'''
	for i in reversed(range(len(apartamente[indice_apartament]))):
		ap.sterge_cheltuiala(apartamente, operatii, indice_apartament, i)

def sterge_cheltuieli_apartamente_consecutive(apartamente, operatii, indice_primul_apartament, indice_ultimul_apartament):
	'''Sterge toate cheltuielile apartamentelor, ale calor indice se afla intre indice_primul_apartament si indice_ultimul_apartament.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       indice_primul_apartament -- int
	       indice_ultimul_apartament -- int
	'''
	for i in range(indice_primul_apartament, indice_ultimul_apartament+1):
		try:
			for j in reversed(range(len(apartamente[i]))):
				ap.sterge_cheltuiala(apartamente, operatii, i, j)
		except KeyError:
			pass

def sterge_cheltuieli_dupa_tip(apartamente, operatii, tip):
	'''Sterge toate cheltuielile ale caror tip este egal cu tipul furnizat.
	input: apartamente -- dictionar cu apartamente
	       operatii -- lista de operatii
	       tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
	'''
	for indice in list(apartamente):
		apartament = apartamente[indice]
		i = 0
		while i < len(apartament):
			if ch.get_tip(apartament[i]) == tip:
				ap.sterge_cheltuiala(apartamente, operatii, indice, i)
			else:
				i += 1