

CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

SRC = cpp
ALL0 = pi_spaces
ALL1 = getlvldiff

all: $(ALL0) $(ALL1)

pi_spaces: pi_spaces.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

getlvldiff: getlvldiff.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(ALL) *.o

test: all
	bash test
