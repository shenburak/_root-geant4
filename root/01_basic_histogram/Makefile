APP = basic_histogram
CXX ?= $(shell root-config --cxx)
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 $(shell root-config --cflags)
LDFLAGS = $(shell root-config --ldflags)
LDLIBS = $(shell root-config --libs)

$(APP): main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(APP) *.o *.root *.png
