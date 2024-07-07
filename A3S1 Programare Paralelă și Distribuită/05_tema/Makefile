# CFLAGS = -g
CFLAGS = -O2 -std=c++20
# CFLAGS = -std=c++20
RUN_PREFIX = valgrind
# RUN_PREFIX = valgrind --leak-check=full

.PHONY: test run prepare

test: test.py prepare
	python test.py

run: prepare
	$(RUN_PREFIX) ./target/sequential ./data ./target/result.txt /dev/null
	# $(RUN_PREFIX) ./target/threaded ./data ./target/result.txt /dev/null 4 2

prepare: \
	target/sequential \
	target/threaded \
	check/result.txt \
	data

# check

check/result.txt: data target/sequential
	mkdir -p ./check
	target/sequential ./data ./check/result.txt /dev/null

# data

data: gen.py
	python gen.py data

# compile

target/threaded: threaded.cpp Makefile
	mkdir -p ./target
	bear -- g++ $(CFLAGS) threaded.cpp -o ./target/threaded

target/sequential: sequential.cpp Makefile
	mkdir -p ./target
	bear -- g++ $(CFLAGS) sequential.cpp -o ./target/sequential
