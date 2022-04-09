CXX=clang++
CXXFLAGS=-Wall -g
CHECKS=cppcoreguidelines-*
TESTFLAGS=-Wall -g --coverage -D ONLY_RUN_TESTS -o app-test
APPFLAGS=-Wall -g -o app

.PHONY: all test clean

# all: test uitest
# all: test
all: app

uitest: app
	@echo
	@echo ===UITEST===
	cat ./carti.txt | valgrind ./app

test: clean *.cpp *.hpp
	$(CXX) $(TESTFLAGS) *.cpp
	@echo
	@echo ===VALGRIND===
	valgrind --leak-check=full ./app-test
	@echo
	@echo ===COVERAGE===
	llvm-cov gcov -r *.cpp
	@echo
	@echo ===LINTER===
	clang-tidy -checks='$(CHECKS)' *.cpp *.hpp -- $(TESTFLAGS)

clean:
	rm -f *.gcda *.gcno *.gcov

app: *.cpp *.hpp
	$(CXX) $(APPFLAGS) *.cpp
	@echo
	@echo ===LINTER===
	clang-tidy -checks='$(CHECKS)' *.cpp *.hpp -- $(APPFLAGS)
