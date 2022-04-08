CXX=clang++
CXXFLAGS=-Wall -g

.PHONY: run

run: app
	valgrind ./app

app: *.cpp *.h *.hpp
	$(CXX) $(CXXFLAGS) *.cpp -o app
