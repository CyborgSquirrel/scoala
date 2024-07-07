.PHONY: all

all: target/conv-static target/conv-dynamic

target:
	mkdir -p ./target

target/conv-static: target conv.cpp
	g++ -O2 -DisStatic -Wall conv.cpp -o target/conv-static

target/conv-dynamic: target conv.cpp
	g++ -O2 -DisDynamic -Wall conv.cpp -o target/conv-dynamic
