CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: rorschach


rorschach: rorschach.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f rorschach
