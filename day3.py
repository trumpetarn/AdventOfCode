from __future__ import print_function
"""
17  16  15  14  13
18   5   4   3  12
19   6   1   2  11 
20   7   8   9  10 
21  22  23	24	25 
"""
import numpy as np


def radius(value):
	i = (np.sqrt(value)+1)/2.0-1
	return np.ceil(i)

def values_inside(r):
	# Number of values that has r-1 distance to centre
	return (2*r-1)**2
	
def axis_values(value):
	r = radius(value)
	inside = values_inside(r)
	n = values_inside(r+1) - inside
	x = n*1.0/4
	x1 = inside + x/2
	x2 = x1 + x
	x3 = x2 + x
	x4 = x3 + x
	return np.array([x1,x2,x3,x4])
	
def distance_from_centre(value):
	distance_from_axis = np.min(np.abs(axis_values(value) - value))
	return distance_from_axis + radius(value)

def task1():
	val = 277678
	print("Task 1:", distance_from_centre(val) )

def next_index(i,j,x):
	# left
	if (x[i][j-1] == 0 and x[i+1][j] != 0):
		return i, j-1
	#top
	if (x[i-1][j] == 0 and x[i][j-1] != 0):
		return i-1, j
	#down
	if (x[i+1][j] == 0 and x[i][j+1] != 0):
		return i+1, j
	#right
	return i, j+1
	
def sum_of_neighbors(x,i,j):
	sum = x[i+1][j]+x[i][j+1]+x[i-1][j]+x[i][j-1]+x[i+1][j+1]+x[i+1][j-1]+x[i-1][j+1]+x[i-1][j-1]
	return sum

def print_matrix(x, n):
	for i in range(0,n):
		for j in range(0,n):
			if (i==j) and (n/2 == i):
				print('(', int(x[i][j]), ')\t', end='')
			elif (int(x[i][j])!=0):
				print(int(x[i][j]), "\t", end='')
			else:
				print(" ", "\t", end='')
			
		print("\n", end='')
	
def task2():
	val = 277678
	n =11
	x =  np.zeros((n, n))
	i = n//2
	j = n//2
	x[i][j] = 1
	j = j+1
	x[i][j] = 1
	while x[i][j] < val:
		i,j = next_index(i,j,x)
		x[i][j] = sum_of_neighbors(x,i,j)
	print("Task 2:", x[i][j])
	print_matrix(x, n)
	
task1()
task2()


# 1, 1, 2, 4, 5, 10, 11, 23, 25, 26, 54,
