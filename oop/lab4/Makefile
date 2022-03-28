CC=gcc
CFLAGS=-Wall

.PHONY: all clean test

all: app

test: *.c *.h
	$(CC) $(CFLAGS) -g -fprofile-arcs -ftest-coverage -D ONLY_RUN_TESTS *.c -o app-test
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
