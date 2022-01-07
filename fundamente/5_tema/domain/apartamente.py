import domain.cheltuiala as ch
from datetime import date

''' APARTAMENTE '''

''' ADAUGARE '''

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
    '''Modifica tip unei cheltuieli din apartamente.
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

def test_sterge_cheltuiala():
    apartamente = {}
    operatii = []
    
    cheltuieli = [
        ch.creeaza_azi(456, "apa"),
        ch.creeaza_azi(0.0003, "altele"),
        ch.creeaza_azi(45646, "canal"),
        ch.creeaza_azi(76557, "incalzire"),
    ]
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli[0])
    sterge_cheltuiala(apartamente, operatii, 1, 0)
    assert not 1 in apartamente
    
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[1])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[2])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli[3])
    
    sterge_cheltuiala(apartamente, operatii, 2, 2)
    assert len(apartamente[2]) == 2
    sterge_cheltuiala(apartamente, operatii, 2, 0)
    assert len(apartamente[2]) == 1
    sterge_cheltuiala(apartamente, operatii, 2, 0)
    assert not 2 in apartamente

''' STERGERE '''

def sterge_cheltuieli_apartament(apartamente, operatii, indice_apartament):
    '''Sterge toate cheltuielile apartamentului aflat la indice_apartament.
    input: apartamente -- dictionar cu apartamente
           operatii -- lista de operatii
           indice_apartament -- int
    '''
    for i in reversed(range(len(apartamente[indice_apartament]))):
        sterge_cheltuiala(apartamente, operatii, indice_apartament, i)

def test_sterge_cheltuieli_apartament():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
    
    sterge_cheltuieli_apartament(apartamente, operatii, 1)
    assert not 1 in apartamente

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
                sterge_cheltuiala(apartamente, operatii, i, j)
        except KeyError:
            pass

def test_sterge_cheltuieli_apartamente_consecutive():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(100, 'apa'))
    
    sterge_cheltuieli_apartamente_consecutive(apartamente, operatii, 2, 3)
    
    assert len(apartamente) == 3
    
    assert 1 in apartamente
    assert not 2 in apartamente
    assert not 3 in apartamente
    assert 4 in apartamente
    assert 100 in apartamente

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
                sterge_cheltuiala(apartamente, operatii, indice, i)
            else:
                i += 1

def test_sterge_cheltuieli_dupa_tip():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(100, 'altele'))
    adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(100, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(100, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 101, ch.creeaza_azi(100, 'apa'))
    
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

''' UNDO '''

def inceput_operatie(operatii, text):
    '''Adauga inceputul unei operatii.
    input: operatii -- lista de operatii
           text -- string
    '''
    operatii.append({"nume":"inceput", "text": text})

def undo(apartamente, operatii):
    '''Reface ultima operatie.
    input: apartamente -- dictionar cu apartamente
           operatii -- lista de operatii
    '''
    operatie = operatii.pop()
    while operatie["nume"] != "inceput":
        if operatie["nume"] == "adauga":
            del apartamente[operatie["indice_apartament"]][operatie["indice_cheltuiala"]]
        elif operatie["nume"] == "set_suma":
            ch.set_suma(apartamente[operatie["indice_apartament"]][operatie["indice_cheltuiala"]], operatie["suma"])
        elif operatie["nume"] == "set_tip":
            ch.set_tip(apartamente[operatie["indice_apartament"]][operatie["indice_cheltuiala"]], operatie["tip"])
        elif operatie["nume"] == "set_data":
            ch.set_data(apartamente[operatie["indice_apartament"]][operatie["indice_cheltuiala"]], operatie["data"])
        elif operatie["nume"] == "sterge":
            if not operatie["indice_apartament"] in apartamente:
                apartamente[operatie["indice_apartament"]] = []
            apartamente[operatie["indice_apartament"]].insert(operatie["indice_cheltuiala"], operatie["cheltuiala"])
        operatie = operatii.pop()

def test_undo():
    apartamente = {}
    operatii = []
    
    inceput_operatie(operatii, "")
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1114, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1837, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1211, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(2279, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(680, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(2447, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(2408, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 3, ch.creeaza_azi(1579, 'altele'))
    adauga_cheltuiala(apartamente, operatii, 4, ch.creeaza_azi(324, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 100, ch.creeaza_azi(3408, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 101, ch.creeaza_azi(3550, 'apa'))
    
    inceput_operatie(operatii, "")
    sterge_cheltuieli_apartament(apartamente, operatii, 1)
    assert not 1 in apartamente
    undo(apartamente, operatii)
    assert len(apartamente[1]) == 3
    
    inceput_operatie(operatii, "")
    sterge_cheltuieli_apartament(apartamente, operatii, 2)
    assert not 2 in apartamente
    undo(apartamente, operatii)
    assert len(apartamente[2]) == 2
    
    inceput_operatie(operatii, "")
    sterge_cheltuiala(apartamente, operatii, 4, 0)
    assert not 4 in apartamente
    undo(apartamente, operatii)
    assert len(apartamente[4]) == 1
    
    inceput_operatie(operatii, "")
    modifica_cheltuiala_tip(apartamente, operatii, 100, 0, "apa")
    assert ch.get_tip(apartamente[100][0]) == "apa"
    undo(apartamente, operatii)
    assert ch.get_tip(apartamente[100][0]) == "gaz"

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

def test_cauta_apartamente_cu_cheltuieli_mai_mari():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(15, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(10, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(5, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(15, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(999, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(1000, 'altele'))
    
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

def cauta_cheltuieli_de_tip(apartamente, tip):
    '''Cauta toate apartamentele care au cheltuieli mai mari decat suma furnizata.
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

