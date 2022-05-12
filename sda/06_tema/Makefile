CXX = g++
CXXFLAGS = -Wall -g

.PHONY: run

run: app
	# valgrind -s ./app
	./app

app: *.cpp *.h
	$(CXX) $(CXXFLAGS) *.cpp -o app
