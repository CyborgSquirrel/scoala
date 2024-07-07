from domain.entity import Student, Discipline, Grade
from domain.validator import StudentValidator, DisciplineValidator, GradeValidator
from domain.validator import ValidatorException

import unittest

class TestValidators(unittest.TestCase):
	def test_student_validator(self):
		student_id = 1
		name = "Kujo Jotaro"
		
		invalid_student_id = -2
		invalid_name = ""
		
		validator = StudentValidator()	
		validator.validate(Student(student_id, name))
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Student(invalid_student_id, name))
		self.assertEqual(ex.exception.get_errors(), "student_id must be >= 1\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Student(student_id, invalid_name))
		self.assertEqual(ex.exception.get_errors(), "name must not be empty\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Student(invalid_student_id, invalid_name))
		self.assertEqual(ex.exception.get_errors(), "student_id must be >= 1\nname must not be empty\n")

	def test_discipline_validator(self):
		discipline_id = 2
		name = "Romanian Language and Literature"
		professor = "DIO"
		
		invalid_discipline_id = -123
		invalid_name = ""
		invalid_professor = ""
		
		validator = DisciplineValidator()
		
		# valid
		validator.validate(Discipline(discipline_id, name, professor))
		
		# 1 invalid parameter
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(invalid_discipline_id, name, professor))
		self.assertEqual(ex.exception.get_errors(), "discipline_id must be >= 1\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(discipline_id, invalid_name, professor))
		self.assertEqual(ex.exception.get_errors(), "name must not be empty\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(discipline_id, name, invalid_professor))
		self.assertEqual(ex.exception.get_errors(), "professor name must not be empty\n")
		
		# 2 invalid parameters
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(invalid_discipline_id, invalid_name, professor))
		self.assertEqual(ex.exception.get_errors(), "discipline_id must be >= 1\nname must not be empty\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(invalid_discipline_id, name, invalid_professor))
		self.assertEqual(ex.exception.get_errors(), "discipline_id must be >= 1\nprofessor name must not be empty\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(discipline_id, invalid_name, invalid_professor))
		self.assertEqual(ex.exception.get_errors(), "name must not be empty\nprofessor name must not be empty\n")
		
		# 3 invalid parameters
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Discipline(invalid_discipline_id, invalid_name, invalid_professor))
		self.assertEqual(ex.exception.get_errors(), "discipline_id must be >= 1\nname must not be empty\nprofessor name must not be empty\n")

	def test_grade_validator(self):
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
		validator.validate(Grade(grade_id, student_id, discipline_id, value))
		
		# 1 invalid parameter
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Grade(grade_id, student_id, discipline_id, invalid_value))
		self.assertEqual(ex.exception.get_errors(), "value must be between 1 and 10\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Grade(grade_id, invalid_student_id, discipline_id, value))
		self.assertEqual(ex.exception.get_errors(), "student_id must be >= 1\n")
		
		# 2 invalid parameters
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Grade(grade_id, invalid_student_id, discipline_id, invalid_value))
		self.assertEqual(ex.exception.get_errors(), "student_id must be >= 1\nvalue must be between 1 and 10\n")
		
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Grade(invalid_grade_id, student_id, invalid_discipline_id, value))
		self.assertEqual(ex.exception.get_errors(), "grade_id must be >= 1\ndiscipline_id must be >= 1\n")
		
		# 4 invalid parameters
		with self.assertRaises(ValidatorException) as ex:
			validator.validate(Grade(invalid_grade_id, invalid_student_id, invalid_discipline_id, invalid_value))
		self.assertEqual(ex.exception.get_errors(), "grade_id must be >= 1\nstudent_id must be >= 1\ndiscipline_id must be >= 1\nvalue must be between 1 and 10\n")
