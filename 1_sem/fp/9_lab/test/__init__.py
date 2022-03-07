from .domain_test import run_domain_tests
from .repo_test import run_repo_tests
from .service_test import run_service_tests

class TestRunner:
	def __init__(self, quiet):
		self.__quiet = quiet
	
	def __info(self, message):
		if not self.__quiet:
			print(message)
	
	def __run_tests(self, tests, func):
		self.__info(f"Running {tests}...")
		func()
		self.__info(f"Finished running {tests}")
		
	def run(self):
		self.__run_tests("domain tests", run_domain_tests)
		self.__run_tests("repo tests", run_repo_tests)
		self.__run_tests("service tests", run_service_tests)

test_runner = TestRunner(True)
test_runner.run()