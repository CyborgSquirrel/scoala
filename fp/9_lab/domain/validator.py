class ValidatorException(Exception):
	def __init__(self, errors):
		self.__errors = errors
	
	def get_errors(self):
		return self.__errors
	
class StudentValidator:
	def validate(self, student):
		''' Validates a student.
		input: student -- Student
		raise: ValidatorException, if the student's data is invalid
		'''
		errors = ""
		
		student_id = student.get_student_id()
		if type(student_id) != int:
			errors += "student_id must be integer\n"
		elif student_id < 1:
			errors += "student_id must be >= 1\n"
		
		name = student.get_name()
		if type(name) != str:
			errors += "name must be string\n"
		elif name == "":
			errors += "name must not be empty\n"
		
		if len(errors) > 0:
			raise ValidatorException(errors)

class DisciplineValidator:
	def validate(self, discipline):
		''' Validates a discipline.
		input: discipline -- Discipline
		raise: ValidatorException, if the discipline's data is invalid
		'''
		errors = ""
		
		discipline_id = discipline.get_discipline_id()
		if type(discipline_id) != int:
			errors += "discipline_id must be integer\n"
		elif discipline_id < 1:
			errors += "discipline_id must be >= 1\n"
		
		name = discipline.get_name()
		if type(name) != str:
			errors += "name must be string\n"
		elif name == "":
			errors += "name must not be empty\n"
		
		professor = discipline.get_professor()
		if type(professor) != str:
			errors += "professor must be string\n"
		elif professor == "":
			errors += "professor name must not be empty\n"
		
		if len(errors) > 0:
			raise ValidatorException(errors)

class GradeValidator:
	def validate(self, grade):
		''' Validates a grade.
		input: grade -- Grade
		raise: ValidatorException, if the grade's data is invalid
		'''
		errors = ""
		
		grade_id = grade.get_grade_id()
		if type(grade_id) != int:
			errors += "grade_id must be integer\n"
		elif grade_id < 1:
			errors += "grade_id must be >= 1\n"
		
		student_id = grade.get_student_id()
		if type(student_id) != int:
			errors += "student_id must be integer\n"
		elif student_id < 1:
			errors += "student_id must be >= 1\n"
		
		discipline_id = grade.get_discipline_id()
		if type(discipline_id) != int:
			errors += "discipline_id must be integer\n"
		elif discipline_id < 1:
			errors += "discipline_id must be >= 1\n"
		
		value = grade.get_value()
		if type(value) not in [float, int]:
			errors += "value must be float or int\n"
		elif value < 1 or value > 10:
			errors += "value must be between 1 and 10\n"
		
		if len(errors) > 0:
			raise ValidatorException(errors)
