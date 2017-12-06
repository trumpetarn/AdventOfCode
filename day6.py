
def get_max_index(memory):
	index = 0
	max = -1
	for i,val in enumerate(memory):
		if val > max:
			index = i
			max = val
	return index

def distribute_memory(memory, index):
	mem_len = len(memory)
	mem_val = memory[index]
	memory[index] = 0
	for i in range(0, mem_val):
		idx = (index + 1 + i) % mem_len
		memory[idx] = memory[idx] + 1
	return memory
	
def tasks():
	mem = [[10,3,15,10,5,15,5,15,9,2,5,8,5,2,3,6]]
	i = get_max_index(mem[0][:])
	new = distribute_memory(mem[0][:], i)
	while (not new in mem):
		mem.append(new)
		i = get_max_index(mem[-1][:])
		new = distribute_memory(mem[-1][:], i)
	print "Task 1", len(mem)
	print "Task 2:", len(mem) - mem.index(new)
	print "Recurring line", new
	
tasks()