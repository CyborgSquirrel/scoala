CXX = g++
CXXFLAGS = -Wall -g

.PHONY: run

run: app
	./app

pseudocod.pdf: ./pseudocod.md
	pandoc pseudocod.md --output=pseudocod.pdf

app: *.cpp *.h
	$(CXX) $(CXXFLAGS) -o app *.cpp *.h
