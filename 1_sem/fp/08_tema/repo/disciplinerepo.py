from . import RepoException

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
		''' Update a discipline.
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
