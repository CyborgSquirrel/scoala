CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean test

all: app

uitest: materiale.txt all
	cat ./materiale.txt | valgrind --leak-check=full ./app

test: *.c *.h
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -D ONLY_RUN_TESTS *.c -o app-test
	@echo
	@echo ===VALGRIND===
	valgrind --track-origins=yes --leak-check=full ./app-test
	@echo
	@echo ===COVERAGE===
	gcov *.gcda

clean:
	rm -f *.gcno *.gcda *.gcov

app: *.c *.h
	$(CC) $(CFLAGS) *.c -o app
