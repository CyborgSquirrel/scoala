import domain.cheltuiala as ch
import domain.apartamente as ap
from datetime import date
import math

''' CHELTUIALA '''

def test_ch_creeaza():
	cheltuiala = ch.creeaza(123, "apa", date(2021, 11, 11))
	assert math.isclose(ch.get_suma(cheltuiala), 123)
	assert ch.get_tip(cheltuiala) == "apa"
	assert ch.get_data(cheltuiala) == date(2021, 11, 11)
	
	cheltuiala = ch.creeaza(13.37, "canal", date(1999, 12, 12))
	assert math.isclose(ch.get_suma(cheltuiala), 13.37)
	assert ch.get_tip(cheltuiala) == "canal"
	assert ch.get_data(cheltuiala) ==  date(1999, 12, 12)
	
	try:
		cheltuiala = ch.creeaza_azi("7", "canal")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"
	
	try:
		cheltuiala = ch.creeaza_azi(7, 0)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		cheltuiala = ch.creeaza_azi(7, "caal")
		assert False
	except ValueError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"

def test_set_suma():
	cheltuiala = ch.creeaza_azi(12, "apa")
	
	ch.set_suma(cheltuiala, 12.001)
	assert math.isclose(ch.get_suma(cheltuiala), 12.001)
	
	ch.set_suma(cheltuiala, 495)
	assert math.isclose(ch.get_suma(cheltuiala), 495)
	
	try:
		ch.set_suma(cheltuiala, "o suta de parale si o duzina de carboave")
		assert False
	except TypeError as er:
		assert str(er) == "suma must be a float, or an int, not 'str'"

def test_set_tip():
	cheltuiala = ch.creeaza_azi(83, "apa")
	
	ch.set_tip(cheltuiala, "canal")
	assert ch.get_tip(cheltuiala) == "canal"
	
	ch.set_tip(cheltuiala, "incalzire")
	assert ch.get_tip(cheltuiala) == "incalzire"
	
	ch.set_tip(cheltuiala, "gaz")
	assert ch.get_tip(cheltuiala) == "gaz"
	
	ch.set_tip(cheltuiala, "altele")
	assert ch.get_tip(cheltuiala) == "altele"
	
	ch.set_tip(cheltuiala, "apa")
	assert ch.get_tip(cheltuiala) == "apa"
	
	try:
		ch.set_tip(cheltuiala, 121)
		assert False
	except TypeError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"
	
	try:
		ch.set_tip(cheltuiala, "secret")
		assert False
	except ValueError as er:
		assert str(er) == "tip must be one of the following strings: 'apa', 'canal', 'incalzire', 'gaz', 'altele'"

def test_set_data():
	cheltuiala = ch.creeaza_azi(83, "apa")
	
	ch.set_data(cheltuiala, date(2021, 11, 10))
	assert ch.get_data(cheltuiala) == date(2021, 11, 10)
	
	ch.set_data(cheltuiala, date(1990, 5, 5))
	assert ch.get_data(cheltuiala) == date(1990, 5, 5)
	
	ch.set_data(cheltuiala, date(2017, 1, 1))
	assert ch.get_data(cheltuiala) == date(2017, 1, 1)

''' APARTAMENTE '''

def test_adauga_cheltuiala():
	apartamente = {}
	operatii = []
	
	cheltuieli = [
		ch.creeaza_azi(6.5756, "gaz"),
		ch.creeaza_azi(456, "apa"),
		ch.creeaza_azi(0.0003, "altele"),
		ch.creeaza_azi(45646, "canal"),
		ch.creeaza_azi(76557, "incalzire"),
	]
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[0])
	
	assert apartamente[1][0] == cheltuieli[0]
	
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[1])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[2])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[3])
	
	assert apartamente[2] == [cheltuieli[1], cheltuieli[2], cheltuieli[3]]
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[4])
	
	assert apartamente[1][1] == cheltuieli[4]

def test_modifica_cheltuiala_suma():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
	ap.modifica_cheltuiala_suma(apartamente, operatii, 1, 0, 333)
	assert ch.get_suma(apartamente[1][0]) == 333
	ap.modifica_cheltuiala_suma(apartamente, operatii, 1, 0, 312312.55)
	assert ch.get_suma(apartamente[1][0]) == 312312.55
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
	ap.modifica_cheltuiala_suma(apartamente, operatii, 1, 1, 3453.1)
	assert ch.get_suma(apartamente[1][1]) == 3453.1

