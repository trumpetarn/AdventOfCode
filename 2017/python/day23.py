""" Compare day 18 """
from collections import defaultdict
import signal
import sys


MUL = 0
H = 0

def signal_handler(signal, frame):
	global H
	print 'H:',H
	sys.exit(0)	
signal.signal(signal.SIGINT, signal_handler)

def get_value(c, reg):
	if c in "qwertyuiopasdfghjklzxcvbnm":
		return reg[c]
	return int(c)

def read_instruction(reg, line, idx):
	global MUL
	data = line.split(' ')
	if data[0] == "set":
		reg[data[1]] = get_value(data[2], reg)
	elif data[0] == "sub":
		reg[data[1]] -= get_value(data[2], reg)
	elif data[0] == "mul":
		MUL += 1
		reg[data[1]] *= get_value(data[2], reg)
	elif data[0] == "jnz":
		if get_value(data[1],reg) != 0:
			idx += get_value(data[2], reg)-1
	else:
		print "ERROR"
		print data
		exit()
	idx += 1
	return reg, idx

def task1():
	global MUL
	global H
	idx = 0
	file = open("inputs/input_day23.txt")
	instructions = file.read().split('\n')
	reg = defaultdict(int)
	while 0 <= idx < len(instructions):
		reg, idx = read_instruction(reg, instructions[idx], idx)
	print MUL

def isPrime(n):
	""" Returns whether or not n is prime """
	if n==2 or n==3: return True
	if n%2==0 or n<2: return False
	for i in range(3,int(n**0.5)+1,2):   # only odd numbers
		if n%i==0:
			return False    
	return True	
	
task1()
# Part 2
"""We are calculating all non primes between 109300 and 126300"""
for b in range(109300,126300+1,17):
	if not isPrime(b):
		H += 1
print H