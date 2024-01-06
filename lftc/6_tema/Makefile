.PHONY: test run

RUN_PREFIX = 
# RUN_PREFIX = valgrind
# RUN_PREFIX = valgrind --leak-check=full
# RUN_PREFIX = valgrind --leak-check=full --show-leak-kinds=all

CFLAGS = -g
# CFLAGS =

run: target/analyzer
	$(RUN_PREFIX) ./target/analyzer example/a.rs target/a.asm
	$(RUN_PREFIX) ./target/analyzer example/b.rs target/b.asm

target/analyzer: \
	main.c \
	target/scanner.h target/scanner.c \
	target/analyzer.h target/analyzer.c \
	str_hash_set.h str_hash_set.c \
	global.h global.c \
	string_builder.h string_builder.c \
	common.h common.c \
	Makefile \

	mkdir -p ./target
	gcc $(CFLAGS) -Wall \
		./main.c \
		./target/scanner.c ./target/analyzer.c \
		common.c \
		string_builder.c str_hash_set.c \
		global.c \
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
		-Wcounterexamples \
		--output=./target/analyzer.c \
		--header=./target/analyzer.h \
		analyzer.y

	@mv -f target/analyzer.tmp target/analyzer.stamp

target/analyzer.h target/analyzer.c: target/analyzer.stamp
