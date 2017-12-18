"""
snd X plays a sound with a frequency equal to the value of X.
set X Y sets register X to the value of Y.
add X Y increases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Many of the instructions can take either a register (a single letter) or a number. The value of a register is the integer it contains; the value of a number is that number.

After each jump instruction, the program continues with the instruction to which the jump jumped. After any other instruction, the program continues with the next instruction. Continuing (or jumping) off either end of the program terminates it.

What is the value of the recovered frequency (the value of the most recently played sound) the first time a rcv instruction is executed with a non-zero value?"""


def readInstructions(reg, i, instructions, receives):
	sends = []
	status = "ok"
	while True:
		ins = instructions[i].split(' ')
		#Pre handling of data
		if ins[0] != "snd" and not ins[1] in reg.keys():
			reg[ins[1]] = 0
		if ins[-1] in "qwertyuiopasdfghjklzxcvbnm":
			val = reg[ins[-1]]
		else:
			val = int(ins[-1])
		# Main if
		if (ins[0] == "snd"):
			sends.append(val)
		elif (ins[0] == "set"):
			reg[ins[1]] = val
		elif (ins[0] == "add"):
			reg[ins[1]] += val
		elif (ins[0] == "mul"):
			reg[ins[1]] *= val
		elif (ins[0] == "mod"):
			reg[ins[1]] = reg[ins[1]] % val
		elif (ins[0] == "rcv"):
			if len(receives) == 0:
				status = "r"
				break
			reg[ins[1]] = receives.pop(0)
		elif (ins[0] == "jgz"):
			if reg[ins[1]] > 0:
				i += val-1
		i += 1
		if not 0<=i<len(instructions):
			status="done"
			break
	return status, reg, i, sends


def task2(file="inputs/input_day18.txt"):
	data = open(file)
	instructions = data.read().split('\n')
	#instructions = ["snd 1","snd 2","snd p","rcv a","rcv b","rcv c","rcv d"]
	i0 = 0
	i1 = 0
	reg0 = {'p':0}
	reg1 = {'p':1}
	send0 = []
	send1 = []
	status0 = "ok"
	status1 = "ok"
	p0Sends = 0
	p1Sends = 0
	while True:
		print p0Sends, p1Sends
		status0, reg0, i0, send0 = readInstructions(reg0, i0, instructions, send1)
		p0Sends += len(send0)
		if status0 == "r" or status0 == "done":
			if (status1 == "r" and len(send0)==0) or status1 == "done":
				break # Deadlock

		status1, reg1, i1, send1 = readInstructions(reg1, i1, instructions, send0)
		p1Sends += len(send1)
		if status1 == "r" or status1 == "done":
			if (status0 == "r" and len(send1)==0) or status0 == "done":
				break # Deadlock

	print "Ans:",p1Sends
	print p0Sends
	print reg0
	print reg1

"""
		if len(rec0)==0:
			reg0, i0, rec1 = readInstructions(reg0, i0, instructions, rec0[:])
			reg1, i1, rec0 = readInstructions(reg1, i1, instructions, rec1[:])
			p1Sends += len(rec0)
			break
"""	
"""
		if len(rec1)==0:
			reg1, i1, rec0 = readInstructions(reg1, i1, instructions, rec1[:])
			reg0, i0, rec1 = readInstructions(reg0, i0, instructions, rec0[:])
			p1Sends += len(rec0)
			break
"""

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
				print "rcv",reg[ins[1]]
				break
		elif (ins[0] == "jgz"):
			if reg[ins[1]] > 0:
				i += int(ins[2]) -1
		i += 1

#def task1():
#	readInstructions1({})#, file="inputs/input_test.txt")
task1()
task2()