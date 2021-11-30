from domain.entity import Discipline
from domain.validator import DisciplineValidator

from . import ServiceException

class DisciplineService:
	def __init__(self, validator, discipline_repo):
		''' Create discipline service with given validator.
		input: validator -- DisciplineValidator
		'''
		self.__validator = validator
		self.__discipline_repo = discipline_repo
	
	def get_disciplines(self):
		''' Gets a list of all the disciplines.
		output: list of Discipline
		'''
		return self.__discipline_repo.get_disciplines()
	
	def add_discipline(self, discipline_id, name, professor):
		''' Creates a discipline with given student_id, name, and professor, and adds the discipline to the repository of disciplines.
		input: discipline_id -- int, >= 1
		       name -- string, must not be empty
		       professor -- string, must not be empty
		raise: ValidatorException, if the discipline's data is invalid
		       RepoException, if the discipline is already in the repository
		'''
		discipline = Discipline(discipline_id, name, professor)
		self.__validator.validate(discipline)
		self.__discipline_repo.store(discipline)
	
	def update_discipline(self, discipline_id, name, professor):
		''' Updates the discipline with the given discipline_id.
		input: discipline_id -- int, >= 1
		       name -- string, must not be empty
		       professor -- string, must not be empty
		raise: ValidatorException, if the discipline's data is invalid
		       RepoException, if the discipline is not in the repository
		'''
		discipline = Discipline(discipline_id, name, professor)
		self.__validator.validate(discipline)
		self.__discipline_repo.update(discipline)
	
	def find_discipline(self, discipline_id):
		''' Finds the discipline with the given discipline_id.
		input: discipline_id -- int, >= 1
		output: Discipline
		raise: ValidatorException, if the discipline's data is invalid
		       RepoException, if the discipline is not in the repository
		'''
		return self.__discipline_repo.find(discipline_id)
