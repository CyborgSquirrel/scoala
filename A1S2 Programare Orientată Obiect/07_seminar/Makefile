.PHONY: all test clean build

# all: test uitest
all: run
# all: app

run: build
	./app

build: Qmakefile
	make -f Qmakefile

clean:
	make -f Qmakefile clean
	rm Qmakefile

Qmakefile: app.pro *.cpp *.hpp
	qmake -o Qmakefile
