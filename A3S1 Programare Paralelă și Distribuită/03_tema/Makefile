# CFLAGS = -g
CFLAGS = -O2
# RUN_PREFIX = valgrind

.PHONY: test run prepare

test: test.py prepare
	python test.py

run: prepare
	$(RUN_PREFIX) mpirun --oversubscribe -n 4 \
		./target/mpi-v2 \
			10 10 \
			./data/mat.dat ./data/conv.dat ./target/result.dat ./target/time.txt

prepare: \
	target/mpi-v1 \
	target/mpi-v2 \
	check/mpi/1000-1000.dat \
	check/mpi/10000-10000.dat \
	data/mat.dat \
	data/conv.dat \

# check

check/mpi/1000-1000.dat: ../02_tema/check/cpp/1000-1000.dat
	mkdir -p ./check/mpi
	cp ../02_tema/check/cpp/1000-1000.dat ./check/mpi

check/mpi/10000-10000.dat: ../02_tema/check/cpp/10000-10000.dat
	mkdir -p ./check/mpi
	cp ../02_tema/check/cpp/10000-10000.dat ./check/mpi

# data

data/mat.dat: ../02_tema/data/mat.dat
	mkdir -p ./data
	cp ../02_tema/data/mat.dat ./data

data/conv.dat: ../02_tema/data/conv.dat
	mkdir -p ./data
	cp ../02_tema/data/conv.dat ./data

# compile

target/mpi-v1: mpi-v1.c Makefile
	mkdir -p ./target
	bear -- mpicc $(CFLAGS) mpi-v1.c -o ./target/mpi-v1

target/mpi-v2: mpi-v2.c Makefile
	mkdir -p ./target
	bear -- mpicc $(CFLAGS) mpi-v2.c -o ./target/mpi-v2
