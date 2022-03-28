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

''' STUDENT SERVICE '''

def test_get_students():
	validator = StudentValidator()
	repo = InMemoryStudentRepo()
	service = StudentService(validator, repo)
	
	service.add_student(1, "Kujo Jotaro")
	service.add_student(2, "Dio Brando")
	
	assert service.get_students() == [ Student(1, "Kujo Jotaro"), Student(2, "Dio Brando") ]

def test_add_student():
	validator = StudentValidator()
	repo = InMemoryStudentRepo()
	service = StudentService(validator, repo)
	
	try:
		service.add_student(1, "Jojo")
	except ServiceException:
		assert False

def test_update_student():
	validator = StudentValidator()
	repo = InMemoryStudentRepo()
	service = StudentService(validator, repo)
	
	service.add_student(1, "Jojo")
	try:
		service.update_student(1, "Jonno")
	except ServiceException:
		assert False

def test_find_student():
	validator = StudentValidator()
	repo = InMemoryStudentRepo()
	service = StudentService(validator, repo)
	
	service.add_student(1, "Jojo")
	try:
		assert service.find_student(1) == Student(1, "Jojo")
	except ServiceException:
		assert False

''' DISCIPLINE SERVICE '''

def test_get_disciplines():
	validator = DisciplineValidator()
	repo = InMemoryDisciplineRepo()
	service = DisciplineService(validator, repo)
	
	service.add_discipline(1, "Mathematics", "John Doe")
	service.add_discipline(2, "PE", "Jeff")
	
	assert service.get_disciplines() == [ Discipline(1, "Mathematics", "John Doe"), Discipline(2, "PE", "Jeff") ]

def test_add_discipline():
	validator = DisciplineValidator()
	repo = InMemoryDisciplineRepo()
	service = DisciplineService(validator, repo)
	
	try:
		service.add_discipline(1, "Mathematics", "John Doe")
	except ServiceException:
		assert False

def test_update_discipline():
	validator = DisciplineValidator()
	repo = InMemoryDisciplineRepo()
	service = DisciplineService(validator, repo)
	
	service.add_discipline(1, "Mathematics", "Pythagoras")
	try:
		service.update_discipline(1, "Geometry", "Pythagoras")
	except ServiceException:
		assert False

def test_find_discipline():
	validator = DisciplineValidator()
	repo = InMemoryDisciplineRepo()
	service = DisciplineService(validator, repo)
	
	service.add_discipline(1, "Literature", "Mihai Eminescu")
	try:
		assert service.find_discipline(1) == Discipline(1, "Literature", "Mihai Eminescu")
	except ServiceException:
		assert False

''' GRADE SERVICE '''

def __init_grade_service_and_its_dependencies():
	student_validator = StudentValidator()
	student_repo = InMemoryStudentRepo()
	student_service = StudentService(student_validator, student_repo)

	discipline_validator = DisciplineValidator()
	discipline_repo = InMemoryDisciplineRepo()
	discipline_service = DisciplineService(discipline_validator, discipline_repo)

	grade_validator = GradeValidator()
	grade_repo = InMemoryGradeRepo()
	grade_service = GradeService(grade_validator, grade_repo, student_repo, discipline_repo)
	
	return student_service, discipline_service, grade_service

def test_get_grades():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	student_service.add_student(1, "Joseph")
	student_service.add_student(2, "Bobo")
	discipline_service.add_discipline(1, "Arithmetic", "Jim")
	grade_service.add_grade(1, 1, 1, 9.5)
	grade_service.add_grade(2, 2, 1, 4.2)
	grade_service.add_grade(3, 2, 1, 7.9)
	
	assert grade_service.get_grades() == [
		Grade(1, 1, 1, 9.5),
		Grade(2, 2, 1, 4.2),
		Grade(3, 2, 1, 7.9),
	]

def test_add_grade():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	student_service.add_student(1, "Andrei")
	discipline_service.add_discipline(1, "Mathematics", "John Doe")
	
	try:
		grade_service.add_grade(1, 1, 1, 10)
	except ServiceException:
		assert False

