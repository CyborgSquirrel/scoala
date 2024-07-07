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
		return list(self.__discipline_repo.values())
	
	def add_discipline(self, discipline_id, name, professor):
		''' Creates a discipline with given student_id, name, and professor, and adds the discipline to the repository of disciplines.
		input: discipline_id -- int, >= 1
		       name -- string, must not be empty
		       professor -- string, must not be empty
		raise: ValidatorException, if the discipline's data is invalid
		       ServiceException, if the discipline is already in the repository
		'''
		if not discipline_id in self.__discipline_repo:
			discipline = Discipline(discipline_id, name, professor)
			self.__validator.validate(discipline)
			self.__discipline_repo[discipline_id] = discipline
		else:
			raise ServiceException("the given discipline_id is already in use")
