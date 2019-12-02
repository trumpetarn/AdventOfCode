CC=gcc
CXX=g++
CPPFLAGS=-g -Wall
RM=rm -f

SRCS=$(wildcard *.cpp)
FILTER_SRC=$(filter-out aoc.cpp, $(SRCS))
OBJS=$(subst .cpp,.o,$(SRCS))
FILTER_OBJS=$(subst .cpp,.o,$(FILTER_SRCS))
DAY_SRC=$(wildcard day*.cpp)
DAY=$(subst .cpp,,$(DAY_SRC))

all: aoc

run: all
	@ ./aoc.out

aoc: $(OBJS)
	@ $(CXX) -o aoc.out $(OBJS)

aoc.o: aoc.cpp aoc.h
	@ $(CXX) -c aoc.cpp $(CPPFLAGS)

$(FILTER_OBJS): $(FILTER_SRC)
	@ $(CXX) -c $< $(CPPFLAGS)

$(DAY): all
	@ ./aoc.out $(subst day,,$@)

.PHONY: clean

clean:
	@rm -f $(OBJS) *.out