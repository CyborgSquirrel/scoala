from entity import MaterialDTO

class RepoException(Exception): pass

class CodDejaUtilizatException(RepoException): pass
class CodInexistentException(RepoException): pass
class MaterialInexistentException(RepoException): pass
class VanzareInexistentaException(RepoException): pass

class RepoMateriale:
	def __init__(self):
		self.__materiale = {}
	
	def store(self, material):
		if material.get_cod() in self.__materiale:
			raise CodDejaUtilizatException()
		self.__materiale[material.get_cod()] = material
	
	def find(self, cod):
		if not cod in self.__materiale:
			raise CodInexistentException()
		return self.__materiale[cod]
	
	def update(self, material):
		if not material.get_cod() in self.__materiale:
			raise MaterialInexistentException()
		self.__materiale[material.get_cod()] = material
	
	def get_all(self):
		return list(self.__materiale.values())
	
	def get_all_dto(self):
		material_dtos = []
		for material in self.__materiale.values():
			material_dto = MaterialDTO(
				material.get_cod(),
				material.get_denumire(),
				material.get_cantitate_pe_stoc(),
				material.get_pret_unitar()
			)
			material_dtos.append(material_dto)
		return material_dtos

class RepoVanzari:
	def __init__(self, path):
		self.__vanzari = {}
		self.__path = path
	
	def __store_all_to_file(self):
		with open(self.__path, "w") as f:
			for vanzare in self.__vanzari.values():
				print(f"{vanzare.get_denumire_material()},{vanzare.get_cantitate()},{vanzare.get_valoare_incasata()}", file=f)
	
	def store(self, vanzare):
		if vanzare.get_cod() in self.__vanzari:
			raise CodDejaUtilizatException()
		self.__vanzari[vanzare.get_cod()] = vanzare
		self.__store_all_to_file()
	
	def find(self, cod):
		if not cod in self.__vanzari:
			raise CodInexistentException()
		return self.__vanzari[cod]
	
	def update(self, vanzare):
		if not vanzare.get_cod() in self.__vanzari:
			raise VanzareInexistentaException()
		self.__vanzari[vanzare.get_cod()] = vanzare
		self.__store_all_to_file()
	
	def get_all(self):
		return list(self.__vanzari.values())