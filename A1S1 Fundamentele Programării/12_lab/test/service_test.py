from service.studentservice import StudentService
from service.disciplineservice import DisciplineService
from service.gradeservice import GradeService

from repo.studentrepo import InMemoryStudentRepo
from repo.disciplinerepo import InMemoryDisciplineRepo
from repo.graderepo import InMemoryGradeRepo

from domain.validator import \
StudentValidator, DisciplineValidator, GradeValidator

from domain.entity import \
Student, Discipline, Grade

from service import ServiceException

import unittest

class TestStudentService(unittest.TestCase):
	def setUp(self):
		validator = StudentValidator()
		repo = InMemoryStudentRepo()
		self.service = StudentService(validator, repo)
	
	def test_get_students(self):
		service = self.service
		
		service.add_student(1, "Kujo Jotaro")
		service.add_student(2, "Dio Brando")
		
		self.assertEqual(
			service.get_students(),
			[ Student(1, "Kujo Jotaro"), Student(2, "Dio Brando") ],
		)

	def test_add_student(self):
		service = self.service
		
		service.add_student(1, "Jojo")

	def test_update_student(self):
		service = self.service
		
		service.add_student(1, "Jojo")
		service.update_student(1, "Jonno")

	def test_find_student(self):
		service = self.service
		
		service.add_student(1, "Jojo")
		self.assertEqual(service.find_student(1), Student(1, "Jojo"))

class TestDisciplineService(unittest.TestCase):
	def setUp(self):
		validator = DisciplineValidator()
		repo = InMemoryDisciplineRepo()
		self.service = DisciplineService(validator, repo)
	
	def test_get_disciplines(self):
		service = self.service
		
		service.add_discipline(1, "Mathematics", "John Doe")
		service.add_discipline(2, "PE", "Jeff")
		
		self.assertEqual(
			service.get_disciplines(),
			[ Discipline(1, "Mathematics", "John Doe"), Discipline(2, "PE", "Jeff") ],
		)

	def test_add_discipline(self):
		service = self.service
		
		service.add_discipline(1, "Mathematics", "John Doe")

	def test_update_discipline(self):
		service = self.service
		
		service.add_discipline(1, "Mathematics", "Pythagoras")
		service.update_discipline(1, "Geometry", "Pythagoras")

	def test_find_discipline(self):
		service = self.service
		
		service.add_discipline(1, "Literature", "Mihai Eminescu")
		self.assertEqual(
			service.find_discipline(1),
			Discipline(1, "Literature", "Mihai Eminescu"),
		)

