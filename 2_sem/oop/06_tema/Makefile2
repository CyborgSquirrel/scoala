CXX=g++
CXXFLAGS=-Wall -g

.PHONY: all test clean

# all: test uitest
all: test

uitest: app
	@echo
	@echo ===UITEST===
	cat ./carti.txt | valgrind ./app

test: *.cpp *.hpp
	$(CXX) $(CXXFLAGS) *.cpp --coverage -D ONLY_RUN_TESTS -o app-test
	@echo
	@echo ===VALGRIND===
	valgrind ./app-test
	@echo
	@echo ===COVERAGE===
	gcov -r $$(fd -I --extension gcda . | grep -v './app-test-ui.gcda' | tr '\n' ' ')

clean:
	rm -f *.gcda *.gcno *.gcov

app: *.cpp *.hpp
	$(CXX) $(CXXFLAGS) *.cpp -o app
