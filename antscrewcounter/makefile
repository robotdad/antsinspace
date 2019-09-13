CXXFLAGS=-w -pedantic -std=c++11 -g -O3 -fpic -msse4.2 -march=native -DNDEBUG

.PHONY: all

all: antscrewcounter rediswq.py

rediswq.py:
	wget https://raw.githubusercontent.com/kubernetes/website/master/content/en/examples/application/job/redis/rediswq.py

csvmonkey.hpp:
	wget https://raw.githubusercontent.com/dw/csvmonkey/csv-game/csvmonkey.hpp

antscrewcounter: antscrewcounter.cpp csvmonkey.hpp

	$(CXX) $(CXXFLAGS) $< -o $@

clean: 
	rm antscrewcounter csvmonkey.hpp rediswq.py
