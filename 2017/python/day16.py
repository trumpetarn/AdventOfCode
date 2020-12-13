def spin(x, data):
	data = data[-1*x:] + data[:-1*x]
	return data

def exchange(a, b, data):
	tmp = data[a]
	data[a] = data[b]
	data[b] = tmp
	return data

def partner(a,b,data):
	i = data.index(a)
	j = data.index(b)
	return exchange(i,j,data)

def read_instructions(instructions, data):
	for i in instructions:
		if (i[0] == 's'):
			data = spin(int(i[1:]),data[:])
		elif (i[0]=='x'):
			tmp = i[1:].split('/')
			data = exchange(int(tmp[0]),int(tmp[1]),data[:])
		elif (i[0]=='p'):
			tmp = i[1:].split('/')
			data = partner(tmp[0],tmp[1],data[:])
	return data

def main():
	data = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p']
	file = open('../new_inputs/input_day16.txt')
	instructions = file.read().split(',')
	data = read_instructions(instructions, data[:])
	print "Task 1:", ''.join(data)
	''' Part 2 crashes
	for i in range(0,1000000000-1):
		data = read_instructions(instructions, data[:])
	print "Task 2:", ''.join(data)
	'''
main()