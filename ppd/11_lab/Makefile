.PHONY: run

run: target/main
	./target/main

target/main: main_in_classs_openmp.cpp
	mkdir -p target
	bear -- g++ -fopenmp main_in_classs_openmp.cpp -o ./target/main
