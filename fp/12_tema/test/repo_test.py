from repo import RepoException

from domain.entity import \
Student, Discipline, Grade

from repo.studentrepo import InMemoryStudentRepo, FileStudentRepo
from repo.disciplinerepo import InMemoryDisciplineRepo, FileDisciplineRepo
from repo.graderepo import InMemoryGradeRepo, FileGradeRepo

from shutil import copyfile

import unittest

''' INMEMORY '''

class TestInMemoryStudentRepo(unittest.TestCase):
	def test_store(self):
		repo = InMemoryStudentRepo()
		
		repo.store(Student(1, "Jojo"))
		
		with self.assertRaises(RepoException) as ex:
			repo.store(Student(1, "Dio"))
		self.assertEqual(ex.exception.get_errors(), "student is already in the repo")

	def test_update(self):
		repo = InMemoryStudentRepo()
		
		repo.store(Student(1, "Jojo"))
		repo.update(Student(1, "Dio"))
		
		with self.assertRaises(RepoException) as ex:
			repo.update(Student(2, "Giorno"))
		self.assertEqual(ex.exception.get_errors(), "there is no such student in the repo")

	def test_erase(self):
		repo = InMemoryStudentRepo()
		
		repo.store(Student(1, "Jojo"))
		repo.erase(1)
		
		with self.assertRaises(RepoException) as ex:
			repo.erase(1)
		self.assertEqual(ex.exception.get_errors(), "there is no student with the given student_id in the repo")

	def test_find(self):
		repo = InMemoryStudentRepo()
		
		student = Student(1, "Jojo")
		repo.store(student)
		
		self.assertEqual(repo.find(student.get_student_id()), student)
		
		with self.assertRaises(RepoException) as ex:
			repo.find(2)
		self.assertEqual(ex.exception.get_errors(), "there is no student with the given student_id in the repo")

	def test_get_len(self):
		repo = InMemoryStudentRepo()
		
		repo.store(Student(1, "Jojo"))
		self.assertEqual(repo.get_len(), 1)
		
		repo.store(Student(2, "Dio"))
		self.assertEqual(repo.get_len(), 2)

class TestInMemoryDisciplineRepo(unittest.TestCase):
	def test_store(self):
		repo = InMemoryDisciplineRepo()
		
		repo.store(Discipline(1, "Mathematics", "John Doe"))
		
		with self.assertRaises(RepoException) as ex:
			repo.store(Discipline(1, "Informatics", "Jimbo"))
		self.assertEqual(ex.exception.get_errors(), "discipline is already in the repo")

	def test_update(self):
		repo = InMemoryDisciplineRepo()
		
		repo.store(Discipline(1, "Mathematics", "Dohn Joe"))
		repo.update(Discipline(1, "PE", "Jamal"))
		
		with self.assertRaises(RepoException) as ex:
			repo.update(Discipline(2, "Nice Discipline", "Nice Professor"))
		self.assertEqual(ex.exception.get_errors(), "there is no such discipline in the repo")

	def test_erase(self):
		repo = InMemoryDisciplineRepo()
		
		repo.store(Discipline(1, "Mathematics", "Tom Hardy"))
		repo.erase(1)
		
		with self.assertRaises(RepoException) as ex:
			repo.erase(1)
		self.assertEqual(ex.exception.get_errors(), "there is no discipline with the given discipline_id in the repo")

	def test_find(self):
		repo = InMemoryDisciplineRepo()
		
		discipline = Discipline(1, "Mathematics", "Euler")
		repo.store(discipline)
		
		self.assertEqual(repo.find(discipline.get_discipline_id()), discipline)
		
		with self.assertRaises(RepoException) as ex:
			repo.find(2)
		self.assertEqual(ex.exception.get_errors(), "there is no discipline with the given discipline_id in the repo")

	def test_get_len(self):
		repo = InMemoryDisciplineRepo()
		
		repo.store(Discipline(1, "Philosophy", "Friedrich Nietzche"))
		self.assertEqual(repo.get_len(), 1)
		
		repo.store(Discipline(2, "Informatics", "Donald Knuth"))
		self.assertEqual(repo.get_len(), 2)

