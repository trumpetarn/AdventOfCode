#!/usr/bin/env python
from __future__ import print_function
from python import day01,day02
import os
import sys
import time

'''Include all Python funcs'''
pyDay = [day01.main, day02.main]
'''Include all solved days in cpp'''
cppDay = [1, 2]

def timeit(func):
	start = time.time()
	func()
	end = time.time()
	print("Execution time:", (1000)*(end-start), "ms");


def runCpp(n):
	if n in cppDay:
		print("C++")
		cmd = 'cd cpp && make day%02d' % n
		os.system(cmd)
	else:
		print("No C++ soultion")

def runPy(n):
	if n-1 < len(pyDay):
		print("Python")
		timeit(pyDay[n-1])
	else:
		print("No Python solution")

if (len(sys.argv)>1):
	for i in sys.argv[1:]:
		n = int(i)
		print("--- Day %d---" % n)
		runCpp(n)
		runPy(n)
		print("")
else:
	for i in range(1,26):
		if (i in cppDay) or (i-1 < len(pyDay)):
			print("--- Day %d---" % i)
			runCpp(i)
			runPy(i)
			print("")