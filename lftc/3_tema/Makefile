.PHONY: test run

RUN_PREFIX = 
# RUN_PREFIX = valgrind --leak-check=full
# RUN_PREFIX = valgrind --leak-check=full --show-leak-kinds=all

CFLAGS = -g
# CFLAGS =

run: target/analyzer
	@printf '\n\n=== %s ===\n' 'test/2-1.rs'
	$(RUN_PREFIX) ./target/analyzer test/2-1.rs
	@printf '\n\n=== %s ===\n' 'test/2-2.rs'
	$(RUN_PREFIX) ./target/analyzer test/2-2.rs
	@printf '\n\n=== %s ===\n' 'test/2-3.rs'
	$(RUN_PREFIX) ./target/analyzer test/2-3.rs
	@printf '\n\n=== %s ===\n' 'test/3-1.rs'
	$(RUN_PREFIX) ./target/analyzer test/3-1.rs
	@printf '\n\n=== %s ===\n' 'test/3-2.rs'
	$(RUN_PREFIX) ./target/analyzer test/3-2.rs

target/analyzer: target/flex.c obj.c Makefile
	mkdir -p ./target
	gcc $(CFLAGS) -Wall ./target/flex.c -o ./target/analyzer

target/flex.c: scanner.l
	mkdir -p ./target
	flex -o ./target/flex.c scanner.l
