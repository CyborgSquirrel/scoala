# JAVA_ARGS = -Xmx6G
JAVA_ARGS =
CPP_ARGS = -O2
# CPP_ARGS = -g

.PHONY: all

all: \
	check/cpp/10-10.dat \
	check/cpp/1000-1000.dat \
	check/cpp/10000-10000.dat \
	check/java/10-10.dat \
	check/java/1000-1000.dat \
	check/java/10000-10000.dat

# input file generation

data/conv.dat: gen_random.py
	python gen_random.py --force 5 5 data/conv.dat

data/mat.dat: gen_random.py
	python gen_random.py --force 10000 10000 data/mat.dat

# cpp compile

target/conv: conv.cpp
	mkdir -p ./target
	g++ -std=c++20 $(CPP_ARGS) -Wall ./conv.cpp -o ./target/conv

# cpp checks

CPP_CHECK_DEPS = target/conv data/conv.dat data/mat.dat

check/cpp/10-10.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv 0 10 10 ./data/mat.dat ./data/conv.dat ./check/cpp/10-10.dat

check/cpp/1000-1000.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv 0 1000 1000 ./data/mat.dat ./data/conv.dat ./check/cpp/1000-1000.dat

check/cpp/10000-10000.dat: $(CPP_CHECK_DEPS)
	mkdir -p ./check/cpp
	./target/conv 0 10000 10000 ./data/mat.dat ./data/conv.dat ./check/cpp/10000-10000.dat

# java checks

JAVA_CHECK_DEPS = conv.java data/conv.dat data/mat.dat

check/java/10-10.dat: $(JAVA_CHECK_DEPS)
	mkdir -p ./check/java
	java $(JAVA_ARGS) conv.java 0 10 10 ./data/mat.dat ./data/conv.dat ./check/java/10-10.dat

check/java/1000-1000.dat: $(JAVA_CHECK_DEPS)
	mkdir -p ./check/java
	java $(JAVA_ARGS) conv.java 0 1000 1000 ./data/mat.dat ./data/conv.dat ./check/java/1000-1000.dat

check/java/10000-10000.dat: $(JAVA_CHECK_DEPS)
	mkdir -p ./check/java
	java $(JAVA_ARGS) conv.java 0 10000 10000 ./data/mat.dat ./data/conv.dat ./check/java/10000-10000.dat

