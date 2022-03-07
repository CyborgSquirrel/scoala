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
		''' Update a grade.
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