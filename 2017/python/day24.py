"""This is only part 1 and was considered slow, when faulty, full solution in c"""

def get_ports(port, components, hist):
	ret = []
	for c in components:
		if port in c and c not in hist:
			ret.append(c)
	return ret

def max_tree(port, components, hist):
	ret = get_ports(port, components, hist)
	if len(ret) == 0:
		return 0
	maxi = 0;
	for i, c in enumerate(ret):
		hist.append(c)
		stren = sum(c)
		if c[0] == port:
			val = max_tree(c[1], components, hist)
		else:
			val = max_tree(c[0], components, hist)
		if val+stren > maxi:
			maxi = val+stren
		hist.remove(c)
	return maxi

a = open("inputs/input_day24.txt", 'r')
inputs = a.read().split('\n')
components = []
for comp in inputs:
	if comp != '':
		tmp = comp.split('/')
		components.append((int(tmp[0]),int(tmp[1])))

print max_tree(0,components[:],[])