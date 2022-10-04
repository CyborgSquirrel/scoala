CXX=clang++
CXXFLAGS=-Wall -g
CHECKS=cppcoreguidelines-*

.PHONY: all test clean

# all: test uitest
# all: test
all: app

uitest: app
	@echo
	@echo ===UITEST===
	cat ./carti.txt | valgrind ./app

test: *.cpp *.hpp
	$(CXX) $(CXXFLAGS) --coverage *.cpp -D ONLY_RUN_TESTS -o app-test
	@echo
	@echo ===VALGRIND===
	valgrind ./app-test
	@echo
	@echo ===COVERAGE===
	# gcov -r $$(fd -I --extension gcda . | grep -v './app-test-ui.gcda' | tr '\n' ' ')
	llvm-cov gcov -r *.cpp

clean:
	rm -f *.gcda *.gcno *.gcov

app: *.cpp *.hpp
	$(CXX) $(CXXFLAGS) *.cpp -o app
	clang-tidy -checks='$(CHECKS)' *.cpp -- $(CXXFLAGS) -o app
