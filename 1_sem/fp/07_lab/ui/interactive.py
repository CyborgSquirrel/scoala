from domain.validator import ValidatorException
from service import ServiceException

class UIInteractive:
	def __init__(self, student_service, discipline_service, grade_service):
		self.__student_service = student_service
		self.__discipline_service = discipline_service
		self.__grade_service = grade_service
		self.__commands = {
			"help": self.__help,
			
			"add student": self.__add_student,
			"erase student": self.__erase_student,
			"print students": self.__print_students,
			
			"add discipline": self.__add_discipline,
			"erase discipline": self.__erase_discipline,
			"print disciplines": self.__print_disciplines,
			
			"assign grade": self.__add_grade,
			"erase grade": self.__erase_grade,
			"print grades": self.__print_grades,
			
			"find lowest grade": self.__find_lowest_grade,
		}
	
	def __error(self, message):
		message_parts = message.split("\n")
		for message_part in message_parts:
			if message_part != "":
				print(f"Error: {message_part}")
	
	def __note(self, message):
		print(f"Note: {message}")
	
	def __help(self):
		print(f"Help: input one of the following commands: {list(self.__commands.keys())}")
		print("Input 'help' to show this message")
	
	def __add_student(self):
		student_id = input("student_id = ")
		name = input("name = ")
		
		try:
			student_id = int(student_id)
		except:
			self.__error("Invalid student_id\n")
			return
		
		try:
			self.__student_service.add_student(student_id, name)
		except (ValidatorException, ServiceException) as ex:
			self.__error(ex.get_errors())
		
	def __erase_student(self):
		self.__note("this will also erase all the student's grades")
		student_id = input("student_id = ")
		
		try:
			student_id = int(student_id)
		except:
			self.__error("invalid student_id\n")
			return
		
		try:
			self.__grade_service.erase_student_and_all_their_grades(student_id)
		except ServiceException as ex:
			self.__error(ex.get_errors())
	
	def __print_students(self):
		for student in self.__student_service.get_students():
			print(str(student))
	
	def __add_discipline(self):
		discipline_id = input("discipline_id = ")
		name = input("name = ")
		professor = input("professor = ")
		
		try:
			discipline_id = int(discipline_id)
		except:
			self.__error("invalid discipline_id\n")
			return
		
		try:
			self.__discipline_service.add_discipline(discipline_id, name, professor)
		except (ValidatorException, ServiceException) as ex:
			self.__error(ex.get_errors())
		
	def __erase_discipline(self):
		self.__note("this will also erase all the discipline's grades")
		discipline_id = input("discipline_id = ")
		
		try:
			discipline_id = int(discipline_id)
		except:
			self.__error("invalid discipline_id\n")
			return
		
		try:
			self.__grade_service.erase_discipline_and_all_its_grades(discipline_id)
		except ServiceException as ex:
			self.__error(ex.get_errors())
	
	def __print_disciplines(self):
		for discipline in self.__discipline_service.get_disciplines():
			print(str(discipline))
	
	def __add_grade(self):
		grade_id = input("grade_id = ")
		student_id = input("student_id = ")
		discipline_id = input("discipline_id = ")
		value = input("value = ")
		
		try:
			grade_id = int(grade_id)
		except:
			self.__error("invalid grade_id\n")
			return
		
		try:
			student_id = int(student_id)
		except:
			self.__error("invalid student_id\n")
			return
		
		try:
			discipline_id = int(discipline_id)
		except:
			self.__error("invalid discipline_id\n")
			return
		
		try:
			value = float(value)
		except:
			self.__error("invalid value\n")
			return
		
		try:
			self.__grade_service.add_grade(grade_id, student_id, discipline_id, value)
		except (ValidatorException, ServiceException) as ex:
			self.__error(ex.get_errors())
	
	def __erase_grade(self):
		grade_id = input("grade_id = ")
		
		try:
			grade_id = int(grade_id)
		except:
			self.__error("invalid grade_id\n")
			return
		
		try:
			self.__grade_service.erase_grade(grade_id)
		except ServiceException as ex:
			self.__error(ex.get_errors())
	
	def __print_grades(self):
		for grade in self.__grade_service.get_grades():
			print(str(grade))
	
	def __find_lowest_grade(self):
		try:
			lowest_grade = self.__grade_service.find_lowest_grade()
			print(f"lowest_grade = {lowest_grade}")
		except ServiceException as ex:
			self.__error(ex.get_errors())
	
	def run(self):
		self.__help()
		print()
		while True:
			command = input("# ")
			if command in self.__commands:
				self.__commands[command]()
			else:
				self.__error("invalid command")
			print()
