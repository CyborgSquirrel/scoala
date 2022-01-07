import domain.cheltuiala as ch
from datetime import date

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
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[0])
    
    assert apartamente[1][0] == cheltuieli[0]
    
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[1])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[2])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[3])
    
    assert apartamente[2] == [cheltuieli[1], cheltuieli[2], cheltuieli[3]]
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[4])
    
    assert apartamente[1][1] == cheltuieli[4]

def test_modifica_cheltuiala_suma():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
    modifica_cheltuiala_suma(apartamente, operatii, 1, 0, 333)
    assert ch.get_suma(apartamente[1][0]) == 333
    modifica_cheltuiala_suma(apartamente, operatii, 1, 0, 312312.55)
    assert ch.get_suma(apartamente[1][0]) == 312312.55
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
    modifica_cheltuiala_suma(apartamente, operatii, 1, 1, 3453.1)
    assert ch.get_suma(apartamente[1][1]) == 3453.1

def test_modifica_cheltuiala_tip():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
    modifica_cheltuiala_tip(apartamente, operatii, 1, 0, "apa")
    assert ch.get_tip(apartamente[1][0]) == "apa"
    modifica_cheltuiala_tip(apartamente, operatii, 1, 0, "gaz")
    assert ch.get_tip(apartamente[1][0]) == "gaz"
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
    modifica_cheltuiala_tip(apartamente, operatii, 1, 1, "altele")
    assert ch.get_tip(apartamente[1][1]) == "altele"

def test_modifica_cheltuiala_data():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(45646, "canal"))
    modifica_cheltuiala_data(apartamente, operatii, 1, 0, date(2022, 12, 30))
    assert ch.get_data(apartamente[1][0]) == date(2022, 12, 30)
    modifica_cheltuiala_data(apartamente, operatii, 1, 0, date(1980, 7, 10))
    assert ch.get_data(apartamente[1][0]) == date(1980, 7, 10)
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(2434, "apa"))
    modifica_cheltuiala_data(apartamente, operatii, 1, 1, date(2001, 3, 6))
    assert ch.get_data(apartamente[1][1]) == date(2001, 3, 6)

def sterge_cheltuiala(apartamente, operatii, indice_apartament, indice_cheltuiala):
    '''Adauga cheltuiala la un apartament, din dictionarul de apartamente.
    input: apartamente -- dictionar cu apartamente
           operatii -- lista de operatii
           indice_apartament -- int
           indice_cheltuiala -- int
    '''
    cheltuiala = apartamente[indice_apartament].pop(indice_cheltuiala)
    if len(apartamente[indice_apartament]) == 0:
        del apartamente[indice_apartament]
    operatii.append({"nume":"sterge", "indice_apartament":indice_apartament, "indice_cheltuiala":indice_cheltuiala, "cheltuiala":cheltuiala})


def ruleaza_teste():
    ''' CHELTUIALA '''
    test_ch_creeaza()
    test_set_suma()
    test_set_tip()
    test_set_data()

    ''' APARTAMENTE '''

ruleaza_teste()
