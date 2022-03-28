from domain.entity import Student, Discipline, Grade
from domain.validator import StudentValidator, DisciplineValidator, GradeValidator
from domain.validator import ValidatorException

def test_student_validator():
	student_id = 1
	name = "Kujo Jotaro"
	
	invalid_student_id = -2
	invalid_name = ""
	
	validator = StudentValidator()	
	try:
		validator.validate(Student(student_id, name))
	except ValidatorException:
		assert False
	
	try:
		validator.validate(Student(invalid_student_id, name))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "student_id must be >= 1\n"
	
	try:
		validator.validate(Student(student_id, invalid_name))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "name must not be empty\n"
	
	try:
		validator.validate(Student(invalid_student_id, invalid_name))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "student_id must be >= 1\nname must not be empty\n"

def test_discipline_validator():
	discipline_id = 2
	name = "Romanian Language and Literature"
	professor = "DIO"
	
	invalid_discipline_id = -123
	invalid_name = ""
	invalid_professor = ""
	
	validator = DisciplineValidator()
	
	# valid
	try:
		validator.validate(Discipline(discipline_id, name, professor))
	except ValidatorException:
		assert False
	
	# 1 invalid parameter
	try:
		validator.validate(Discipline(invalid_discipline_id, name, professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "discipline_id must be >= 1\n"
	
	try:
		validator.validate(Discipline(discipline_id, invalid_name, professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "name must not be empty\n"
	
	try:
		validator.validate(Discipline(discipline_id, name, invalid_professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "professor name must not be empty\n"
	
	# 2 invalid parameters
	try:
		validator.validate(Discipline(invalid_discipline_id, invalid_name, professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "discipline_id must be >= 1\nname must not be empty\n"
	
	try:
		validator.validate(Discipline(invalid_discipline_id, name, invalid_professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "discipline_id must be >= 1\nprofessor name must not be empty\n"
	
	try:
		validator.validate(Discipline(discipline_id, invalid_name, invalid_professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "name must not be empty\nprofessor name must not be empty\n"
	
	# 3 invalid parameters
	try:
		validator.validate(Discipline(invalid_discipline_id, invalid_name, invalid_professor))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "discipline_id must be >= 1\nname must not be empty\nprofessor name must not be empty\n"

def test_grade_validator():
	grade_id = 1
	student_id = 77
	discipline_id = 12
	value = 9.5
	
	invalid_grade_id = -15
	invalid_student_id = -7
	invalid_discipline_id = -127
	invalid_value = 10.20
	
	validator = GradeValidator()
	
	# valid
	try:
		validator.validate(Grade(grade_id, student_id, discipline_id, value))
	except ValidatorException:
		assert False
	
	# 1 invalid parameter
	try:
		validator.validate(Grade(grade_id, student_id, discipline_id, invalid_value))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "value must be between 1 and 10\n"
	
	try:
		validator.validate(Grade(grade_id, invalid_student_id, discipline_id, value))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "student_id must be >= 1\n"
	
	# 2 invalid parameters
	try:
		validator.validate(Grade(grade_id, invalid_student_id, discipline_id, invalid_value))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "student_id must be >= 1\nvalue must be between 1 and 10\n"
	
	try:
		validator.validate(Grade(invalid_grade_id, student_id, invalid_discipline_id, value))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "grade_id must be >= 1\ndiscipline_id must be >= 1\n"
	
	# 4 invalid parameters
	try:
		validator.validate(Grade(invalid_grade_id, invalid_student_id, invalid_discipline_id, invalid_value))
		assert False
	except ValidatorException as ex:
		assert ex.get_errors() == "grade_id must be >= 1\nstudent_id must be >= 1\ndiscipline_id must be >= 1\nvalue must be between 1 and 10\n"

def run_domain_tests():
	test_student_validator()
	test_discipline_validator()
	test_grade_validator()