.PHONY: run

run: target
	mpirun ./target

target: main.c
	bear -- mpicc main.c -o target
