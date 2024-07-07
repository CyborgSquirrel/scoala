CXX = g++
CXXFLAGS = -Wall

.PHONY: test

test: p3
	./p3 ./1-in.txt ./1-out-test.txt
	diff ./1-out-test.txt ./1-out.txt
	./p3 ./2-in.txt ./2-out-test.txt
	diff ./2-out-test.txt ./2-out.txt
	./p3 ./3-in.txt ./3-out-test.txt
	diff ./3-out-test.txt ./3-out.txt
	./p3 ./4-in.txt ./4-out-test.txt
	diff ./4-out-test.txt ./4-out.txt
	./p3 ./5-in.txt ./5-out-test.txt
	diff ./5-out-test.txt ./5-out.txt
	./p3 ./6-in.txt ./6-out-test.txt
	diff ./6-out-test.txt ./6-out.txt
	./p3 ./7-in.txt ./7-out-test.txt
	diff ./7-out-test.txt ./7-out.txt
	./p3 ./8-in.txt ./8-out-test.txt
	diff ./8-out-test.txt ./8-out.txt
	./p3 ./9-in.txt ./9-out-test.txt
	diff ./9-out-test.txt ./9-out.txt

p3: p3.cpp
	$(CXX) $(CXXFLAGS) p3.cpp -o p3
