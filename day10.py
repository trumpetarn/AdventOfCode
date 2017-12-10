def knoting(lengths, numbers, pos=0, skip=0):
	for i in lengths:
		idx1 = pos
		idx2 = (pos + i) % len(numbers)
		if idx1 < idx2:
			sublist = numbers[idx1:idx2][::-1]
			numbers = numbers[0:idx1] + sublist + numbers[idx2:]
		elif i != 0:
			sublist = (numbers[idx1:]+numbers[0:idx2])[::-1]
			numbers[idx1:] = sublist[0:len(numbers[idx1:])]
			numbers[:idx2] = sublist[len(numbers[idx1:]):]
		prev = numbers[:]
		pos = (pos + i + skip) % len(numbers)
		skip += 1
	return numbers, pos, skip

def string_to_ascii(s):
	lst = []
	for c in s:
		lst.append(ord(c))
	return lst

def create_hashstring(lst):
	hstr = ""
	for i in lst:
		hstr += str(hex(i))
	return hstr.replace('0x','')

def generate_hash(numbers, div=16):
	blocks = len(numbers)/div
	xor = []
	for i in range(0,blocks):
		tmp = numbers[i*blocks]
		for j in range(1,div):
			tmp = tmp ^ numbers[i*blocks+j]
		xor.append(tmp)
	return create_hashstring(xor)

def task1():
	N = list(range(0,256))
	lengths = [83,0,193,1,254,237,187,40,88,27,2,255,149,29,42,100]
	numbers,_,_ = knoting(lengths, N)
	print "Task 1:", numbers[0]*numbers[1]

def task2():
	numbers = list(range(0,256))
	in_data = "83,0,193,1,254,237,187,40,88,27,2,255,149,29,42,100"
	buff = [17, 31, 73, 47, 23]
	lengths = string_to_ascii(in_data) + buff
	p=0
	s=0
	for i in range(0,64):
		numbers,p,s = knoting(lengths, numbers, pos=p, skip=s)
	xor = generate_hash(numbers)
	print "Task 2:",xor

task1()
task2()