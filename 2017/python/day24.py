"""This is very slow and is incorrect"""

def get_ports(port, components):
	ret = []
	for c in components:
		if port in c:
			ret.append(c)
	return ret

def max_tree(port, components):
	ret = get_ports(port, components)
	if len(ret) == 0:
		return 0
	maxi = 0;
	for i, c in enumerate(ret):
		stren = sum(c)
		tmp = components[0:i]+components[i+1:]
		if c[0] == port:
			val = max_tree(c[1], tmp)
		else:
			val = max_tree(c[0], tmp)
		if val+stren > maxi:
			maxi = val+stren
	return maxi

a = open("inputs/input_test.txt", 'r')
inputs = a.read().split('\n')
components = []
for comp in inputs:
	if comp != '':
		tmp = comp.split('/')
		components.append((int(tmp[0]),int(tmp[1])))

print max_tree(0,components[:])

