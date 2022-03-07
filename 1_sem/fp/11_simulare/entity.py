class Material:
	def __init__(self, cod, denumire, um, cantitate_pe_stoc, pret_unitar):
		''' Creeaza un material cu codul, denumirea, cantitatea pe stoc, si pretul unitar furnizate.
		input: cod -- int
		       denumire -- string
		       um -- string
		       cantitate_pe_stoc -- float
		       pret_unitar -- float
		'''
		self.__cod = cod
		self.__denumire = denumire
		self.__um = um
		self.__cantitate_pe_stoc = cantitate_pe_stoc
		self.__pret_unitar = pret_unitar
	
	def get_cod(self):
		return self.__cod
	
	def get_denumire(self):
		return self.__denumire
	
	def get_um(self):
		return self.__um
	
	def get_cantitate_pe_stoc(self):
		return self.__cantitate_pe_stoc
	
	def get_pret_unitar(self):
		return self.__pret_unitar
	
	def __eq__(self, other):
		if type(self) != type(other):
			return false
		return self.get_cod() == other.get_cod()

class MaterialDTO:
	def __init__(self, cod, denumire, cantitate_pe_stoc, pret_unitar):
		''' Creeaza un material data transfer object cu codul, denumirea, cantitatea pe stoc, si pretul unitar furnizate.
		input: cod -- int
		       denumire -- string
		       cantitate_pe_stoc -- float
		       pret_unitar -- float
		'''
		self.__cod = cod
		self.__denumire = denumire
		self.__cantitate_pe_stoc = cantitate_pe_stoc
		self.__pret_unitar = pret_unitar
		self.__valoare_de_pe_stoc = None
	
	def set_valoare_de_pe_stoc(self, valoare_de_pe_stoc):
		self.__valoare_de_pe_stoc = valoare_de_pe_stoc
	
	def get_cod(self):
		return self.__cod
	
	def get_denumire(self):
		return self.__denumire
	
	def get_cantitate_pe_stoc(self):
		return self.__cantitate_pe_stoc
	
	def get_pret_unitar(self):
		return self.__pret_unitar
	
	def get_valoare_de_pe_stoc(self):
		return self.__valoare_de_pe_stoc

class Vanzare:
	def __init__(self, cod, cod_material, cantitate):
		''' Creeaza o vanzare cu codul, codul materialului, si cantitatea furnizate
		input: cod -- int
		       cod_material -- int
		       cantitate -- float
		'''
		self.__cod = cod
		self.__cod_material = cod_material
		self.__cantitate = cantitate
		self.__denumire_material = None
		self.__valoare_incasata = None
	
	def set_denumire_material(self, denumire_material):
		self.__denumire_material = denumire_material
	
	def set_valoare_incasata(self, valoare_incasata):
		self.__valoare_incasata = valoare_incasata
	
	def get_cod(self):
		return self.__cod
	
	def get_cod_material(self):
		return self.__cod_material
	
	def get_denumire_material(self):
		return self.__denumire_material
	
	def get_cantitate(self):
		return self.__cantitate
	
	def get_valoare_incasata(self):
		return self.__valoare_incasata
	