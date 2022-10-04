CXX = g++
CXXFLAGS = -g -Wall

.PHONY: test

test: app
	./app

app: *.cpp *.h
	$(CXX) $(CXXFLAGS) *.cpp -o app
