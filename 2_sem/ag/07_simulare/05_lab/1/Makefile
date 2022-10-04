CXX = g++
CXXFLAGS = -Wall -g

.PHONY: run

run: prufer-codare
	./prufer-codare 1-in.txt 1-out-test.txt
	diff -Z 1-out.txt 1-out-test.txt
	./prufer-codare 2-in.txt 2-out-test.txt
	diff -Z 2-out.txt 2-out-test.txt
	./prufer-codare 3-in.txt 3-out-test.txt
	diff -Z 3-out.txt 3-out-test.txt
	./prufer-codare 4-in.txt 4-out-test.txt
	diff -Z 4-out.txt 4-out-test.txt
	./prufer-codare 5-in.txt 5-out-test.txt
	diff -Z 5-out.txt 5-out-test.txt
	./prufer-codare 6-in.txt 6-out-test.txt
	diff -Z 6-out.txt 6-out-test.txt
	./prufer-codare 7-in.txt 7-out-test.txt
	diff -Z 7-out.txt 7-out-test.txt
	./prufer-codare 8-in.txt 8-out-test.txt
	diff -Z 8-out.txt 8-out-test.txt
	./prufer-codare 9-in.txt 9-out-test.txt
	diff -Z 9-out.txt 9-out-test.txt

prufer-codare: p1.cpp
	$(CXX) $(CXXFLAGS) p1.cpp -o prufer-codare
