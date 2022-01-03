from . import RepoException
from domain.entity import Discipline

class InMemoryDisciplineRepo:
	def __init__(self):
		self.__disciplines = {}
	
	def store(self, discipline):
		''' Store a discipline in the repo.
		input: discipline -- Discipline
		raise: RepoException, if there already is a discipline with the provided discipline's id
		'''
		if not discipline.get_discipline_id() in self.__disciplines:
			self.__disciplines[discipline.get_discipline_id()] = discipline
		else:
			raise RepoException("discipline is already in the repo")
	
	def update(self, discipline):
		''' Update a discipline in the repo.
		input: discipline -- Discipline
		raise: RepoException, if the discipline is not in the repo
		'''
		if discipline.get_discipline_id() in self.__disciplines:
			self.__disciplines[discipline.get_discipline_id()] = discipline
		else:
			raise RepoException("there is no such discipline in the repo")
	
	def erase(self, discipline_id):
		''' Erase a discipline from the repo.
		input: discipline_id -- int, >= 1
		raise: RepoException, if there is no discipline with discipline_id
		'''
		if not discipline_id in self.__disciplines:
			raise RepoException("there is no discipline with the given discipline_id in the repo")
		else:
			del self.__disciplines[discipline_id]
	
	def find(self, discipline_id):
		''' Find a discipline in the repo.
		input: discipline_id -- int, >= 1
		output: Discipline
		raise: RepoException, if there is no discipline with discipline_id
		'''
		if not discipline_id in self.__disciplines:
			raise RepoException("there is no discipline with the given discipline_id in the repo")
		else:
			return self.__disciplines[discipline_id]
	
	def get_disciplines(self):
		''' Return a list of all the disciplines.
		output: list of Discipline
		'''
		return list(self.__disciplines.values())
	
	def get_len(self):
		''' Returns number of disciplines.
		output: int
		'''
		return len(self.__disciplines)

class FileDisciplineRepo(InMemoryDisciplineRepo):
	def __init__(self, filename):
		super().__init__()
		self.__filename = filename
		self.__load_all_from_file()
	
	def __load_all_from_file(self):
		try:
			with open(self.__filename, "r") as f:
				index = 0
				
				for line in f:
					if line[-1] == '\n':
						line = line[:-1]
					if line.strip() != "":
						if index == 0:
							discipline_id = int(line)
						elif index == 1:
							name = line
						elif index == 2:
							professor = line
							
							discipline = Discipline(discipline_id, name, professor)
							super().store(discipline)
						
						index += 1
						index %= 3
						
		except FileNotFoundError:
			with open(self.__filename, "w") as f:
				pass
	
	def __store_all_to_file(self):
		with open(self.__filename, "w") as f:
			disciplines = super().get_disciplines()
			for discipline in disciplines:
				print(f"{discipline.get_discipline_id()}\n{discipline.get_name()}\n{discipline.get_professor()}", file=f)
	
	def store(self, discipline):
		''' Store a discipline in the repo (and in the file).
		input: discipline -- Discipline
		raise: RepoException, if there already is a discipline with the provided discipline's id
		'''
		super().store(discipline)
		self.__store_all_to_file()
	
	def update(self, discipline):
		''' Update a discipline in the repo (and in the file).
		input: discipline -- Discipline
		raise: RepoException, if the discipline is not in the repo
		'''
		super().update(discipline)
		self.__store_all_to_file()
	
	def erase(self, discipline_id):
		''' Erase a discipline from the repo (and in the file).
		input: discipline_id -- int, >= 1
		raise: RepoException, if there is no discipline with discipline_id
		'''
		super().erase(discipline_id)
		self.__store_all_to_file()