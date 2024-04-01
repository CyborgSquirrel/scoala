.PHONY: test run

RUN_PREFIX = 
# RUN_PREFIX = valgrind
# RUN_PREFIX = valgrind --leak-check=full
# RUN_PREFIX = valgrind --leak-check=full --show-leak-kinds=all

CFLAGS = -g
# CFLAGS =

run: target/analyzer
	$(RUN_PREFIX) ./target/analyzer a.rs

	# @printf '\n\n=== %s ===\n' 'test/2-1.rs'
	# $(RUN_PREFIX) ./target/analyzer test/2-1.rs
	# @printf '\n\n=== %s ===\n' 'test/2-2.rs'
	# $(RUN_PREFIX) ./target/analyzer test/2-2.rs
	# @printf '\n\n=== %s ===\n' 'test/2-3.rs'
	# $(RUN_PREFIX) ./target/analyzer test/2-3.rs
	# @printf '\n\n=== %s ===\n' 'test/3-1.rs'
	# $(RUN_PREFIX) ./target/analyzer test/3-1.rs
	# @printf '\n\n=== %s ===\n' 'test/3-2.rs'
	# $(RUN_PREFIX) ./target/analyzer test/3-2.rs

target/analyzer: \
	target/scanner.h \
	target/scanner.c \
	target/analyzer.h \
	target/analyzer.c \
	main.c \
	obj.c \
	Makefile \

	mkdir -p ./target
	gcc $(CFLAGS) -Wall \
		./main.c ./target/scanner.c ./target/analyzer.c \
		-o ./target/analyzer

# scanner

target/scanner.stamp: scanner.l
	mkdir -p ./target

	@rm -f target/scanner.tmp
	@touch target/scanner.tmp

	flex \
		--outfile=./target/scanner.c \
		--header-file=./target/scanner.h \
		scanner.l

	@mv -f target/scanner.tmp target/scanner.stamp

target/scanner.h target/scanner.c: target/scanner.stamp

# analyzer

target/analyzer.stamp: analyzer.y
	mkdir -p ./target

	@rm -f target/analyzer.tmp
	@touch target/analyzer.tmp

	bison \
		--output=./target/analyzer.c \
		--header=./target/analyzer.h \
		analyzer.y

	@mv -f target/analyzer.tmp target/analyzer.stamp

target/analyzer.h target/analyzer.c: target/analyzer.stamp