class TestGradeService(unittest.TestCase):
	def setUp(self):
		student_validator = StudentValidator()
		student_repo = InMemoryStudentRepo()
		self.student_service = StudentService(student_validator, student_repo)

		discipline_validator = DisciplineValidator()
		discipline_repo = InMemoryDisciplineRepo()
		self.discipline_service = DisciplineService(discipline_validator, discipline_repo)

		grade_validator = GradeValidator()
		grade_repo = InMemoryGradeRepo()
		self.grade_service = GradeService(grade_validator, grade_repo, student_repo, discipline_repo)

	def test_get_grades(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		student_service.add_student(1, "Joseph")
		student_service.add_student(2, "Bobo")
		discipline_service.add_discipline(1, "Arithmetic", "Jim")
		grade_service.add_grade(1, 1, 1, 9.5)
		grade_service.add_grade(2, 2, 1, 4.2)
		grade_service.add_grade(3, 2, 1, 7.9)
		
		self.assertEqual( 
			grade_service.get_grades(),
			[ Grade(1, 1, 1, 9.5), Grade(2, 2, 1, 4.2), Grade(3, 2, 1, 7.9) ],
		)

	def test_add_grade(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Andrei")
		discipline_service.add_discipline(1, "Mathematics", "John Doe")
		
		grade_service.add_grade(1, 1, 1, 10)

	def test_find_grade(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Jojo")
		discipline_service.add_discipline(1, "Philosophy", "Tom Hanks")
		grade_service.add_grade(1, 1, 1, 9.5)
		
		assert grade_service.find_grade(1) == Grade(1, 1, 1, 9.5)
	
	def test_get_grades_sorted_by_student_name_and_value(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Harry Potter")
		student_service.add_student(2, "Hermione Granger")
		
		discipline_service.add_discipline(1, "Potions", "Snape")
		discipline_service.add_discipline(2, "Defense", "Loony")
		
		grade_service.add_grade(1, 1, 1, 9)
		grade_service.add_grade(2, 1, 2, 4.4)
		grade_service.add_grade(3, 2, 1, 9.2)
		grade_service.add_grade(4, 2, 2, 7.9)
		
		sorted_grades = grade_service.get_grades_sorted_by_student_name_and_value()
		
		self.assertEqual(sorted_grades[0].get_student_name(), "Harry Potter")
		self.assertEqual(sorted_grades[0].get_value(), 4.4)
		self.assertEqual(sorted_grades[1].get_student_name(), "Harry Potter")
		self.assertEqual(sorted_grades[1].get_value(), 9)
		self.assertEqual(sorted_grades[2].get_student_name(), "Hermione Granger")
		self.assertEqual(sorted_grades[2].get_value(), 7.9)
		self.assertEqual(sorted_grades[3].get_student_name(), "Hermione Granger")
		self.assertEqual(sorted_grades[3].get_value(), 9.2)
	
	def test_get_grades_with_discipline_sorted_by_criterion(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Otilia Marculescu")
		student_service.add_student(2, "Felix Sima")
		
		discipline_service.add_discipline(1, "Religion", "Simion Tulea")
		discipline_service.add_discipline(2, "War", "Aglae Tulea")
		discipline_service.add_discipline(3, "Politics", "Stanica Ratiu")
		
		grade_service.add_grade(1, 1, 1, 7)
		grade_service.add_grade(2, 1, 1, 6.5)
		grade_service.add_grade(3, 1, 2, 5.25)
		grade_service.add_grade(4, 1, 3, 9.5)
		
		grade_service.add_grade(5, 2, 1, 7.5)
		grade_service.add_grade(6, 2, 2, 8.5)
		grade_service.add_grade(7, 2, 3, 10)
		
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(1, "name")), 3)
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(2, "name")), 2)
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(3, "name")), 2)
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(1, "grade")), 3)
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(2, "grade")), 2)
		self.assertEqual(len(grade_service.get_grades_with_discipline_sorted_by_criterion(3, "grade")), 2)
		
		with self.assertRaises(ServiceException) as ex:
			grade_service.get_grades_with_discipline_sorted_by_criterion(2, "awesomeness")
		self.assertEqual(ex.exception.get_errors(), "invalid criterion")

	def test_get_top_20_percent_of_students(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Otilia Marculescu")
		student_service.add_student(2, "Felix Sima")
		student_service.add_student(3, "Titi Tulea")
		student_service.add_student(4, "Aurica Tulea")
		student_service.add_student(5, "Olimpia")
		
		discipline_service.add_discipline(1, "Religion", "Simion Tulea")
		discipline_service.add_discipline(2, "War", "Aglae Tulea")
		discipline_service.add_discipline(3, "Politics", "Stanica Ratiu")
		
		grade_service.add_grade( 1, 1, 1, 9.5)
		grade_service.add_grade( 2, 1, 2, 7)
		grade_service.add_grade( 3, 1, 3, 7.5)
		
		grade_service.add_grade( 4, 2, 1, 10)
		grade_service.add_grade( 5, 2, 2, 9.5)
		grade_service.add_grade( 6, 2, 3, 9.75)
		
		grade_service.add_grade( 7, 3, 1, 7.25)
		grade_service.add_grade( 8, 3, 2, 6.5)
		grade_service.add_grade( 9, 3, 3, 4)
		
		grade_service.add_grade(10, 4, 1, 7.5)
		grade_service.add_grade(11, 4, 2, 3.5)
		grade_service.add_grade(12, 4, 3, 5)
		
		grade_service.add_grade(13, 5, 1, 8.75)
		grade_service.add_grade(14, 5, 2, 7)
		grade_service.add_grade(15, 5, 3, 9)
		
		top = grade_service.get_top_20_percent_of_students()[0]
		self.assertEqual(top.get_student_name(), "Felix Sima")
		self.assertEqual(top.get_average(), (10+9.5+9.75)/3)

	def test_get_top_3_students_by_average(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		with self.assertRaises(ServiceException) as ex:
			grade_service.get_top_3_students_by_average()
		self.assertEqual(ex.exception.get_errors(), "too few students\n")
		
		student_service.add_student(1, "Andrei")
		student_service.add_student(2, "Andrei'")
		student_service.add_student(3, "Andrei''")
		student_service.add_student(4, "Andrei'''")
		
		discipline_service.add_discipline(1, "John Doe", "Mathematics")
		discipline_service.add_discipline(2, "Dohn Joe", "Informatics")
		
		grade_service.add_grade(1, 1, 1, 9.7)
		grade_service.add_grade(2, 1, 2, 8)
		
		grade_service.add_grade(3, 2, 1, 5.2)
		grade_service.add_grade(4, 2, 2, 10)
		
		grade_service.add_grade(5, 3, 1, 4.1)
		grade_service.add_grade(6, 3, 2, 4.1)
		
		grade_service.add_grade(7, 4, 1, 8.3)
		grade_service.add_grade(8, 4, 2, 6.2)
		
		top_3_students = grade_service.get_top_3_students_by_average()
		self.assertEqual(top_3_students[0].get_student_name(), "Andrei")
		self.assertEqual(top_3_students[0].get_average(), (9.7+8)/2)
		self.assertEqual(top_3_students[1].get_student_name(), "Andrei'")
		self.assertEqual(top_3_students[1].get_average(), (5.2+10)/2)
		self.assertEqual(top_3_students[2].get_student_name(), "Andrei'''")
		self.assertEqual(top_3_students[2].get_average(), (8.3+6.2)/2)

	def test_erase_grade(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Jonno")
		student_service.add_student(2, "Niko")
		discipline_service.add_discipline(1, "Mathematics", "John Doe")
		grade_service.add_grade(1, 1, 1, 9.5)
		grade_service.add_grade(2, 2, 1, 4.2)
		
		grade_service.erase_grade(1)
		grade_service.erase_grade(2)

	def test_erase_student_and_all_their_grades(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Jonno")
		student_service.add_student(2, "Niko")
		discipline_service.add_discipline(1, "Mathematics", "John Doe")
		grade_service.add_grade(1, 1, 1, 9.5)
		grade_service.add_grade(2, 1, 1, 9.9)
		grade_service.add_grade(3, 2, 1, 4.2)
		grade_service.add_grade(4, 2, 1, 4.1)
		grade_service.add_grade(5, 2, 1, 7.7)
		
		grade_service.erase_student_and_all_their_grades(1)
		grade_service.erase_student_and_all_their_grades(2)

	def test_erase_discipline_and_all_its_grades(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		student_service.add_student(1, "Niko")
		discipline_service.add_discipline(1, "Mathematics", "John Doe")
		discipline_service.add_discipline(2, "Informatics", "Joe Generic")
		grade_service.add_grade(1, 1, 1, 3.2)
		grade_service.add_grade(2, 1, 1, 1.2)
		grade_service.add_grade(3, 1, 1, 7.5)
		grade_service.add_grade(4, 1, 2, 7.6)
		grade_service.add_grade(5, 1, 2, 8.1)
		
		grade_service.erase_discipline_and_all_its_grades(1)
		grade_service.erase_discipline_and_all_its_grades(2)
		
	def test_find_lowest_grade(self):
		student_service, discipline_service, grade_service = \
			self.student_service, self.discipline_service, self.grade_service
		
		with self.assertRaises(ServiceException) as ex:
			grade_service.find_lowest_grade()
		self.assertEqual(ex.exception.get_errors(), "there are no grades")
		
		student_service.add_student(1, "Keith Pete")
		student_service.add_student(2, "Simple Student")
		discipline_service.add_discipline(1, "Mathematics", "Lebowski")
		grade_service.add_grade(1, 1, 1, 3.3)
		grade_service.add_grade(2, 2, 1, 9.5)
		grade_service.add_grade(3, 2, 1, 7.25)
		
		self.assertEqual(grade_service.find_lowest_grade(), Grade(1, 1, 1, 3.3))
