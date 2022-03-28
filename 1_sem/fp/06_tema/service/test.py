from service.studentservice import StudentService
from service.disciplineservice import DisciplineService
from service.gradeservice import GradeService

from domain.validator import \
StudentValidator, DisciplineValidator, GradeValidator

from domain.entity import \
Student, Discipline, Grade

from . import ServiceException

''' STUDENT SERVICE '''

def test_get_students():
	validator = StudentValidator()
	repo = {}
	service = StudentService(validator, repo)
	
	service.add_student(1, "Kujo Jotaro")
	service.add_student(2, "Dio Brando")
	
	assert service.get_students() == [ Student(1, "Kujo Jotaro"), Student(2, "Dio Brando") ]

def test_add_student():
	validator = StudentValidator()
	repo = {}
	service = StudentService(validator, repo)
	
	try:
		service.add_student(1, "Jojo")
	except ServiceException:
		assert False
	
	try:
		service.add_student(1, "Jojo")
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given student_id is already in use"

''' DISCIPLINE SERVICE '''

def test_get_disciplines():
	validator = DisciplineValidator()
	repo = {}
	service = DisciplineService(validator, repo)
	
	service.add_discipline(1, "Mathematics", "John Doe")
	service.add_discipline(2, "PE", "Jeff")
	
	assert service.get_disciplines() == [ Discipline(1, "Mathematics", "John Doe"), Discipline(2, "PE", "Jeff") ]

def test_add_discipline():
	validator = DisciplineValidator()
	repo = {}
	service = DisciplineService(validator, repo)
	
	try:
		service.add_discipline(1, "Mathematics", "John Doe")
	except ServiceException:
		assert False
	
	try:
		service.add_discipline(1, "Mathematics", "John Doe")
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given discipline_id is already in use"

''' GRADE SERVICE '''

def __init_grade_service_and_its_dependencies():
	student_validator = StudentValidator()
	student_repo = {}
	student_service = StudentService(student_validator, student_repo)

	discipline_validator = DisciplineValidator()
	discipline_repo = {}
	discipline_service = DisciplineService(discipline_validator, discipline_repo)

	grade_validator = GradeValidator()
	grade_repo = {}
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
	
	try:
		grade_service.add_grade(1, 1, 1, 10)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given student_id is not in the repository"
	
	student_service.add_student(1, "Andrei")
	
	try:
		grade_service.add_grade(1, 1, 1, 10)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given discipline_id is not in the repository"
	
	discipline_service.add_discipline(1, "Mathematics", "John Doe")
	
	try:
		grade_service.add_grade(1, 1, 1, 10)
	except ServiceException:
		assert False
	
	try:
		grade_service.add_grade(1, 1, 1, 10)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given grade_id is already in use"

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
	
	try:
		grade_service.erase_grade(3)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given grade_id is not in the repository"

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
		grade_service.erase_student_and_all_their_grades(1)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given student_id is not in the repository"
	
	try:
		grade_service.erase_student_and_all_their_grades(2)
	except ServiceException:
		assert False
	
	try:
		grade_service.erase_student_and_all_their_grades(3)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given student_id is not in the repository"

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
		grade_service.erase_discipline_and_all_its_grades(1)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given discipline_id is not in the repository"
	
	try:
		grade_service.erase_discipline_and_all_its_grades(2)
	except ServiceException:
		assert False
	
	try:
		grade_service.erase_discipline_and_all_its_grades(3)
		assert False
	except ServiceException as ex:
		assert ex.get_errors() == "the given discipline_id is not in the repository"

def run_tests():
	test_get_students()
	test_add_student()
	
	test_get_disciplines()
	test_add_discipline()
	
	test_get_grades()
	test_add_grade()
	test_erase_grade()
	test_erase_student_and_all_their_grades()
	test_erase_discipline_and_all_its_grades()

run_tests()