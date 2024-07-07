# GXX_ARGS_EXTRA = -g
GXX_ARGS_EXTRA = -O2
GXX_ARGS = -std=c++20 -Wall $(GXX_ARGS_EXTRA)

# NVCC_ARGS_EXTRA = -g
NVCC_ARGS = --expt-relaxed-constexpr $(NVCC_ARGS_EXTRA)

.PHONY: prepare test

test: prepare test.py
	python test.py

prepare: \
	check/cpp/10-10.dat \
	check/cpp/1000-1000.dat \
	check/cpp/10000-10000.dat \
	target/conv-cu \

# input file generation

data/conv.dat: gen_random.py
	mkdir -p ./data
	python gen_random.py --force 5 5 data/conv.dat

data/mat.dat: gen_random.py
	mkdir -p ./data
	python gen_random.py --force 10000 10000 data/mat.dat

# gxx compile

target/conv-cpp: conv.cpp
	mkdir -p ./target
	bear -- g++ $(GXX_ARGS) ./conv.cpp -o ./target/conv-cpp

# cpp checks

CPP_CHECK_DEPS = target/conv-cpp data/conv.dat data/mat.dat

check/cpp/10-10.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv-cpp 0 10 10 ./data/mat.dat ./data/conv.dat ./check/cpp/10-10.dat

check/cpp/1000-1000.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv-cpp 0 1000 1000 ./data/mat.dat ./data/conv.dat ./check/cpp/1000-1000.dat

check/cpp/10000-10000.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv-cpp 0 10000 10000 ./data/mat.dat ./data/conv.dat ./check/cpp/10000-10000.dat

