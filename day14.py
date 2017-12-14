import day10

def hash_to_binary(hashstr):
	bin_str = ""
	for hval in hashstr:
		bin_str += str(bin(int(hval, 16)))[2:].zfill(4)
	return bin_str

def main():
	in_data = "hwlqcszp"
	num_used = 0
	N = list(range(0,256))
	for i in range(0,128):
		hash_in = in_data + '-' + str(i)
		hashstr = day10.generate_knothash(hash_in)
		binstr = hash_to_binary(hashstr)
		num_used += binstr.count('1')
	print num_used
main()