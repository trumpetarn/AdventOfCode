import threading
import time

def init_firewall(filename='inputs/input_day13.txt'):
	file = open(filename)
	data = file.read().split('\n')
	firewall = []
	current_idx = 0
	for line in data[:-1]: #Remove last empty line
		temp_data = line.split(': ')
		depth = int(temp_data[0])
		rnge = int(temp_data[1])
		for i in range(current_idx, depth):
			firewall.append(None)
		firewall.append([0]*rnge)
		current_idx = depth+1
	return firewall

def scan(firewall, step, delay_set={}):
	'''Returns True if "caught"
	if delay is set it will calculate for all delays in the set
	and only return False if a delay passes trough'''
	if len(delay_set) == 0:
		if firewall[step] is None:
			return False
		return firewall[step][0] == 1
	ret = True
	if (step - min(delay_set)) >= len(firewall):
		return False, delay_set
	relevant = set(range(step-len(firewall),step+1))
	for delay in (relevant & delay_set):
		if not firewall[step-delay] is None:
			if firewall[step-delay][0] == 1:
				ret = True
				delay_set = delay_set - {delay}
	return ret, delay_set
	
	

def start_scanner(firewall):
	for layer in firewall:
		if not layer is None:
			layer[0] = 1
		
def reset_scanner(firewall):
	for layer in firewall:
		if not layer is None:
			for i in range(0,len(layer)):
				layer[i] = 0

def move_scanner(firewall):
	for layer in firewall:
		if not layer is None:
			idx = layer.index(1)
			if layer[0] == -1:
				next_i = idx-1
			else:
				next_i = (idx+1) % len(layer)
				if next_i == 0:
					layer[0] = -1
					next_i = idx-1
			layer[idx] = 0
			layer[next_i] = 1

def task1():
	fwall = init_firewall()
	start_scanner(fwall)
	severity = 0
	for step in range(0,len(fwall)):
		if scan(fwall, step):
			severity += step*len(fwall[step])
		move_scanner(fwall)
	print "Task 1, Trip severity:", severity

def task2():
	'''Slow solution??'''
	start = time.time()
	fwall = init_firewall()
	delay = 78150
	caught = True
	while caught:
		delay += 1
		caught = False
		start_scanner(fwall)
		for d in range(0,delay):
			move_scanner(fwall)
		for step in range(0,len(fwall)):
			if scan(fwall, step):
				caught = True
				break
			move_scanner(fwall)
		reset_scanner(fwall)
	print "Task 2, Delay:", delay, 'picoseconds'
	print "Time2: ", (time.time()-start), "s"

def task2b():
	start = time.time()
	fwall = init_firewall()#'inputs/input_test.txt')
	start_scanner(fwall)
	d_set = set(range(0,100000))
	ret = True
	step = -1
	while ret:
		step += 1
		ret, d_set = scan(fwall, step, delay_set=d_set)
		if len(d_set)==0:
			d_set = {-1}
			break
		move_scanner(fwall)
	print "Task 2, Delay:", min(d_set), 'picoseconds'
	print "Time: ", (time.time()-start), "s"

task1()

#t = threading.Thread(target=task2)
#t.start()
task2b()
#t.join()	
