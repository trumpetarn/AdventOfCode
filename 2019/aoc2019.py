#!/usr/bin/env python
from __future__ import print_function
from python import day01
import os
import time

def timeit(func):
	start = time.time()
	func()
	end = time.time()
	print("Execution time:", (1000)*(end-start), "ms");

print("\n--- C++ ---")
'''Check cpp/aoc.cpp'''
os.system('cd cpp && make run')

print("--- Python ---")
'''Include all Python funcs'''
timeit(day01.main)
