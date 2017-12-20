from collections import defaultdict
""" Done with help from https://www.reddit.com/r/adventofcode/comments/7kj35s/2017_day_18_solutions/dreth75/"""

def value(ins, reg,p):
	if ins[-1] in "qwertyuiopasdfghjklzxcvbnm":
		return reg[p][ins[-1]]
	return int(ins[-1])

def task2(file="inputs/input_day18.txt"):
	data = open(file)
	instructions = data.read().split('\n')
	N = len(instructions)
	#instructions = ["snd 1","snd 2","snd p","rcv a","rcv b","rcv c","rcv d"]
	idx = [0,0]
	p0 = defaultdict(int)
	p1 = defaultdict(int)
	p0['p'] = 0
	p1['p'] = 1
	reg = [p0,p1] 
	send = [[],[]]
	status = ["ok","ok"]
	p = 0 #Current Program
	sends = 0
	i = idx[p]

	while True:
		ins = instructions[i].split(' ')
		#Pre handling of data
		# Main if
		if (ins[0] == "snd"):
			if p == 1:
				sends += 1
			send[p].append(value(ins,reg,p))
		elif (ins[0] == "set"):
			reg[p][ins[1]] = value(ins,reg,p)
		elif (ins[0] == "add"):
			reg[p][ins[1]] += value(ins,reg,p)
		elif (ins[0] == "mul"):
			reg[p][ins[1]] *= value(ins,reg,p)
		elif (ins[0] == "mod"):
			reg[p][ins[1]] %= value(ins,reg,p)
		elif (ins[0] == "rcv"):
			if send[1-p]:
				status[p] = "ok"
				reg[p][ins[1]] = send[1-p].pop(0)
			else:
				if status[p-1] == "done":
					break #Deadlock
				if len(send[p])==0 and status[1-p] == "r":
					break #Both recieving
				status[p] = "r"
				idx[p] = i
				p = 1-p
				i = idx[p]-1
		elif (ins[0] == "jgz"):
			if ins[1] in 'qwertyuiopasdfghjklzxcvbnm':
				if reg[p][ins[1]] > 0:
					i += value(ins,reg,p)-1
			elif ins[1] > 0:
				i += value(ins,reg,p)-1
		i += 1
		if not 0<=i<N:
			status[p]="done"
			if state[1-p] == "done":
				break
			ind[p] = i
			p = 1-p
			i = ind[p]
			break
	print "Task2: Pgm1 sends",sends,"times"

def task1(reg={}, file="inputs/input_day18.txt"):
	data = open(file)
	instructions = data.read().split('\n')
	i = 0
	while i < len(instructions):
		ins = instructions[i].split(' ')
		#Pre handling of data
		if ins[-1] in reg:
			val = reg[ins[-1]]
		else:
			val = int(ins[-1])
		if not ins[1] in reg.keys():
			reg[ins[1]] = 0
		# Main if
		if (ins[0] == "snd"):
			reg['last_played'] = reg[ins[1]]
		elif (ins[0] == "set"):
			reg[ins[1]] = val
		elif (ins[0] == "add"):
			reg[ins[1]] += val
		elif (ins[0] == "mul"):
			reg[ins[1]] *= val
		elif (ins[0] == "mod"):
			reg[ins[1]] = reg[ins[1]] % val
		elif (ins[0] == "rcv"):
			if reg[ins[1]] != 0:
				reg[ins[1]] = reg['last_played']
				print "Task1: Last rcv is",reg[ins[1]]
				break
		elif (ins[0] == "jgz"):
			if reg[ins[1]] > 0:
				i += int(ins[2]) -1
		i += 1

#def task1():
#	readInstructions1({})#, file="inputs/input_test.txt")
task1()
task2()