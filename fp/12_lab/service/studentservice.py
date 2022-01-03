from domain.entity import Student
from domain.validator import StudentValidator

from . import ServiceException
from repo import RepoException
from domain.validator import ValidatorException

import random, string

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
		return self.__student_repo.get_students()
	
	def add_student(self, student_id, name):
		''' Creates a student with given student_id, and name, and adds the student to the repository of students.
		input: student_id -- int, >= 1
		       name -- string, must not be empty
		raise: ValidatorException, if the student's data is invalid
		       RepoException, if the student is already in the repository
		'''
		student = Student(student_id, name)
		self.__validator.validate(student)
		self.__student_repo.store(student)
	
	def add_random_student(self):
		''' Creates a student with random student_id, and name, and adds the student too the repository of students.
		'''
		characters = string.ascii_lowercase + string.ascii_uppercase + " "
		
		name_len = random.randint(5, 50)
		name = ""
		for i in range(name_len):
			name += random.choice(characters)
		student_id = random.randint(1, 9999)
		student = Student(student_id, name)
		try:
			self.__validator.validate(student)
			self.__student_repo.store(student)
		except (RepoException, ValidatorException):
			self.add_random_student()
	
	def update_student(self, student_id, name):
		''' Updates the student with the given student_id.
		input: student_id -- int, >= 1
		       name -- string, must not be empty
		raise: ValidatorException, if the student's data is invalid
		       RepoException, if the student is not in the repository
		'''
		student = Student(student_id, name)
		self.__validator.validate(student)
		self.__student_repo.update(student)
	
	def find_student(self, student_id):
		''' Finds the student with the given student_id.
		input: student_id -- int, >= 1
		output: Student
		raise: ValidatorException, if the student's data is invalid
		       RepoException, if the student is not in the repository
		'''
		return self.__student_repo.find(student_id)
