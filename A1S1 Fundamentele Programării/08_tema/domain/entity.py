class Student:
	def __init__(self, student_id, name):
		''' Create student with given student_id, and name.
		input: student_id -- int, >= 1
		       name -- string, must not be empty
		'''
		self.__student_id = student_id
		self.__name = name
	
	def get_student_id(self):
		return self.__student_id
	
	def get_name(self):
		return self.__name
	
	def __eq__(self, other):
		if type(self) != type(other): return False
		return self.get_student_id() == other.get_student_id()
	
	def __str__(self):
		return f"{self.get_student_id()}@{self.get_name()}"

class Discipline:
	def __init__(self, discipline_id, name, professor):
		''' Create student with given discipline_id, name, and professor.
		input: discipline_id -- int, >= 1
		       name -- string, must not be empty
		       professor -- string, must not be empty
		'''
		self.__discipline_id = discipline_id
		self.__name = name
		self.__professor = professor
	
	def get_discipline_id(self):
		return self.__discipline_id
	
	def get_name(self):
		return self.__name
	
	def get_professor(self):
		return self.__professor
	
	def __eq__(self, other):
		if type(self) != type(other): return False
		return self.get_discipline_id() == other.get_discipline_id()
	
	def __str__(self):
		return f"{self.get_discipline_id()}@{self.get_name()}~{self.get_professor()}"

class Grade:
	def __init__(self, grade_id, student_id, discipline_id, value):
		''' Create student with given student_id, and discipline_id.
		input: grade_id -- int, >= 1
		       student_id -- int, >= 1
		       discipline_id -- int, >= 1
		       value -- float, 1 <= value <= 10
		'''
		self.__grade_id = grade_id
		self.__student_id = student_id
		self.__discipline_id = discipline_id
		self.__value = value
	
	def get_grade_id(self):
		return self.__grade_id
	
	def get_student_id(self):
		return self.__student_id
	
	def get_discipline_id(self):
		return self.__discipline_id
	
	def get_value(self):
		return self.__value
	
	def __eq__(self, other):
		if type(self) != type(other): return False
		return self.get_grade_id() == other.get_grade_id()
	
	def __str__(self):
		return f"{self.get_grade_id()}@{self.get_student_id()}@{self.get_discipline_id()}~{self.get_value()}"