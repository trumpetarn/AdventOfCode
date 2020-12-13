def clean_input(line):
	clean_str = []
	is_garbage = False
	num_of_garbage = 0
	last_char = ''
	for char in line:
		if last_char != '!':
			if not is_garbage:
				if char == '{':
					clean_str.append(char)
				elif char == '<':
					is_garbage = True
				elif char == '}':
					clean_str.append(char)
				else:
					clean_str.append(char)
			else:
				if char == '>':
					is_garbage = False
				elif char != '!':
					num_of_garbage = num_of_garbage + 1
			last_char = char
		elif char == '!':
			last_char = ''
		else:
			last_char = char
	return clean_str, num_of_garbage

def tasks():
	file = open('../new_inputs/input_day9.txt')
	line = file.readline()
	clean_str,garbage = clean_input(line[0:-1])
	points = 0
	level = 0
	for char in clean_str:
		if char == '{':
			level = level + 1
		elif char == '}':
			points = points + level
			level = level - 1
	print "Task 1:", points
	print "Task 2:", garbage

tasks()