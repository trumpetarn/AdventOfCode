import threading
import time

def populate_list(filename='../new_inputs/input_day5.txt'):
	file = open(filename)
	mylist = filter(None, list(file.read().split('\n')))
	return map(int, mylist)

def read_and_increment(index, mylist):
	try:
		jumps = mylist[index]
		mylist[index] = jumps+1
	except (IndexError):
		print "List done"
		return len(mylist)
	return jumps
	
def read_and_increment2(index, mylist):
	try:
		jumps = mylist[index]
		if (jumps >= 3):
			mylist[index] = jumps-1
		else:
			mylist[index] = jumps+1
	except (IndexError):
		print "List done"
		return len(mylist)
	return jumps
	
def task1():
	instructions = populate_list()
	i = 0
	steps = 0
	while (i < len(instructions)):
		jumps = read_and_increment(i, instructions)
		i = i + jumps
		steps = steps + 1
	print "Number of steps", steps
	
def task2():
	instructions = populate_list()
	i = 0
	steps = 0
	while (i < len(instructions)):
		jumps = read_and_increment2(i, instructions)
		i = i + jumps
		steps = steps + 1
	print "Number of steps", steps

def main():
	t = threading.Thread(target=task1)
	t.start()
	task2()
	t.join()
	
print "Parallel"
start = time.time()
main()
print "Time: ", (time.time()-start), "s"

print "Seriell"
start = time.time()
task1()
task2()
print "Time: ", (time.time()-start), "s"