def test_cauta_cheltuieli_de_tip():
    apartamente = {}
    operatii = []
    
    cheltuieli_apa = [ch.creeaza_azi(1, 'apa'), ch.creeaza_azi(10, 'apa'), ch.creeaza_azi(15, 'apa')]
    cheltuieli_gaz = [ch.creeaza_azi(100, 'gaz'), ch.creeaza_azi(5, 'gaz')]
    cheltuieli_canal = [ch.creeaza_azi(15, 'canal'), ch.creeaza_azi(999, 'canal')]
    cheltuieli_altele = [ch.creeaza_azi(1000, 'altele')]
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[0])
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_canal[0])
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_gaz[0])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_apa[1])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_gaz[1])
    adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_apa[2])
    adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_canal[1])
    adauga_cheltuiala(apartamente, operatii, 10, cheltuieli_altele[0])
    
    def my_sorted(iterable):
        def my_key(a):
            return str(ch.get_suma(a)) + ch.get_tip(a)
        return sorted(iterable, key=my_key)
    
    assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'apa')) == my_sorted(cheltuieli_apa)
    assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'gaz')) == my_sorted(cheltuieli_gaz)
    assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'canal')) == my_sorted(cheltuieli_canal)
    assert my_sorted(cauta_cheltuieli_de_tip(apartamente, 'altele')) == my_sorted(cheltuieli_altele)
    assert cauta_cheltuieli_de_tip(apartamente, 'incalzire') == []

''' RAPORTARE '''

def calculeaza_suma_totala_pe_tip(apartamente, tip):
    '''Calculeaza suma totala pentru un tip de ch.
    input: apartamente -- dictionar cu apartamente
           tip -- string, una din urmatoarele variante: 'apa', 'canal', 'incalzire', 'gaz', 'altele'
    output: cheltuielile_cautate -- lista cu cheltuielile cautate
    '''
    suma_totala = 0
    for indice,apartament in apartamente.items():
        for cheltuiala in apartament:
            if ch.get_tip(cheltuiala) == tip:
                suma_totala += ch.get_suma(cheltuiala)
    return suma_totala

