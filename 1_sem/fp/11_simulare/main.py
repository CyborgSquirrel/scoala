from entity import Material, Vanzare
from repo import RepoMateriale, RepoVanzari
from srv import SrvMateriale, SrvVanzari

from srv import VanzareImposibilaException

from srv import SrvException
from repo import RepoException

repo_materiale = RepoMateriale()
repo_vanzari = RepoVanzari("vanzari.txt")

srv_materiale = SrvMateriale(repo_materiale)
srv_vanzari = SrvVanzari(repo_vanzari, repo_materiale)

class UiException(Exception):
	def __init__(self, error):
		self.__error = error
	
	def get_error(self):
		return self.__error

class ConsoleUi:
	def __init__(self, srv_materiale, srv_vanzari):
		self.__srv_materiale = srv_materiale
		self.__srv_vanzari = srv_vanzari
		self.__cod_pentru_vanzare = 0
	
	def __input(self, name, converter):
		try:
			return converter(input(f"{name} = "))
		except:
			raise UiException(f"valoare invalida pentru {name}")
	
	def __adauga_material(self):
		cod = self.__input("cod", int)
		denumire = self.__input("denumire", str)
		um = self.__input("um", str)
		cantitate_pe_stoc = self.__input("cantitate pe stoc", float)
		pret_unitar = self.__input("pret unitar", float)
		
		material = Material(cod, denumire, um, cantitate_pe_stoc, pret_unitar)
		self.__srv_materiale.adauga_material(material)
	
	def __salveaza_materiale_cu_valoarea_de_pe_stoc_mai_mare_decat(self):
		valoare_de_pe_stoc = self.__input("valoare de pe stoc", float)
		self.__srv_materiale.salveaza_materiale_cu_valoarea_de_pe_stoc_mai_mare_decat(valoare_de_pe_stoc)
	
	def __efectueaza_vanzare(self):
		cod = self.__input("cod", int)
		# TODO: poate ar fi bine sa scrie si um langa cantitate
		cantitate = self.__input("cantitate", float)
		
		try:
			vanzare = Vanzare(self.__cod_pentru_vanzare, cod, cantitate)
			self.__cod_pentru_vanzare += 1
			srv_vanzari.adauga_vanzare(vanzare)
			print("Vanzarea este posibilia si a fost efectuata")
		except VanzareImposibilaException:
			print("Vanzarea este imposibila")
	
	def run(self):
		while True:
			comanda = input("# ")
			try:
				if comanda == "1":
					self.__adauga_material()
				elif comanda == "2":
					self.__salveaza_materiale_cu_valoarea_de_pe_stoc_mai_mare_decat()
				elif comanda == "3":
					self.__efectueaza_vanzare()
				else:
					raise UiException("comanda invalida")
			except UiException as ex:
				print(ex.get_error())
			except (RepoException, SrvException):
				print("Ultima operatie a declansat o eroare")

ui = ConsoleUi(srv_materiale, srv_vanzari)
ui.run()