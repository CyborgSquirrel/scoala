from domain.entity import Grade
from domain.validator import GradeValidator

from . import ServiceException

class GradeService:
	def __init__(self, validator, grade_repo, student_repo, discipline_repo):
		''' Create grade service with given validator.
		input: validator -- GradeValidator
		       student_repo -- StudentRepository
		       discipline_repo -- DisciplineRepository
		'''
		self.__validator = validator
		self.__grade_repo = grade_repo
		self.__student_repo = student_repo
		self.__discipline_repo = discipline_repo
	
	def get_grades(self):
		''' Gets a list of all the grades.
		output: list of Grade
		'''
		return list(self.__grade_repo.values())
	
	def add_grade(self, grade_id, student_id, discipline_id, value):
		''' Creates a grade with given grade_id, and name, and adds the grade to the repository of grades.
		input: grade_id -- int, >= 1
		       student_id -- int, >= 1
		       discipline_id -- int, >= 1
		       value -- float, 1 <= value <= 10
		raise: ValidatorException, if the grade's data is invalid
		       ServiceException, if the grade is already in the repository
		'''
		if not grade_id in self.__grade_repo:
			grade = Grade(grade_id, student_id, discipline_id, value)
			self.__validator.validate(grade)
			
			if not student_id in self.__student_repo:
				raise ServiceException("the given student_id is not in the repository")
			
			if not discipline_id in self.__discipline_repo:
				raise ServiceException("the given discipline_id is not in the repository")
			
			self.__grade_repo[grade_id] = grade
		else:
			raise ServiceException("the given grade_id is already in use")
	
	def erase_grade(self, grade_id):
		''' Erases the grade with grade_id.
		input: grade_id -- int, >= 1
		raise: ServiceException, if the grade is not in the repository
		'''
		if grade_id in self.__grade_repo:
			del self.__grade_repo[grade_id]
		else:
			raise ServiceException("the given grade_id is not in the repository")
	
	def erase_student_and_all_their_grades(self, student_id):
		''' Erases the student with student_id, and all their grades.
		input: student_id -- int, >= 1
		raise: ServiceException, if the student is not in the repository
		'''
		if student_id in self.__student_repo:
			for grade_id in list(self.__grade_repo):
				if self.__grade_repo[grade_id].get_student_id() == student_id:
					self.erase_grade(grade_id)
			del self.__student_repo[student_id]
		else:
			raise ServiceException("the given student_id is not in the repository")
	
	def erase_discipline_and_all_its_grades(self, discipline_id):
		''' Erases the discipline with discipline_id, and all its grades.
		input: discipline_id -- int, >= 1
		raise: ServiceException, if the discipline is not in the repository
		'''
		if discipline_id in self.__discipline_repo:
			for grade_id in list(self.__grade_repo):
				if self.__grade_repo[grade_id].get_discipline_id() == discipline_id:
					self.erase_grade(grade_id)
			del self.__discipline_repo[discipline_id]
		else:
			raise ServiceException("the given discipline_id is not in the repository")
	
	def find_lowest_grade(self):
		''' Finds the grade with the lowest value.
		output: lowest_grade -- Grade
		raise: ServiceException, if there are no grades
		'''
		lowest_grade = None
		for grade in self.__grade_repo.values():
			if lowest_grade == None or grade.get_value() < lowest_grade.get_value():
				lowest_grade = grade
		
		if lowest_grade == None:
			raise ServiceException("there are no grades")
		else:
			return lowest_grade