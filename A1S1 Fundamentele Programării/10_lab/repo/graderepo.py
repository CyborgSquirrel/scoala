from domain.dto import StudentGradeDTO
from domain.entity import Grade

from . import RepoException

class InMemoryGradeRepo:
	def __init__(self):
		self.__grades = {}
	
	def store(self, grade):
		''' Store a grade in the repo.
		input: grade -- Grade
		raise: RepoException, if there already is a grade with the provided grade's id
		'''
		if not grade.get_grade_id() in self.__grades:
			self.__grades[grade.get_grade_id()] = grade
		else:
			raise RepoException("grade is already in the repo")
	
	def update(self, grade):
		''' Update a grade in the repo.
		input: grade -- Grade
		raise: RepoException, if the grade is not in the repo
		'''
		if grade.get_grade_id() in self.__grades:
			self.__grades[grade.get_grade_id()] = grade
		else:
			raise RepoException("there is no such grade in the repo")
	
	def erase(self, grade_id):
		''' Erase a grade from the repo.
		input: grade_id -- int, >= 1
		raise: RepoException, if there is no grade with grade_id
		'''
		if not grade_id in self.__grades:
			raise RepoException("there is no grade with the given grade_id in the repo")
		else:
			del self.__grades[grade_id]
	
	def find(self, grade_id):
		''' Find a grade in the repo.
		input: grade_id -- int, >= 1
		output: Grade
		raise: RepoException, if there is no grade with grade_id
		'''
		if not grade_id in self.__grades:
			raise RepoException("there is no grade with the given grade_id in the repo")
		else:
			return self.__grades[grade_id]
	
	def get_grades(self):
		''' Return a list of all the grades.
		output: list of Grade
		'''
		return list(self.__grades.values())
	
	def get_len(self):
		''' Returns number of grades.
		output: int
		'''
		return len(self.__grades)
	
	def get_student_grades_by_discipline_id(self, discipline_id):
		''' Returns a list of all the grades with specified discipline_id.
		input: discipline_id -- int, >= 1
		output: list of StudentGradeDTO
		'''
		student_grade_dtos = []
		for grade in self.__grades.values():
			if grade.get_discipline_id() == discipline_id:
				student_grade_dto = StudentGradeDTO(
					grade.get_grade_id(),
					grade.get_student_id(),
					grade.get_discipline_id(),
					grade.get_value(),
				)
				
				student_grade_dtos.append(student_grade_dto)
		return student_grade_dtos

class FileGradeRepo(InMemoryGradeRepo):
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
							grade_id = int(line)
						elif index == 1:
							student_id = int(line)
						elif index == 2:
							discipline_id = int(line)
						elif index == 3:
							value = float(line)
							
							grade = Grade(grade_id, student_id, discipline_id, value)
							super().store(grade)
						
						index += 1
						index %= 4
						
		except FileNotFoundError:
			with open(self.__filename, "w") as f:
				pass
	
	def __store_all_to_file(self):
		with open(self.__filename, "w") as f:
			grades = super().get_grades()
			for grade in grades:
				print(f"{grade.get_grade_id()}\n{grade.get_student_id()}\n{grade.get_discipline_id()}\n{grade.get_value()}", file=f)
	
	def store(self, grade):
		''' Store a grade in the repo (and in the file).
		input: grade -- Grade
		raise: RepoException, if there already is a grade with the provided grade's id
		'''
		super().store(grade)
		self.__store_all_to_file()
	
	def update(self, grade):
		''' Update a grade in the repo (and in the file).
		input: grade -- Grade
		raise: RepoException, if the grade is not in the repo
		'''
		super().update(grade)
		self.__store_all_to_file()
	
	def erase(self, grade_id):
		''' Erase a grade from the repo (and in the file).
		input: grade_id -- int, >= 1
		raise: RepoException, if there is no grade with grade_id
		'''
		super().erase(grade_id)
		self.__store_all_to_file()