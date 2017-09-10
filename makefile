CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LXX = g++
LXXFLAGS = -L.

all: rorschach

rorschach.o: rorschach.cpp
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

rule_runner.o: rule_runner.cpp
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

scanner.o: scanner.cpp
	@echo "Compiling $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

rorschach: rorschach.o scanner.o rule_runner.o
	@echo "Linking $@..."
	@$(LXX) $(LXXFLAGS) -o $@ $^

clean:
	rm -f rorschach
	rm -f *.o
