

CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

SRC = cpp
ALL = pi_spaces getlvldiff

all: $(ALL) 

pi_spaces: pi_spaces.cpp
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

getlvldiff: getlvldiff.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(ALL) *.o

test: all
	bash test
