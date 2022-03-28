from domain.entity import Student
from domain.validator import StudentValidator

from . import ServiceException

class StudentService:
	def __init__(self, validator, student_repo):
		''' Create student service with given validator.
		input: validator -- StudentValidator
		'''
		self.__validator = validator
		self.__student_repo = student_repo
	
	def get_students(self):
		''' Gets a list of all the students.
		output: list of Student
		'''
		return list(self.__student_repo.values())
	
	def add_student(self, student_id, name):
		''' Creates a student with given student_id, and name, and adds the student to the repository of students.
		input: student_id -- int, >= 1
		       name -- string, must not be empty
		raise: ValidatorException, if the student's data is invalid
		       ServiceException, if the student is already in the repository
		'''
		if not student_id in self.__student_repo:
			student = Student(student_id, name)
			self.__validator.validate(student)
			self.__student_repo[student_id] = student
		else:
			raise ServiceException("the given student_id is already in use")