class TestInMemoryGradeRepo(unittest.TestCase):
	def test_store(self):
		repo = InMemoryGradeRepo()
		
		repo.store(Grade(1, 1, 1, 10))
		
		with self.assertRaises(RepoException) as ex:
			repo.store(Grade(1, 2, 1, 9.5))
		self.assertEqual(ex.exception.get_errors(), "grade is already in the repo")

	def test_update(self):
		repo = InMemoryGradeRepo()
		
		repo.store(Grade(1, 1, 1, 7))
		repo.update(Grade(1, 1, 1, 10))
		
		with self.assertRaises(RepoException) as ex:
			repo.update(Grade(2, 1, 1, 5))
		self.assertEqual(ex.exception.get_errors(), "there is no such grade in the repo")

	def test_erase(self):
		repo = InMemoryGradeRepo()
		
		repo.store(Grade(1, 1, 1, 9.5))
		repo.erase(1)
		
		with self.assertRaises(RepoException) as ex:
			repo.erase(1)
		self.assertEqual(ex.exception.get_errors(), "there is no grade with the given grade_id in the repo")

	def test_find(self):
		repo = InMemoryGradeRepo()
		
		grade = Grade(1, 1, 1, 9.75)
		repo.store(grade)
		
		self.assertEqual(repo.find(grade.get_grade_id()), grade)
		
		with self.assertRaises(RepoException) as ex:
			repo.find(2)
		self.assertEqual(ex.exception.get_errors(), "there is no grade with the given grade_id in the repo")

	def test_get_len(self):
		repo = InMemoryGradeRepo()
		
		repo.store(Grade(1, 1, 1, 9))
		self.assertEqual(repo.get_len(), 1)
		
		repo.store(Grade(2, 1, 1, 9.95))
		self.assertEqual(repo.get_len(), 2)

	def test_get_student_grades_by_discipline_id(self):
		repo = InMemoryGradeRepo()
		
		grades_disicpline_1 = [Grade(1, 1, 1, 2), Grade(2, 1, 1, 9), Grade(3, 1, 1, 4)]
		grades_disicpline_2 = [Grade(4, 1, 2, 10), Grade(5, 1, 2, 4)]
		
		repo.store(grades_disicpline_1[0])
		repo.store(grades_disicpline_1[1])
		repo.store(grades_disicpline_1[2])
		repo.store(grades_disicpline_2[0])
		repo.store(grades_disicpline_2[1])
		
		self.assertEqual(len(repo.get_student_grades_by_discipline_id(1)), 3)
		self.assertEqual(len(repo.get_student_grades_by_discipline_id(2)), 2)

''' FILE '''

class TestFileStudentRepo(unittest.TestCase):
	def setUp(self):
		copyfile("test/file/studentrepo_original.txt", "test/file/studentrepo.txt")
		self.student_repo = FileStudentRepo("test/file/studentrepo.txt")

	def test_init(self):
		student_repo = self.student_repo
		self.assertEqual(student_repo.get_len(), 3)
		
		student = student_repo.find(1)
		self.assertEqual(student.get_student_id(), 1)
		self.assertEqual(student.get_name(), "Andrei")
		student = student_repo.find(2)
		self.assertEqual(student.get_student_id(), 2)
		self.assertEqual(student.get_name(), "John Smith")
		student = student_repo.find(99)
		self.assertEqual(student.get_student_id(), 99)
		self.assertEqual(student.get_name(), "Aaron White")

	def test_store(self):
		student_repo = self.student_repo
		student_repo.store(Student(100, "Marie Ableton"))
		self.assertEqual(student_repo.get_len(), 4)
		
		with self.assertRaises(RepoException):
			student_repo.store(Student(100, "Marie Ableton"))

	def test_update(self):
		student_repo = self.student_repo
		student_repo.update(Student(99, "Marie Ableton"))
		self.assertEqual(student_repo.get_len(), 3)
		
		with self.assertRaises(RepoException):
			student_repo.update(Student(100, "Spice Hortson"))

	def test_erase(self):
		student_repo = self.student_repo
		student_repo.erase(1)
		self.assertEqual(student_repo.get_len(), 2)
		
		with self.assertRaises(RepoException):
			student_repo.erase(1)

