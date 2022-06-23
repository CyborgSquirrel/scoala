.PHONY: all test clean build

# all: test uitest
all: run
# all: app

run: build
	./target/app

build: target/Qmakefile
	cd ./target/ ; \
	bear --output ../compile_commands.json -- make -f Qmakefile

clean:
	cd ./target; make -f Qmakefile clean
	rm target/Qmakefile

target/Qmakefile: app.pro *.cpp *.hpp
	qmake -o target/Qmakefile
