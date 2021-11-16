import domain.cheltuiala as ch
import domain.apartamente as ap

from datetime import date, timedelta
import math

def my_sorted(iterable):
	def my_key(a):
		return str(a)
	return sorted(iterable, key=my_key)

from .stergere import *
''' STERGERE '''

def test_sterge_cheltuieli_apartament():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
	
	sterge_cheltuieli_apartament(apartamente, operatii, 1)
	assert not 1 in apartamente

def test_sterge_cheltuieli_apartamente_consecutive():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(100, 'apa'))
	
	sterge_cheltuieli_apartamente_consecutive(apartamente, operatii, 2, 3)
	
	assert len(apartamente) == 3
	
	assert 1 in apartamente
	assert not 2 in apartamente
	assert not 3 in apartamente
	assert 4 in apartamente
	assert 100 in apartamente

def test_sterge_cheltuieli_dupa_tip():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(100, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 101, ch.creeaza_azi(100, 'apa'))
	
	sterge_cheltuieli_dupa_tip(apartamente, operatii, "incalzire")
	
	assert 1 in apartamente and len(apartamente[1]) == 3
	assert 2 in apartamente and len(apartamente[2]) == 2
	assert 3 in apartamente and len(apartamente[3]) == 3
	assert 4 in apartamente and len(apartamente[4]) == 1
	assert 100 in apartamente and len(apartamente[100]) == 1
	assert 101 in apartamente and len(apartamente[101]) == 1
	
	sterge_cheltuieli_dupa_tip(apartamente, operatii, "apa")
	
	assert 1 in apartamente and len(apartamente[1]) == 1
	assert 2 not in apartamente
	assert 3 in apartamente and len(apartamente[3]) == 2
	assert not 4 in apartamente
	assert 100 in apartamente and len(apartamente[100]) == 1
	assert not 101 in apartamente

from .cautare import *
''' CAUTARE '''

def test_cauta_apartamente_cu_cheltuieli_mai_mari():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(15, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(10, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(5, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(15, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(999, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(1000, 'altele'))
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 0)
	assert apartamentele_cautate == [1, 2, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 10)
	assert apartamentele_cautate == [1, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 99)
	assert apartamentele_cautate == [1, 10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 999)
	assert apartamentele_cautate == [10]
	
	apartamentele_cautate = cauta_apartamente_cu_cheltuieli_mai_mari(apartamente, 1000)
	assert apartamentele_cautate == []

def test_cauta_cheltuieli_de_tip():
	apartamente = {}
	operatii = []
	
	cheltuieli_apa = [ch.creeaza_azi(1, 'apa'), ch.creeaza_azi(10, 'apa'), ch.creeaza_azi(15, 'apa')]
	cheltuieli_gaz = [ch.creeaza_azi(100, 'gaz'), ch.creeaza_azi(5, 'gaz')]
	cheltuieli_canal = [ch.creeaza_azi(15, 'canal'), ch.creeaza_azi(999, 'canal')]
	cheltuieli_altele = [ch.creeaza_azi(1000, 'altele')]
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[0])
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_canal[0])
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_gaz[0])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_apa[1])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_gaz[1])
	ap.adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_apa[2])
	ap.adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_canal[1])
	ap.adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_altele[0])
	
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'apa')) == my_sorted(cheltuieli_apa)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'gaz')) == my_sorted(cheltuieli_gaz)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'canal')) == my_sorted(cheltuieli_canal)
	assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'altele')) == my_sorted(cheltuieli_altele)
	assert cauta_cheltuieli_de_tip(apartamente, 'incalzire') == []

def test_cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma():
	apartamente = {}
	operatii = []
	
	data = date(2021, 9, 17)
	suma = 150
	cheltuieli_da = [
		ch.creeaza(suma+563, "apa", data-timedelta(days=3)),
		ch.creeaza(suma+6, "apa", data-timedelta(days=7)),
		ch.creeaza(suma+12, "apa", data-timedelta(days=2)),
		ch.creeaza(suma+64, "apa", data-timedelta(days=1)),
		ch.creeaza(suma+23, "apa", data-timedelta(days=36)),
	]
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_da[0])
	ap.adauga_cheltuiala(apartamente, operatii, 15, cheltuieli_da[1])
	ap.adauga_cheltuiala(apartamente, operatii, 53, cheltuieli_da[2])
	ap.adauga_cheltuiala(apartamente, operatii, 53, cheltuieli_da[3])
	ap.adauga_cheltuiala(apartamente, operatii, 234, cheltuieli_da[4])
	
	cheltuieli_nu = [
		ch.creeaza(suma-342, "apa", data+timedelta(days=5)),
		ch.creeaza(suma-531, "apa", data+timedelta(days=0)),
		ch.creeaza(suma-43, "apa", data+timedelta(days=2)),
		ch.creeaza(suma-32, "apa", data+timedelta(days=343)),
		ch.creeaza(suma-56, "apa", data+timedelta(days=32)),
	]
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_nu[0])
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_nu[1])
	ap.adauga_cheltuiala(apartamente, operatii, 15, cheltuieli_nu[2])
	ap.adauga_cheltuiala(apartamente, operatii, 23, cheltuieli_nu[3])
	ap.adauga_cheltuiala(apartamente, operatii, 13, cheltuieli_nu[4])
	
	assert my_sorted(cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma(apartamente, data, suma)) \
	    == my_sorted(cheltuieli_da)

