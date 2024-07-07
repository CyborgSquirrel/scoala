.PHONY: all clean cerinta-2 cerinta-3 cerinta-3-1 cerinta-3-2

all: cerinta-2 cerinta-3

cerinta-2: build/2-1 build/2-2 build/2-3
	@echo
	@echo ==========
	@cat 2-1.txt
	@bat 2-1.rs
	./build/2-1

	@echo
	@echo ==========
	@cat 2-2.txt
	@bat 2-2.rs
	./build/2-2

	@echo
	@echo ==========
	@cat 2-3.txt
	@bat 2-3.rs
	./build/2-3

cerinta-3: cerinta-3-1 cerinta-3-2

cerinta-3-1:
	@echo
	@echo ==========
	@cat 3-1.txt
	@bat 3-1.rs
	-rustc 3-1.rs

cerinta-3-2: build/3-2
	@echo
	@echo ==========
	@cat 3-2.txt
	@bat 3-2.rs
	./build/3-2

clean:
	rm -rf build

build:
	mkdir -p build

build/2-1: build
	rustc 2-1.rs -o build/2-1
build/2-2: build
	rustc 2-2.rs -o build/2-2
build/2-3: build
	rustc 2-3.rs -o build/2-3
build/3-2: build
	rustc 3-2.rs -o build/3-2
