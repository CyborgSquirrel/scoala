class StudentGradeDTO:
	def __init__(self, grade_id, student_id, discipline_id, value):
		''' Create student grade dto with given grade_id, student_id, discipline_id, and value.
		input: grade_id -- int, >= 1
		       student_id -- int, >= 1
		       discipline_id -- int, >= 1
		       value -- float, 1 <= value <= 10
		'''
		self.__grade_id = grade_id
		self.__student_id = student_id
		self.__discipline_id = discipline_id
		self.__value = value
		
		self.__student_name = None
	
	def get_grade_id(self):
		return self.__grade_id
	
	def get_student_id(self):
		return self.__student_id
	
	def get_discipline_id(self):
		return self.__discipline_id
	
	def get_value(self):
		return self.__value
	
	def get_student_name(self):
		return self.__student_name
	
	def set_student_name(self, student_name):
		self.__student_name = student_name

class StudentGradeAverageDTO:
	def __init__(self, student_name, average):
		''' Create a student grade average dto with given student_name, and average.
		input: student_name -- string, must not be empty
		       average -- float, 1 <= average <= 10
		'''
		self.__student_name = student_name
		self.__average = average
	
	def get_student_name(self):
		return self.__student_name
	
	def get_average(self):
		return self.__average