def test_modifica_cheltuiala_tip():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
	ap.modifica_cheltuiala_tip(apartamente, operatii, 1, 0, "apa")
	assert ch.get_tip(apartamente[1][0]) == "apa"
	ap.modifica_cheltuiala_tip(apartamente, operatii, 1, 0, "gaz")
	assert ch.get_tip(apartamente[1][0]) == "gaz"
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
	ap.modifica_cheltuiala_tip(apartamente, operatii, 1, 1, "altele")
	assert ch.get_tip(apartamente[1][1]) == "altele"

def test_modifica_cheltuiala_data():
	apartamente = {}
	operatii = []
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
	ap.modifica_cheltuiala_data(apartamente, operatii, 1, 0, date(2022, 12, 30))
	assert ch.get_data(apartamente[1][0]) == date(2022, 12, 30)
	ap.modifica_cheltuiala_data(apartamente, operatii, 1, 0, date(1980, 7, 10))
	assert ch.get_data(apartamente[1][0]) == date(1980, 7, 10)
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
	ap.modifica_cheltuiala_data(apartamente, operatii, 1, 1, date(2001, 3, 6))
	assert ch.get_data(apartamente[1][1]) == date(2001, 3, 6)

def test_sterge_cheltuiala():
	apartamente = {}
	operatii = []
	
	cheltuieli = [
		ch.creeaza_azi(456, "apa"),
		ch.creeaza_azi(0.0003, "altele"),
		ch.creeaza_azi(45646, "canal"),
		ch.creeaza_azi(76557, "incalzire"),
	]
	
	ap.adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[0])
	ap.sterge_cheltuiala(apartamente, operatii, 1, 0)
	assert not 1 in apartamente
	
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[1])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[2])
	ap.adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[3])
	
	ap.sterge_cheltuiala(apartamente, operatii, 2, 2)
	assert len(apartamente[2]) == 2
	ap.sterge_cheltuiala(apartamente, operatii, 2, 0)
	assert len(apartamente[2]) == 1
	ap.sterge_cheltuiala(apartamente, operatii, 2, 0)
	assert not 2 in apartamente


def test_undo():
	apartamente = {}
	operatii = []
	
	ap.inceput_operatie(operatii, "adauga multe cheltuieli")
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1114, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1837, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1211, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(2279, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(680, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(2447, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(2408, 'canal'))
	ap.adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(1579, 'altele'))
	ap.adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(324, 'apa'))
	ap.adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(3408, 'gaz'))
	ap.adauga_cheltuiala(apartamente, operatii, 101, ch.creeaza_azi(3550, 'apa'))
	
	ap.inceput_operatie(operatii, "adauga cheltuiala")
	ap.adauga_cheltuiala(apartamente, operatii, 101, ch.creeaza_azi(1231, 'gaz'))
	assert ap.undo(apartamente, operatii) == "adauga cheltuiala"
	assert len(apartamente[101]) == 1
	
	ap.inceput_operatie(operatii, "sterge cheltuieli apartamentul 1")
	ap.sterge_cheltuiala(apartamente, operatii, 1, 0)
	ap.sterge_cheltuiala(apartamente, operatii, 1, 0)
	ap.sterge_cheltuiala(apartamente, operatii, 1, 0)
	assert ap.undo(apartamente, operatii) == "sterge cheltuieli apartamentul 1"
	assert len(apartamente[1]) == 3
	
	assert ap.undo(apartamente, operatii) == "adauga multe cheltuieli"

def ruleaza_teste():
	''' CHELTUIALA '''
	test_ch_creeaza()
	test_set_suma()
	test_set_tip()
	test_set_data()
	
	''' APARTAMENTE '''
	test_adauga_cheltuiala()
	test_modifica_cheltuiala_suma()
	test_modifica_cheltuiala_tip()
	test_modifica_cheltuiala_data()
	test_sterge_cheltuiala()
	
	test_undo()