def test_find_grade():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	student_service.add_student(1, "Jojo")
	discipline_service.add_discipline(1, "Philosophy", "Tom Hanks")
	grade_service.add_grade(1, 1, 1, 9.5)
	
	try:
		assert grade_service.find_grade(1) == Grade(1, 1, 1, 9.5)
	except ServiceException:
		assert False

def test_get_grades_with_discipline_sorted_by_criterion():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
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
	
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(1, "name")) == 3
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(2, "name")) == 2
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(3, "name")) == 2
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(1, "grade")) == 3
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(2, "grade")) == 2
	assert len(grade_service.get_grades_with_discipline_sorted_by_criterion(3, "grade")) == 2
	
	try:
		grade_service.get_grades_with_discipline_sorted_by_criterion(2, "awesomeness")
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "invalid criterion"

def test_get_top_20_percent_of_students():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
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
	assert top.get_student_name() == "Felix Sima"
	assert top.get_average() == (10+9.5+9.75)/3

def test_erase_grade():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	student_service.add_student(1, "Jonno")
	student_service.add_student(2, "Niko")
	discipline_service.add_discipline(1, "Mathematics", "John Doe")
	grade_service.add_grade(1, 1, 1, 9.5)
	grade_service.add_grade(2, 2, 1, 4.2)
	
	try:
		grade_service.erase_grade(1)
	except ServiceException:
		assert False
	
	try:
		grade_service.erase_grade(2)
	except ServiceException:
		assert False

def test_erase_student_and_all_their_grades():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	student_service.add_student(1, "Jonno")
	student_service.add_student(2, "Niko")
	discipline_service.add_discipline(1, "Mathematics", "John Doe")
	grade_service.add_grade(1, 1, 1, 9.5)
	grade_service.add_grade(2, 1, 1, 9.9)
	grade_service.add_grade(3, 2, 1, 4.2)
	grade_service.add_grade(4, 2, 1, 4.1)
	grade_service.add_grade(5, 2, 1, 7.7)
	
	try:
		grade_service.erase_student_and_all_their_grades(1)
	except ServiceException:
		assert False
	
	try:
		grade_service.erase_student_and_all_their_grades(2)
	except ServiceException:
		assert False

def test_erase_discipline_and_all_its_grades():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	student_service.add_student(1, "Niko")
	discipline_service.add_discipline(1, "Mathematics", "John Doe")
	discipline_service.add_discipline(2, "Informatics", "Joe Generic")
	grade_service.add_grade(1, 1, 1, 3.2)
	grade_service.add_grade(2, 1, 1, 1.2)
	grade_service.add_grade(3, 1, 1, 7.5)
	grade_service.add_grade(4, 1, 2, 7.6)
	grade_service.add_grade(5, 1, 2, 8.1)
	
	try:
		grade_service.erase_discipline_and_all_its_grades(1)
	except ServiceException:
		assert False
	
	try:
		grade_service.erase_discipline_and_all_its_grades(2)
	except ServiceException:
		assert False
	
def test_find_lowest_grade():
	student_service, discipline_service, grade_service = \
		__init_grade_service_and_its_dependencies()
	
	try:
		grade_service.find_lowest_grade()
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "there are no grades"
	
	student_service.add_student(1, "Keith Pete")
	student_service.add_student(2, "Simple Student")
	discipline_service.add_discipline(1, "Mathematics", "Lebowski")
	grade_service.add_grade(1, 1, 1, 3.3)
	grade_service.add_grade(2, 2, 1, 9.5)
	grade_service.add_grade(3, 2, 1, 7.25)
	
	try:
		assert grade_service.find_lowest_grade() == Grade(1, 1, 1, 3.3)
	except ServiceException:
		assert False

def run_service_tests():
	test_get_students()
	test_add_student()
	test_update_student()
	test_find_student()
	
	test_get_disciplines()
	test_add_discipline()
	test_update_discipline()
	test_find_discipline()
	
	test_get_grades()
	test_add_grade()
	test_find_grade()
	test_get_grades_with_discipline_sorted_by_criterion()
	test_get_top_20_percent_of_students()
	test_erase_grade()
	test_erase_student_and_all_their_grades()
	test_erase_discipline_and_all_its_grades()
	test_find_lowest_grade()
