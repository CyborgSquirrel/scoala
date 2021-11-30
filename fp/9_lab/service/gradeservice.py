from domain.entity import Grade
from domain.validator import GradeValidator
from domain.dto import StudentGradeAverageDTO

from . import ServiceException

class GradeService:
	def __init__(self, validator, grade_repo, student_repo, discipline_repo):
		''' Create grade service with given validator.
		input: validator -- GradeValidator
		       grade_repo -- GradeRepository
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
		return self.__grade_repo.get_grades()
	
	def get_grades_with_discipline_sorted_by_criterion(self, discipline_id, criterion):
		''' Gets list of all the grades sorted by provided criterion.
		input: criterion -- string, "name", or "grade"
		       discipline_id -- int, >= 1
		output: list of StudentGradeDTO
		raise: ServiceException, if the criterion is invalid
		       RepoException, if there is no discipline with discipline_id
		'''
		self.__discipline_repo.find(discipline_id)
		
		student_grade_dtos = self.__grade_repo.get_student_grades_by_discipline_id(discipline_id)
		reverse = False
		if criterion == "name":
			def key(a):
				student = self.__student_repo.find(a.get_student_id())
				return student.get_name()
		elif criterion == "grade":
			reverse = True
			def key(a):
				return a.get_value()
		else:
			raise ServiceException("invalid criterion")
		
		student_grade_dtos.sort(key=key, reverse=reverse)
		
		for grade in student_grade_dtos:
			student_name = self.__student_repo.find(grade.get_student_id()).get_name()
			grade.set_student_name(student_name)
		
		return student_grade_dtos
	
	def get_top_20_percent_of_students(self):
		''' Gets the top 20% of the students' student_ids, by the total average of their grades.
		output: list of StudentGradeAverageDTO
		'''
		grades = self.__grade_repo.get_grades()
		student_grade_sum = {}
		student_grade_amount = {}
		for grade in grades:
			student_id = grade.get_student_id()
			
			if not student_id in student_grade_sum:
				student_grade_sum[student_id] = 0
			if not student_id in student_grade_amount:
				student_grade_amount[student_id] = 0
			
			student_grade_sum[student_id] += grade.get_value()
			student_grade_amount[student_id] += 1
		
		students = self.__student_repo.get_students()
		student_grade_average_dtos = []
		for student in students:
			student_id = student.get_student_id()
			if student_id in student_grade_sum and student_id in student_grade_amount:
				grade_average = student_grade_sum[student_id] / student_grade_amount[student_id]
				
				student_grade_average_dto = StudentGradeAverageDTO(student.get_name(), grade_average)
				student_grade_average_dtos.append(student_grade_average_dto)
		
		def key(a):
			return a.get_average()
		student_grade_average_dtos.sort(key=key, reverse=True)
		
		cutoff = int(len(student_grade_average_dtos) * 0.20)
		return student_grade_average_dtos[:cutoff]
	
	def get_top_3_students_by_average(self):
		''' Gets the top 3 students by their average grade.
		output: list of StudentGradeAverageDTO
		raise: ServiceException, if there are fewer than 3 students
		'''
		if self.__student_repo.get_len() < 3:
			raise ServiceException("too few students\n")
		
		grades = self.__grade_repo.get_grades()
		student_grade_sum = {}
		student_grade_amount = {}
		for grade in grades:
			student_id = grade.get_student_id()
			
			if not student_id in student_grade_sum:
				student_grade_sum[student_id] = 0
			if not student_id in student_grade_amount:
				student_grade_amount[student_id] = 0
			
			student_grade_sum[student_id] += grade.get_value()
			student_grade_amount[student_id] += 1
		
		students = self.__student_repo.get_students()
		student_grade_average_dtos = []
		for student in students:
			student_id = student.get_student_id()
			if student_id in student_grade_sum and student_id in student_grade_amount:
				grade_average = student_grade_sum[student_id] / student_grade_amount[student_id]
				
				student_grade_average_dto = StudentGradeAverageDTO(student.get_name(), grade_average)
				student_grade_average_dtos.append(student_grade_average_dto)
		
		def key(a):
			return a.get_average()
		student_grade_average_dtos.sort(key=key, reverse=True)
		
		return student_grade_average_dtos[:3]
		
	
	def add_grade(self, grade_id, student_id, discipline_id, value):
		''' Creates a grade with given grade_id, and name, and adds the grade to the repository of grades.
		input: grade_id -- int, >= 1
		       student_id -- int, >= 1
		       discipline_id -- int, >= 1
		       value -- float, 1 <= value <= 10
		raise: ValidatorException, if the grade's data is invalid
		       RepoException, if the grade is already in the repository
		                      if there is no student with student_id
		                      if there is no discipline with discipline_id
		'''
		grade = Grade(grade_id, student_id, discipline_id, value)
		self.__validator.validate(grade)
		
		self.__student_repo.find(student_id)
		self.__discipline_repo.find(discipline_id)
		
		self.__grade_repo.store(grade)
	
	def erase_grade(self, grade_id):
		''' Erases the grade with grade_id.
		input: grade_id -- int, >= 1
		raise: RepoException, if the grade is not in the repository
		'''
		self.__grade_repo.erase(grade_id)
	
	def find_grade(self, grade_id):
		''' Finds the grade with the given grade_id.
		input: grade_id -- int, >= 1
		output: Grade
		raise: ValidatorException, if the grade's data is invalid
		       RepoException, if the grade is not in the repository
		'''
		return self.__grade_repo.find(grade_id)
	
	def erase_student_and_all_their_grades(self, student_id):
		''' Erases the student with student_id, and all their grades.
		input: student_id -- int, >= 1
		raise: RepoException, if the student is not in the repository
		'''
		self.__student_repo.find(student_id)
		for grade in self.__grade_repo.get_grades():
			grade_id = grade.get_grade_id()
			if grade.get_student_id() == student_id:
				self.erase_grade(grade_id)
		self.__student_repo.erase(student_id)
	
	def erase_discipline_and_all_its_grades(self, discipline_id):
		''' Erases the discipline with discipline_id, and all its grades.
		input: discipline_id -- int, >= 1
		raise: RepoException, if the discipline is not in the repository
		'''
		self.__discipline_repo.find(discipline_id)
		for grade in self.__grade_repo.get_grades():
			grade_id = grade.get_grade_id()
			if grade.get_discipline_id() == discipline_id:
				self.erase_grade(grade_id)
		self.__discipline_repo.erase(discipline_id)
	
	def find_lowest_grade(self):
		''' Finds the grade with the lowest value.
		output: lowest_grade -- Grade
		raise: ServiceException, if there are no grades
		'''
		lowest_grade = None
		for grade in self.__grade_repo.get_grades():
			if lowest_grade == None or grade.get_value() < lowest_grade.get_value():
				lowest_grade = grade
		
		if lowest_grade == None:
			raise ServiceException("there are no grades")
		else:
			return lowest_grade