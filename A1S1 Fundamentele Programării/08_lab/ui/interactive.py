from domain.validator import ValidatorException
from service import ServiceException
from repo import RepoException

import textwrap

class UIException(Exception):
	def __init__(self, errors=""):
		self.__errors = errors
	
	def get_errors(self):
		return self.__errors

class UIInteractive:
	def __init__(self, student_service, discipline_service, grade_service):
		self.__student_service = student_service
		self.__discipline_service = discipline_service
		self.__grade_service = grade_service
		self.__running = True
		self.__commands = {
			"help": self.__help,
			"exit": self.__exit,
			
			"add student": self.__add_student,
			"update student": self.__update_student,
			"erase student": self.__erase_student,
			"find student": self.__find_student,
			"print students": self.__print_students,
			
			"add random students": self.__add_random_student,
			
			"add discipline": self.__add_discipline,
			"update discipline": self.__update_discipline,
			"erase discipline": self.__erase_discipline,
			"find discipline": self.__find_discipline,
			"print disciplines": self.__print_disciplines,
			
			"assign grade": self.__add_grade,
			"erase grade": self.__erase_grade,
			"print grades": self.__print_grades,
			
			"find lowest grade": self.__find_lowest_grade,
			# "print sorted grades": self.__print_sorted_grades,
			# "print top 20 percent": self.__print_top_20_percent,
		}
	
	def __run_command(self, command):
		command = command.strip()
		
		if command in self.__commands:
			try:
				self.__commands[command]()
			except (ValidatorException, ServiceException, RepoException, UIException) as ex:
				self.__error(ex.get_errors())
		elif command == "": pass
		else: self.__error("invalid command")
		print()
	
	def __error(self, message):
		message_parts = message.split("\n")
		for message_part in message_parts:
			if message_part != "":
				print(f"Error: {message_part}")
	
	def __hint(self, message):
		print(f"Hint: {message}")
	
	def __note(self, message):
		print(f"Note: {message}")
	
	def __input(self, name, converter):
		value = input(f"{name} = ")
		try:
			return converter(value)
		except:
			raise UIException(f"invalid {name}")
	
	def __help(self):
		help_string = f"write one of the following commands: {list(self.__commands.keys())}"
		help_string = "\n".join(
			textwrap.wrap(
				help_string, width=70,
				initial_indent="Help: ", subsequent_indent="      "
			)
		)
		help_string += "\n"
		help_string += "\n"
		help_string += "      write 'help' to show this message"
		print(help_string)
	
	def __exit(self):
		self.__running = False
	
	def __add_student(self):
		student_id = self.__input("student_id", int)
		name = self.__input("name", str)
		
		self.__student_service.add_student(student_id, name)
	
	def __update_student(self):
		student_id = self.__input("student_id", int)
		name = self.__input("name", str)
		
		self.__student_service.update_student(student_id, name)
		
	def __erase_student(self):
		self.__note("this will also erase all the student's grades")
		student_id = self.__input("student_id", int)
		
		self.__grade_service.erase_student_and_all_their_grades(student_id)
	
	def __find_student(self):
		student_id = self.__input("student_id", int)
		
		student = self.__student_service.find_student(student_id)
		print(str(student))
	
	def __print_students(self):
		for student in self.__student_service.get_students():
			print(str(student))
	
	def __add_random_student(self):
		number_of_students = self.__input("number_of_students", int)
		
		for i in range(number_of_students):
			self.__student_service.add_random_student()
	
	def __add_discipline(self):
		discipline_id = self.__input("discipline_id", int)
		name = self.__input("name", str)
		professor = self.__input("professor", str)
		
		self.__discipline_service.add_discipline(discipline_id, name, professor)
	
	def __update_discipline(self):
		discipline_id = self.__input("discipline_id", int)
		name = self.__input("name", str)
		professor = self.__input("professor", str)
		
		self.__discipline_service.update_discipline(discipline_id, name, professor)
		
	def __erase_discipline(self):
		self.__note("this will also erase all the discipline's grades")
		discipline_id = self.__input("discipline_id", int)
		
		self.__grade_service.erase_discipline_and_all_its_grades(discipline_id)
	
	def __find_discipline(self):
		discipline_id = self.__input("discipline_id", int)
		
		discipline = self.__discipline_service.find_discipline(discipline_id)
		print(str(discipline))
	
	def __print_disciplines(self):
		for discipline in self.__discipline_service.get_disciplines():
			print(str(discipline))
	
	def __add_grade(self):
		grade_id = self.__input("grade_id", int)
		student_id = self.__input("student_id", int)
		discipline_id = self.__input("discipline_id", int)
		value = self.__input("value", float)
		
		self.__grade_service.add_grade(grade_id, student_id, discipline_id, value)
	
	def __erase_grade(self):
		grade_id = self.__input("grade_id", int)
		
		self.__grade_service.erase_grade(grade_id)
	
	def __print_grades(self):
		for grade in self.__grade_service.get_grades():
			print(str(grade))
	
	def __find_lowest_grade(self):
		lowest_grade = self.__grade_service.find_lowest_grade()
		print(f"lowest_grade = {lowest_grade}")
	
	def __print_sorted_grades(self):
		discipline_id = self.__input("discipline_id", int)
		
		self.__hint("criterion can be either 'name' or 'grade'")
		criterion = self.__input("criterion", str)
		
		grades = self.__grade_service.get_grades_with_discipline_sorted_by_criterion(discipline_id, criterion)
		
		print(f"{'Name':15} {'Value':4}")
		for grade_id in grades:
			grade = self.__grade_service.find_grade(grade_id)
			student = self.__student_service.find_student(grade.get_student_id())
			name = student.get_name()
			value = grade.get_value()
			
			print(f"{name:15} {value:4}")
	
	def __print_top_20_percent(self):
		students_and_averages = self.__grade_service.get_top_20_percent_of_students()
		
		print(f"{'Name':15} {'Average':4}")
		for student_id,average in students_and_averages:
			student = self.__student_service.find_student(student_id)
			name = student.get_name()
			
			print(f"{name:15} {average:4}")
	
	def run(self):
		self.__run_command("help")
		while self.__running:
			command = input("# ")
			self.__run_command(command)
