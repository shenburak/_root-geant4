APPS = ingest analysis
CXX ?= $(shell root-config --cxx)
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 $(shell root-config --cflags)
LDFLAGS = $(shell root-config --ldflags)
LDLIBS = $(shell root-config --libs)

all: $(APPS)

ingest: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

analysis: analysis.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(APPS) *.o *.root *.png
