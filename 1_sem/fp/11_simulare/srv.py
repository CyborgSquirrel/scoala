from entity import Material

class SrvException(Exception): pass

class VanzareImposibilaException(Exception): pass

class SrvMateriale:
	def __init__(self, repo):
		''' Creeaza un service de materiale cu repo-ul furnizat.
		input: repo -- RepoMateriale
		'''
		self.__repo = repo
	
	def adauga_material(self, material):
		''' Adauga materialul furnizat in repo-ul de materiale.
		input: material -- Material
		'''
		self.__repo.store(material)
	
	def salveaza_materiale_cu_valoarea_de_pe_stoc_mai_mare_decat(self, valoare_de_pe_stoc_furnizata):
		''' Salveaza materialele cu valoare de pe stoc mai mare decat valoarea de pe stoc furnizata.
		input: valoare_de_pe_stoc_furnizata -- float
		'''
		material_dtos = self.__repo.get_all_dto()
		for material_dto in material_dtos:
			valoare_de_pe_stoc = material_dto.get_pret_unitar() * material_dto.get_cantitate_pe_stoc()
			material_dto.set_valoare_de_pe_stoc(valoare_de_pe_stoc)
		
		with open("valoredepestoc.txt", "w") as f:
			for material_dto in material_dtos:
				if material_dto.get_valoare_de_pe_stoc() >= valoare_de_pe_stoc_furnizata:
					print(f"{material_dto.get_cod()},{material_dto.get_denumire()},{material_dto.get_cantitate_pe_stoc()},{material_dto.get_pret_unitar()}", file=f)

class SrvVanzari:
	def __init__(self, repo_vanzari, repo_materiale):
		''' Creeaza un service de vanzari cu repo_vanzari, si repo_materiale furnizate.
		input: repo_vanzari -- RepoVanzari
		       repo_materiale -- RepoMateriale
		'''
		self.__repo_vanzari = repo_vanzari
		self.__repo_materiale = repo_materiale
	
	def adauga_vanzare(self, vanzare):
		''' Adauga vanzarea furnizata in repo-ul de vanzari.
		input: vanzare -- Vanzare
		'''
		material = self.__repo_materiale.find(vanzare.get_cod_material())
		if vanzare.get_cantitate() <= material.get_cantitate_pe_stoc():
			vanzare.set_denumire_material(material.get_denumire())
			vanzare.set_valoare_incasata(vanzare.get_cantitate()*material.get_pret_unitar())
			
			nou_material = Material(
				material.get_cod(),
				material.get_denumire(),
				material.get_um(),
				material.get_cantitate_pe_stoc() - vanzare.get_cantitate(),
				material.get_pret_unitar(),
			)
			self.__repo_materiale.update(nou_material)
			
			self.__repo_vanzari.store(vanzare)
		else:
			raise VanzareImposibilaException()