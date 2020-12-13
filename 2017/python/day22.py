DIRECTIONS = ['UP','RIGHT','DOWN','LEFT']

def increase_map(pos, MAP):
	pos[0] += 1
	pos[1] += 1
	MAP = ["."*len(MAP)] + MAP + ["."*len(MAP)]
	for i, line in enumerate(MAP):
		MAP[i] = '.' + line + '.'
	return pos, MAP

def move(pos, d, MAP):
	if d==DIRECTIONS[0]:
		pos[1] -= 1
	elif d==DIRECTIONS[1]:
		pos[0] += 1
	elif d==DIRECTIONS[2]:
		pos[1] += 1
	elif d==DIRECTIONS[3]:
		pos[0] -= 1
	while pos[0] >= len(MAP) or pos[1] >= len(MAP) or pos[0] < 0 or pos[1] < 0:
		pos, MAP = increase_map(pos,MAP)
	return pos, MAP

def clean(current_pos, MAP):
	tmp = list(MAP[current_pos[1]])
	tmp[current_pos[0]] = '.'
	MAP[current_pos[1]] = "".join(tmp)
	return MAP

def infect(current_pos, MAP):
	tmp = list(MAP[current_pos[1]])
	tmp[current_pos[0]] = '#'
	MAP[current_pos[1]] = "".join(tmp)
	return MAP

def weaken(current_pos, MAP):
	tmp = list(MAP[current_pos[1]])
	tmp[current_pos[0]] = 'w'
	MAP[current_pos[1]] = "".join(tmp)
	return MAP

def flag(current_pos, MAP):
	tmp = list(MAP[current_pos[1]])
	tmp[current_pos[0]] = 'f'
	MAP[current_pos[1]] = "".join(tmp)
	return MAP

def turn_right(current_dir):
	current = DIRECTIONS.index(current_dir)
	return DIRECTIONS[(current+1)%len(DIRECTIONS)]

def turn_left(current_dir):
	current = DIRECTIONS.index(current_dir)
	return DIRECTIONS[(current-1)%len(DIRECTIONS)]

def turn_around(current_dir):
	current = DIRECTIONS.index(current_dir)
	return DIRECTIONS[(current+2)%len(DIRECTIONS)]

def work(pos, current_dir, MAP, iterations=1, part=1):
	infections = 0
	for i in range(iterations):
		node = MAP[pos[1]][pos[0]]
		if part==1:
			if node == '#':
				current_dir = turn_right(current_dir)
				MAP = clean(pos, MAP)
			else:
				infections += 1
				current_dir = turn_left(current_dir)
				MAP = infect(pos, MAP)
		else:
			if node == '#':
				current_dir = turn_right(current_dir)
				MAP = flag(pos, MAP)
			elif node == 'f':
				current_dir = turn_around(current_dir)
				MAP = clean(pos, MAP)
			elif node == 'w':
				MAP = infect(pos, MAP)
				infections += 1
			else: #clean
				current_dir = turn_left(current_dir)
				MAP = weaken(pos, MAP)
		pos, MAP = move(pos, current_dir, MAP)
	return pos, current_dir, MAP, infections

def init_map(debug=False):
	in_data = """.....###..#....#.#..##...
......##.##...........##.
.#..#..#.#.##.##.........
...#..###..##.#.###.#.#.#
##....#.##.#..####.####..
#..##...#.##.##.....##..#
.#.#......#...####...#.##
###....#######...#####.#.
##..#.####...#.#.##......
##.....###....#.#..#.##.#
.#..##.....#########.##..
##...##.###..#.#..#.#...#
...####..#...#.##.#..####
.#..##......#####..#.###.
...#.#.#..##...#####.....
#..###.###.#.....#.#.###.
##.##.#.#.##.#..#..######
####.##..#.###.#...#..###
.........#####.##.###..##
..#.##.#..#..#...##..#...
###.###.#.#..##...###....
##..#.#.#.#.#.#.#...###..
#..#.#.....#..#..#..##...
........#######.#...#.#..
..##.###.#.##.#.#.###..##"""
	if debug:
		in_data = """..#
#..
..."""
	data = in_data.split('\n')
	centre = [len(data)/2, len(data[0])/2]
	position = centre
	return data, position

def print_map(MAP, current_pos):
	tmp = MAP[:]
	tmp2 = list(tmp[current_pos[1]])
	if tmp2[current_pos[0]] == '.':
		tmp2[current_pos[0]] = '*'
	else:
		tmp2[current_pos[0]] = '='
	tmp[current_pos[1]] = "".join(tmp2)
	for line in tmp:
		print len(line),":", line


MAP, pos = init_map(debug=False)
d = DIRECTIONS[0]
pos, d, MAP, inf = work(pos, d, MAP, 10000000, 2)

print inf
#print_map(MAP,pos)