from .raportare import *
''' RAPORTARE '''

def test_calculeaza_suma_totala_pe_tip():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(10, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(15, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(15, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(999, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(5, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(1000, 'altele'))
	
	assert calculeaza_suma_totala_pe_tip(apartamente, 'apa') == 1+10+15
	assert calculeaza_suma_totala_pe_tip(apartamente, 'canal') == 15+999
	assert calculeaza_suma_totala_pe_tip(apartamente, 'gaz') == 100+5
	assert calculeaza_suma_totala_pe_tip(apartamente, 'altele') == 1000
	assert calculeaza_suma_totala_pe_tip(apartamente, 'incalzire') == 0

def test_sorteaza_apartamentele_dupa_suma_pe_tip():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(250, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(75, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(75, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(1000, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(1, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'incalzire'))
	ap.adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(0.5, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(250, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(1234, 'apa'))
	
	assert sorteaza_apartamentele_dupa_suma_pe_tip(apartamente, 'apa')[0:4] \
	    == [100, 2, 1, 4]

def test_calculeaza_suma_totala_pe_apartament():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(250, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(75, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(75, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(1000, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(1, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(9000.001, 'incalzire'))
	ap.adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(0.5, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(250, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(1234, 'apa'))
	
	assert math.isclose(100+250+75+75, calculeaza_suma_totala_pe_apartament(apartamente, 1))
	assert math.isclose(1000+1, calculeaza_suma_totala_pe_apartament(apartamente, 2))
	assert math.isclose(9000.001+9000.001+9000.001, calculeaza_suma_totala_pe_apartament(apartamente, 3))
	assert math.isclose(0.5, calculeaza_suma_totala_pe_apartament(apartamente, 4))
	assert math.isclose(250+1234, calculeaza_suma_totala_pe_apartament(apartamente, 100))
	pass

from .filtrare import *
''' FILTRARE '''

def test_filtreaza_cheltuieli_diferite_de_tip():
	apartamente = {}
	operatii = []
	
	cheltuieli_apa = [ch.creeaza_azi(5, 'apa'), ch.creeaza_azi(15, 'apa')]
	cheltuieli_canal = [ch.creeaza_azi(20, 'canal')]
	cheltuieli_gaz = [ch.creeaza_azi(5, 'gaz'), ch.creeaza_azi(123, 'gaz')]
	cheltuieli_incalzire = [ch.creeaza_azi(777, 'incalzire'), ch.creeaza_azi(222, 'incalzire')]
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[0])
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[1])
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_canal[0])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_gaz[0])
	ap.adauga_cheltuiala(apartamente, operatii, 3, cheltuieli_gaz[1])
	ap.adauga_cheltuiala(apartamente, operatii, 12, cheltuieli_incalzire[0])
	ap.adauga_cheltuiala(apartamente, operatii, 13, cheltuieli_incalzire[1])
	
	assert my_sorted(cheltuieli_canal+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'apa'))
	assert my_sorted(cheltuieli_apa+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'canal'))
	assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'gaz'))
	assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_gaz) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'incalzire'))

def test_filtreaza_cheltuieli_mai_mici_decat_suma():
	cheltuieli_sub_100 = [ch.creeaza_azi(5, 'apa'), ch.creeaza_azi(25, 'gaz'), ch.creeaza_azi(55, 'incalzire')]
	cheltuieli_sub_1000 = [ch.creeaza_azi(565, 'canal'), ch.creeaza_azi(465, 'incalzire'), ch.creeaza_azi(742, 'incalzire')]
	cheltuieli_sub_5000 = [ch.creeaza_azi(3468, 'gaz'), ch.creeaza_azi(2222, 'altele'), ch.creeaza_azi(2021, 'gaz')]
	
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_sub_100[0])
	ap.adauga_cheltuiala(apartamente, operatii, 7, cheltuieli_sub_100[1])
	ap.adauga_cheltuiala(apartamente, operatii, 3, cheltuieli_sub_100[2])
	ap.adauga_cheltuiala(apartamente, operatii, 12, cheltuieli_sub_1000[0])
	ap.adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_1000[1])
	ap.adauga_cheltuiala(apartamente, operatii, 7, cheltuieli_sub_1000[2])
	ap.adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_5000[0])
	ap.adauga_cheltuiala(apartamente, operatii, 9, cheltuieli_sub_5000[1])
	ap.adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_5000[2])
	
	assert my_sorted(cheltuieli_sub_100) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 100))
	assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 1000))
	assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000+cheltuieli_sub_5000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 5000))

def ruleaza_teste():
	''' STERGERE '''
	test_sterge_cheltuieli_apartament()
	test_sterge_cheltuieli_apartamente_consecutive()
	test_sterge_cheltuieli_dupa_tip()
	
	''' CAUTARE '''
	test_cauta_apartamente_cu_cheltuieli_mai_mari()
	test_cauta_cheltuieli_de_tip()
	test_cauta_cheltuieli_inainte_de_zi_mai_mari_decat_suma()
	
	''' RAPORTARE '''
	test_calculeaza_suma_totala_pe_tip()
	test_sorteaza_apartamentele_dupa_suma_pe_tip()
	test_calculeaza_suma_totala_pe_apartament()
	
	''' FILTRARE '''
	test_filtreaza_cheltuieli_diferite_de_tip()
	test_filtreaza_cheltuieli_mai_mici_decat_suma()