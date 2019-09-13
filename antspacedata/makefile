CXXFLAGS=-w -std=c++11 -g -pedantic -O3 -fpic -msse4.2 -march=native -DNDEBUG

.PHONY: all

all: antspacedata

antspacedata: antspacedata.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean: 
	rm antspacedata 