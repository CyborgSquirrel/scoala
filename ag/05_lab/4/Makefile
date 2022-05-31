CXX = g++
CXXFLAGS = -Wall -g

.PHONY: run

run: huffman-decodare
	./huffman-decodare 1-in.txt 1-out-test.txt
	diff -Z 1-out.txt 1-out-test.txt
	./huffman-decodare 2-in.txt 2-out-test.txt
	diff -Z 2-out.txt 2-out-test.txt
	./huffman-decodare 3-in.txt 3-out-test.txt
	diff -Z 3-out.txt 3-out-test.txt
	./huffman-decodare 4-in.txt 4-out-test.txt
	diff -Z 4-out.txt 4-out-test.txt
	./huffman-decodare 5-in.txt 5-out-test.txt
	diff -Z 5-out.txt 5-out-test.txt

huffman-decodare: p4.cpp
	$(CXX) $(CXXFLAGS) p4.cpp -o huffman-decodare