class TestFileDisciplineRepo(unittest.TestCase):
	def setUp(self):
		copyfile("test/file/disciplinerepo_original.txt", "test/file/disciplinerepo.txt")
		self.discipline_repo = FileDisciplineRepo("test/file/disciplinerepo.txt")

	def test_init(self):
		discipline_repo = self.discipline_repo
		self.assertEqual(discipline_repo.get_len(), 3)
		
		discipline = discipline_repo.find(2)
		self.assertEqual(discipline.get_discipline_id(), 2)
		self.assertEqual(discipline.get_name(), "Mathematics")
		self.assertEqual(discipline.get_professor(), "G.H. Hardy")
		discipline = discipline_repo.find(3)
		self.assertEqual(discipline.get_discipline_id(), 3)
		self.assertEqual(discipline.get_name(), "Eldritch")
		self.assertEqual(discipline.get_professor(), "H.P. Lovecraft")
		discipline = discipline_repo.find(5)
		self.assertEqual(discipline.get_discipline_id(), 5)
		self.assertEqual(discipline.get_name(), "Apologizing")
		self.assertEqual(discipline.get_professor(), "Pewdiepie")

	def test_store(self):
		discipline_repo = self.discipline_repo
		discipline_repo.store(Discipline(100, "Time Travel", "Okabe Rintarou"))
		self.assertEqual(discipline_repo.get_len(), 4)
		
		with self.assertRaises(RepoException):
			discipline_repo.store(Discipline(100, "Time Travel", "Okabe Rintarou"))

	def test_update(self):
		discipline_repo = self.discipline_repo
		discipline_repo.update(Discipline(5, "Time Travel", "Okabe Rintarou"))
		self.assertEqual(discipline_repo.get_len(), 3)
		
		with self.assertRaises(RepoException):
			discipline_repo.update(Discipline(100, "Time Travel", "Okabe Rintarou"))

	def test_erase(self):
		discipline_repo = self.discipline_repo
		discipline_repo.erase(2)
		self.assertEqual(discipline_repo.get_len(), 2)
		
		with self.assertRaises(RepoException):
			discipline_repo.erase(2)

class TestFileGradeRepo(unittest.TestCase):
	def setUp(self):
		copyfile("test/file/graderepo_original.txt", "test/file/graderepo.txt")
		self.grade_repo = FileGradeRepo("test/file/graderepo.txt")

	def test_init(self):
		grade_repo = self.grade_repo
		self.assertEqual(grade_repo.get_len(), 3)
		
		grade = grade_repo.find(1)
		self.assertEqual(grade.get_grade_id(), 1)
		self.assertEqual(grade.get_student_id(), 1)
		self.assertEqual(grade.get_discipline_id(), 1)
		self.assertEqual(grade.get_value(), 9.5)
		grade = grade_repo.find(2)
		self.assertEqual(grade.get_grade_id(), 2)
		self.assertEqual(grade.get_student_id(), 3)
		self.assertEqual(grade.get_discipline_id(), 4)
		self.assertEqual(grade.get_value(), 9.95)
		grade = grade_repo.find(3)
		self.assertEqual(grade.get_grade_id(), 3)
		self.assertEqual(grade.get_student_id(), 5)
		self.assertEqual(grade.get_discipline_id(), 7)
		self.assertEqual(grade.get_value(), 10)

	def test_store(self):
		grade_repo = self.grade_repo
		grade_repo.store(Grade(4, 1, 1, 7.5))
		self.assertEqual(grade_repo.get_len(), 4)
		
		with self.assertRaises(RepoException):
			grade_repo.store(Grade(4, 1, 1, 7.5))

	def test_update(self):
		grade_repo = self.grade_repo
		grade_repo.update(Grade(1, 1, 1, 9.99))
		self.assertEqual(grade_repo.get_len(), 3)
		
		with self.assertRaises(RepoException):
			grade_repo.update(Grade(100, 1, 1, 5))

	def test_erase(self):
		grade_repo = self.grade_repo
		grade_repo.erase(2)
		self.assertEqual(grade_repo.get_len(), 2)
		
		with self.assertRaises(RepoException):
			grade_repo.erase(2)
