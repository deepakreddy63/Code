

CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

SRC = cpp
ALL = pi_spaces getlvldiff

all: $(ALL) 

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

.PHONY: clean
clean:
	$(RM) $(ALL) *.o

test: all
	bash test
