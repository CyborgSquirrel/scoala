from . import RepoException

from domain.entity import \
Student, Discipline, Grade

from repo.studentrepo import InMemoryStudentRepo
from repo.disciplinerepo import InMemoryDisciplineRepo
from repo.graderepo import InMemoryGradeRepo

''' STUDENT REPO '''

def test_inmemory_student_repo_store():
	repo = InMemoryStudentRepo()
	
	try:
		repo.store(Student(1, "Jojo"))
	except RepoException:
		assert False
	
	try:
		repo.store(Student(1, "Dio"))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "student is already in the repo"

def test_inmemory_student_repo_update():
	repo = InMemoryStudentRepo()
	
	repo.store(Student(1, "Jojo"))
	
	try:
		repo.update(Student(1, "Dio"))
	except RepoException:
		assert False
	
	try:
		repo.update(Student(2, "Giorno"))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no such student in the repo"

def test_inmemory_student_repo_erase():
	repo = InMemoryStudentRepo()
	
	repo.store(Student(1, "Jojo"))
	
	try:
		repo.erase(1)
	except RepoException:
		assert False
	
	try:
		repo.erase(1)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no student with the given student_id in the repo"

def test_inmemory_student_repo_find():
	repo = InMemoryStudentRepo()
	
	student = Student(1, "Jojo")
	repo.store(student)
	
	try:
		assert repo.find(student.get_student_id()) == student
	except RepoException:
		assert False
	
	try:
		repo.find(2)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no student with the given student_id in the repo"

''' DISCIPLINE REPO '''

def test_inmemory_discipline_repo_store():
	from domain.entity import Discipline
	repo = InMemoryDisciplineRepo()
	
	try:
		repo.store(Discipline(1, "Mathematics", "John Doe"))
	except RepoException:
		assert False
	
	try:
		repo.store(Discipline(1, "Informatics", "Jimbo"))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "discipline is already in the repo"

def test_inmemory_discipline_repo_update():
	from domain.entity import Discipline
	repo = InMemoryDisciplineRepo()
	
	repo.store(Discipline(1, "Mathematics", "Dohn Joe"))
	
	try:
		repo.update(Discipline(1, "PE", "Jamal"))
	except RepoException:
		assert False
	
	try:
		repo.update(Discipline(2, "Nice Discipline", "Nice Professor"))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no such discipline in the repo"

def test_inmemory_discipline_repo_erase():
	from domain.entity import Discipline
	repo = InMemoryDisciplineRepo()
	
	repo.store(Discipline(1, "Mathematics", "Tom Hardy"))
	
	try:
		repo.erase(1)
	except RepoException:
		assert False
	
	try:
		repo.erase(1)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no discipline with the given discipline_id in the repo"

def test_inmemory_discipline_repo_find():
	from domain.entity import Discipline
	repo = InMemoryDisciplineRepo()
	
	discipline = Discipline(1, "Mathematics", "Euler")
	repo.store(discipline)
	
	try:
		assert repo.find(discipline.get_discipline_id()) == discipline
	except RepoException:
		assert False
	
	try:
		repo.find(2)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no discipline with the given discipline_id in the repo"

''' GRADE REPO '''

def test_inmemory_grade_repo_store():
	from domain.entity import Grade
	repo = InMemoryGradeRepo()
	
	try:
		repo.store(Grade(1, 1, 1, 10))
	except RepoException:
		assert False
	
	try:
		repo.store(Grade(1, 2, 1, 9.5))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "grade is already in the repo"

def test_inmemory_grade_repo_update():
	from domain.entity import Grade
	repo = InMemoryGradeRepo()
	
	repo.store(Grade(1, 1, 1, 7))
	
	try:
		repo.update(Grade(1, 1, 1, 10))
	except RepoException:
		assert False
	
	try:
		repo.update(Grade(2, 1, 1, 5))
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no such grade in the repo"

def test_inmemory_grade_repo_erase():
	from domain.entity import Grade
	repo = InMemoryGradeRepo()
	
	repo.store(Grade(1, 1, 1, 9.5))
	
	try:
		repo.erase(1)
	except RepoException:
		assert False
	
	try:
		repo.erase(1)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no grade with the given grade_id in the repo"

def test_inmemory_grade_repo_find():
	from domain.entity import Grade
	repo = InMemoryGradeRepo()
	
	grade = Grade(1, 1, 1, 9.75)
	repo.store(grade)
	
	try:
		assert repo.find(grade.get_grade_id()) == grade
	except RepoException:
		assert False
	
	try:
		repo.find(2)
		assert False
	except RepoException as ex:
		assert ex.get_errors() == "there is no grade with the given grade_id in the repo"

def run_tests():
	test_inmemory_student_repo_store()
	test_inmemory_student_repo_update()
	test_inmemory_student_repo_erase()
	test_inmemory_student_repo_find()
	
	test_inmemory_discipline_repo_store()
	test_inmemory_discipline_repo_update()
	test_inmemory_discipline_repo_erase()
	test_inmemory_discipline_repo_find()
	
	test_inmemory_grade_repo_store()
	test_inmemory_grade_repo_update()
	test_inmemory_grade_repo_erase()
	test_inmemory_grade_repo_find()