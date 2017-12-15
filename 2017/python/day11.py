def add_lists(a,b):
	for idx, v in enumerate(a):
		a[idx]=a[idx]+b[idx]
	return a

def cube_distance(a, b):
  return (abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2])) / 2	

def hexgrid_walk(data):
	'''Solution using https://www.redblobgames.com/grids/hexagons/'''
	coord = [0, 0, 0]
	# North/South should cancel as nw/se and ne/sw
	coords = {'n':[1, -1, 0],'s':[-1, 1, 0],'nw':[1, 0, -1],'ne':[0, -1, 1],'sw':[0, 1, -1],'se':[-1, 0, 1]}
	max_len = 0
	for d in data:
		coord = add_lists(coord, coords[d])
		val = cube_distance(coord, [0,0,0])
		if val > max_len:
			max_len = val
	return val, max_len


def main():
	file = open('inputs/input_day11.txt')
	data = file.read()
	data = data[:-1].split(',')
	steps, dist = hexgrid_walk(data)
	print "Task1:", steps,"steps"
	print "Task2:", dist,"steps"

main()