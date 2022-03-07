from . import RepoException

class InMemoryStudentRepo:
	def __init__(self):
		self.__students = {}
	
	def store(self, student):
		''' Store a student in the repo.
		input: student -- Student
		raise: RepoException, if there already is a student with the provided student's id
		'''
		if not student.get_student_id() in self.__students:
			self.__students[student.get_student_id()] = student
		else:
			raise RepoException("student is already in the repo")
	
	def update(self, student):
		''' Update a student.
		input: student -- Student
		raise: RepoException, if the student is not in the repo
		'''
		if student.get_student_id() in self.__students:
			self.__students[student.get_student_id()] = student
		else:
			raise RepoException("there is no such student in the repo")
	
	def erase(self, student_id):
		''' Erase a student from the repo.
		input: student_id -- int, >= 1
		raise: RepoException, if there is no student with student_id
		'''
		if not student_id in self.__students:
			raise RepoException("there is no student with the given student_id in the repo")
		else:
			del self.__students[student_id]
	
	def find(self, student_id):
		''' Find a student in the repo.
		input: student_id -- int, >= 1
		output: Student
		raise: RepoException, if there is no student with student_id
		'''
		if not student_id in self.__students:
			raise RepoException("there is no student with the given student_id in the repo")
		else:
			return self.__students[student_id]
	
	def get_students(self):
		''' Return a list of all the students.
		output: list of Student
		'''
		return list(self.__students.values())
