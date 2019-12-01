CC=gcc
CXX=g++
CPPFLAGS=-g -Wall
RM=rm -f

SRCS=$(wildcard *.cpp)
FILTER_SRC=$(filter-out aoc.cpp, $(SRCS))
OBJS=$(subst .cpp,.o,$(SRCS))
FILTER_OBJS=$(subst .cpp,.o,$(FILTER_SRCS))

all: aoc

run: all
	@ ./aoc.out

aoc: $(OBJS)
	@ $(CXX) -o aoc.out $(OBJS)

aoc.o: aoc.cpp aoc.h
	@ $(CXX) -c aoc.cpp $(CPPFLAGS)

$(FILTER_OBJS): $(FILTER_SRC)
	@ $(CXX) -c $< $(CPPFLAGS)

.PHONY: clean

clean:
	@rm -f $(OBJS) *.out