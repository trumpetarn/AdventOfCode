"""
Day 02: 1202 Program Alarm
"""
from __future__ import print_function

def add(a, b):
	return a+b

def multiply(a, b):
	return a*b

def intcode(mem):
	pos = 0;
	for i in mem:
		if (pos==0):
			if i==1:
				p0 = add
			elif i==2:
				p0 = multiply
			else:
				return mem[0]
		elif (pos==1):
			p1 = i
		elif (pos==2):
			p2 = i
		elif (pos==3):
			p3 = i
			mem[p3] = p0(mem[p1], mem[p2])
		else:
			print("ERROR")
		pos = (pos + 1) % 4

def star1(dayInput):
	dayInput[1] = 12
	dayInput[2] = 2
	return intcode(dayInput)

def star2(dayInput):
	for i in range(1,100):
		for j in range(1,i):
			dayInput[1] = i
			dayInput[2] = j
			if (intcode(dayInput[:]) == 19690720):
				return 100*i+j
	return -1

def main():
	dayInput = [1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,1,19,5,23,2,23,9,27,1,5,27,31,1,9,31,35,1,35,10,39,2,13,39,43,1,43,9,47,1,47,9,51,1,6,51,55,1,13,55,59,1,59,13,63,1,13,63,67,1,6,67,71,1,71,13,75,2,10,75,79,1,13,79,83,1,83,10,87,2,9,87,91,1,6,91,95,1,9,95,99,2,99,10,103,1,103,5,107,2,6,107,111,1,111,6,115,1,9,115,119,1,9,119,123,2,10,123,127,1,127,5,131,2,6,131,135,1,135,5,139,1,9,139,143,2,143,13,147,1,9,147,151,1,151,2,155,1,9,155,0,99,2,0,14,0]
	ans1 = star1(dayInput[:])
	ans2 = star2(dayInput[:])
	print("Star 1:", ans1)
	print("Star 2:", ans2)
if __name__== "__main__":
	main()