def test_calculeaza_suma_totala_pe_tip():
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(1, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(10, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(15, 'apa'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(15, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(999, 'canal'))
    adauga_cheltuiala(apartamente, operatii, 1, ch.creeaza_azi(100, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 2, ch.creeaza_azi(5, 'gaz'))
    adauga_cheltuiala(apartamente, operatii, 10, ch.creeaza_azi(1000, 'altele'))
    
    assert calculeaza_suma_totala_pe_tip(apartamente, 'apa') == 1+10+15
    assert calculeaza_suma_totala_pe_tip(apartamente, 'canal') == 15+999
    assert calculeaza_suma_totala_pe_tip(apartamente, 'gaz') == 100+5
    assert calculeaza_suma_totala_pe_tip(apartamente, 'altele') == 1000
    assert calculeaza_suma_totala_pe_tip(apartamente, 'incalzire') == 0

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

def test_filtreaza_cheltuieli_diferite_de_tip():
    apartamente = {}
    operatii = []
    
    cheltuieli_apa = [ch.creeaza_azi(5, 'apa'), ch.creeaza_azi(15, 'apa')]
    cheltuieli_canal = [ch.creeaza_azi(20, 'canal')]
    cheltuieli_gaz = [ch.creeaza_azi(5, 'gaz'), ch.creeaza_azi(123, 'gaz')]
    cheltuieli_incalzire = [ch.creeaza_azi(777, 'incalzire'), ch.creeaza_azi(222, 'incalzire')]
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[0])
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_apa[1])
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_canal[0])
    adauga_cheltuiala(apartamente, operatii, 2, cheltuieli_gaz[0])
    adauga_cheltuiala(apartamente, operatii, 3, cheltuieli_gaz[1])
    adauga_cheltuiala(apartamente, operatii, 12, cheltuieli_incalzire[0])
    adauga_cheltuiala(apartamente, operatii, 13, cheltuieli_incalzire[1])
    
    def my_sorted(iterable):
        def my_key(a):
            return str(ch.get_suma(a)) + ch.get_tip(a)
        return sorted(iterable, key=my_key)
    
    assert my_sorted(cheltuieli_canal+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'apa'))
    assert my_sorted(cheltuieli_apa+cheltuieli_gaz+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'canal'))
    assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_incalzire) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'gaz'))
    assert my_sorted(cheltuieli_apa+cheltuieli_canal+cheltuieli_gaz) == my_sorted(filtreaza_cheltuieli_diferite_de_tip(apartamente, 'incalzire'))

def filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, suma):
    '''Returneaza toate cheltuielile diferite de tipul furnizat.
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

def test_filtreaza_cheltuieli_mai_mici_decat_suma():
    cheltuieli_sub_100 = [ch.creeaza_azi(5, 'apa'), ch.creeaza_azi(25, 'gaz'), ch.creeaza_azi(55, 'incalzire')]
    cheltuieli_sub_1000 = [ch.creeaza_azi(565, 'canal'), ch.creeaza_azi(465, 'incalzire'), ch.creeaza_azi(742, 'incalzire')]
    cheltuieli_sub_5000 = [ch.creeaza_azi(3468, 'gaz'), ch.creeaza_azi(2222, 'altele'), ch.creeaza_azi(2021, 'gaz')]
    
    apartamente = {}
    operatii = []
    
    adauga_cheltuiala(apartamente, operatii, 1, cheltuieli_sub_100[0])
    adauga_cheltuiala(apartamente, operatii, 7, cheltuieli_sub_100[1])
    adauga_cheltuiala(apartamente, operatii, 3, cheltuieli_sub_100[2])
    adauga_cheltuiala(apartamente, operatii, 12, cheltuieli_sub_1000[0])
    adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_1000[1])
    adauga_cheltuiala(apartamente, operatii, 7, cheltuieli_sub_1000[2])
    adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_5000[0])
    adauga_cheltuiala(apartamente, operatii, 9, cheltuieli_sub_5000[1])
    adauga_cheltuiala(apartamente, operatii, 4, cheltuieli_sub_5000[2])
    
    def my_sorted(iterable):
        def my_key(a):
            return str(ch.get_suma(a)) + ch.get_tip(a)
        return sorted(iterable, key=my_key)
    
    assert my_sorted(cheltuieli_sub_100) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 100))
    assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 1000))
    assert my_sorted(cheltuieli_sub_100+cheltuieli_sub_1000+cheltuieli_sub_5000) == my_sorted(filtreaza_cheltuieli_mai_mici_decat_suma(apartamente, 5000))

def ruleaza_teste():
    test_adauga_cheltuiala()
    test_sterge_cheltuiala()
    test_modifica_cheltuiala_suma()
    test_modifica_cheltuiala_tip()
    test_modifica_cheltuiala_data()
    
    test_sterge_cheltuieli_apartament()
    test_sterge_cheltuieli_apartamente_consecutive()
    test_sterge_cheltuieli_dupa_tip()
    
    test_undo()
    
    test_cauta_apartamente_cu_cheltuieli_mai_mari()
    test_cauta_cheltuieli_de_tip()
    
    test_calculeaza_suma_totala_pe_tip()
    
    test_filtreaza_cheltuieli_diferite_de_tip()
    test_filtreaza_cheltuieli_mai_mici_decat_suma()

ruleaza_teste()
