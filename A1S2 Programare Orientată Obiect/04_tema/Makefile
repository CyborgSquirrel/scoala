CC=gcc
CFLAGS=-Wall -fprofile-arcs -ftest-coverage

.PHONY: all clean test

all: app

test: *.c *.h
	$(CC) $(CFLAGS) -D ONLY_RUN_TESTS *.c -o app-test
	@echo
	@echo ===VALGRIND===
	valgrind ./app-test
	@echo
	@echo ===COVERAGE===
	gcov *.gcda

clean:
	rm -f *.gcno *.gcda *.gcov

app: *.c *.h
	$(CC) $(CFLAGS) *.c -o app
