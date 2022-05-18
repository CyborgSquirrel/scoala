CXX = g++
CXXFLAGS = -Wall

.PHONY: test

test: p2
	./p2 ./1-in.txt ./1-out-test.txt
	diff ./1-out-test.txt ./1-out.txt
	./p2 ./2-in.txt ./2-out-test.txt
	diff ./2-out-test.txt ./2-out.txt
	./p2 ./3-in.txt ./3-out-test.txt
	diff ./3-out-test.txt ./3-out.txt
	./p2 ./4-in.txt ./4-out-test.txt
	diff ./4-out-test.txt ./4-out.txt
	./p2 ./5-in.txt ./5-out-test.txt
	diff ./5-out-test.txt ./5-out.txt
	./p2 ./6-in.txt ./6-out-test.txt
	diff ./6-out-test.txt ./6-out.txt
	./p2 ./7-in.txt ./7-out-test.txt
	diff ./7-out-test.txt ./7-out.txt
	./p2 ./8-in.txt ./8-out-test.txt
	diff ./8-out-test.txt ./8-out.txt
	./p2 ./9-in.txt ./9-out-test.txt
	diff ./9-out-test.txt ./9-out.txt
	./p2 ./10-in.txt ./10-out-test.txt
	diff ./10-out-test.txt ./10-out.txt

p2: p2.cpp
	$(CXX) $(CXXFLAGS) p2.cpp -o p2
