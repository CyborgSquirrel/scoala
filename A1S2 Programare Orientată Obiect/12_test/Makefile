.PHONY: all test clean build

# all: test uitest
all: run
# all: app

run: build
	./app

build: Qmakefile
	bear -- make -f Qmakefile

Qmakefile: app.pro *.cpp *.hpp
	qmake -o Qmakefile
