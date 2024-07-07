CXX = g++
CXXFLAGS = -Wall -g

.PHONY: run

run: huffman-codare
	./huffman-codare 1-in.txt 1-out-test.txt
	diff -Z 1-out.txt 1-out-test.txt
	./huffman-codare 2-in.txt 2-out-test.txt
	diff -Z 2-out.txt 2-out-test.txt
	./huffman-codare 3-in.txt 3-out-test.txt
	diff -Z 3-out.txt 3-out-test.txt
	./huffman-codare 4-in.txt 4-out-test.txt
	diff -Z 4-out.txt 4-out-test.txt
	./huffman-codare 5-in.txt 5-out-test.txt
	diff -Z 5-out.txt 5-out-test.txt

huffman-codare: p3.cpp
	$(CXX) $(CXXFLAGS) p3.cpp -o huffman-codare
