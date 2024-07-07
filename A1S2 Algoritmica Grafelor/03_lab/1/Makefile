$CXX=g++
$CXXFLAGS=-Wall

test: app
	./app 1-in.txt 1-out-test.txt
	diff 1-out.txt 1-out-test.txt
	./app 2-in.txt 2-out-test.txt
	diff 2-out.txt 2-out-test.txt
	./app 3-in.txt 3-out-test.txt
	diff 3-out.txt 3-out-test.txt
	./app 4-in.txt 4-out-test.txt
	diff 4-out.txt 4-out-test.txt
	./app 5-in.txt 5-out-test.txt
	diff 5-out.txt 5-out-test.txt
	./app 6-in.txt 6-out-test.txt
	diff 6-out.txt 6-out-test.txt
	./app 7-in.txt 7-out-test.txt
	diff 7-out.txt 7-out-test.txt

app: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o app
