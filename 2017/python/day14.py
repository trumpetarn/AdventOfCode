import day10

def hash_to_binary(hashstr):
	bin_str = ""
	for hval in hashstr:
		bin_str += str(bin(int(hval, 16)))[2:].zfill(4)
	return bin_str

def generate_grid(in_data):
	num_used = 0
	N = list(range(0,256))
	grid = []
	for i in range(0,128):
		hash_in = in_data + '-' + str(i)
		hashstr = day10.generate_knothash(hash_in)
		binstr = hash_to_binary(hashstr)
		num_used += binstr.count('1')
		grid.append(binstr.replace('1','#').replace('0','.'))
	return grid, num_used

def get_neighbors(i,j, size=128):
	nums = set()
	if i+1 < size:
		nums.add((i+1,j))
	if j+1 < size:
		nums.add((i,j+1))
	if i-1 >= 0:
		nums.add((i-1,j))
	if j-1 >= 0:
		nums.add((i,j-1))
	return nums

def grid_printer(grid, N):
	'''Used for debugging mostly'''
	for i in range(0,N):
		print grid[i][:N]

def grouping(grid, i, j, group_id='*'):
	if grid[i][j]=='#':
		grid[i] = grid[i][:j] + group_id + grid[i][j+1:]
		neighbors = get_neighbors(i,j,len(grid))
		for k in neighbors:
			grouping(grid, k[0], k[1], group_id)
		return True
	return False

def find_groups(grid):
	group_id = 0
	for i in range(0,len(grid)):
		for j in range(0,len(grid)):
			if grouping(grid, i, j, str(hex(group_id)[-1])):
				group_id += 1
	return group_id

def main():
	in_data = "hwlqcszp"
	grid, num_used = generate_grid(in_data)
	print "Task 1:",num_used
	print "Task 2;",find_groups(grid)

if __name__ == "__main__":
	main()