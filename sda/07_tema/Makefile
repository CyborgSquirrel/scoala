CXX = g++
CXXFLAGS = -g -Wall

.PHONY: test

test: app
	valgrind ./app

app: *.cpp *.h
	$(CXX) $(CXXFLAGS) *.cpp -o app
