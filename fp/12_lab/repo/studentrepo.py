from . import RepoException
from domain.entity import Student

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
		''' Update a student in the repo.
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
	
	def get_len(self):
		''' Returns number of students.
		output: int
		'''
		return len(self.__students)

class FileStudentRepo(InMemoryStudentRepo):
	def __init__(self, filename):
		super().__init__()
		self.__filename = filename
		self.__load_all_from_file()
	
	def __load_all_from_file(self):
		try:
			with open(self.__filename, "r") as f:
				for line in f:
					if line[-1] == '\n':
						line = line[:-1]
					if line.strip() != "":
						line = line.split(";")
						student = Student(int(line[0]), line[1])
						super().store(student)
		except FileNotFoundError:
			with open(self.__filename, "w") as f:
				pass
	
	def __store_all_to_file(self):
		with open(self.__filename, "w") as f:
			students = super().get_students()
			for student in students:
				print(f"{student.get_student_id()};{student.get_name()}", file=f)
	
	def store(self, student):
		''' Store a student in the repo (and in the file).
		input: student -- Student
		raise: RepoException, if there already is a student with the provided student's id
		'''
		super().store(student)
		self.__store_all_to_file()
	
	def update(self, student):
		''' Update a student in the repo (and in the file).
		input: student -- Student
		raise: RepoException, if the student is not in the repo
		'''
		super().update(student)
		self.__store_all_to_file()
	
	def erase(self, student_id):
		''' Erase a student from the repo (and in the file).
		input: student_id -- int, >= 1
		raise: RepoException, if there is no student with student_id
		'''
		super().erase(student_id)
		self.__store_all_to_file()