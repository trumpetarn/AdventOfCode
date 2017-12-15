def format_data(file):
	ret = []
	for line in file:
		data = line[:-1].replace(',','').split(' ')
		lst = [int(i) for i in data[2:]]
		ret.append([int(data[0])]+lst)
	return ret

def find_all_in_group(data,group_id=0):
	done = False
	group = [group_id]
	connected = set([0])
	prev_size = 0
	k = 0
	while not done:
		k += 1
		tmp = []
		for line in data: 
			comp = set(group) & set(line)
			if len(comp) > 0:
				tmp.append(line[0])
		connected = connected | set(tmp)
		group = tmp[:]
		done = (prev_size == len(connected))
		prev_size = len(connected)
	return connected


def task2(data):
	all_pgms = set(range(0,len(data)))
	pgms = set()
	groups = 0
	while len(pgms) < len(data):
		group_id = min(all_pgms)
		pgms = pgms | find_all_in_group(data, group_id)
		all_pgms = all_pgms - pgms
		groups += 1
	return groups


def main():
	file = open('inputs/input_day12.txt')
	data = format_data(file)
	programs = find_all_in_group(data)
	num = task2(data)
	print "Task1:", len(programs)
	print "Task2:", num, "groups"

main()