.PHONY: test run

# test:
# 	make -C test

run: analyzer
	./analyzer

analyzer: lex.yy.c
	gcc lex.yy.c -o analyzer

lex.yy.c: scanner.l
	flex scanner.l
