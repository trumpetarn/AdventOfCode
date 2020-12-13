import numpy as np
import itertools

def read_input():
	in_data = open("../new_inputs/input_day21.txt")
	convertions = {}
	for line in in_data:
		data = line.split(' ')
		convertions[data[0]] = data[2]
	return convertions

def init_image():
	debug = ['.#2.','1#..','.3##','.#4#']
	img = ['.#.','..#','###']
	return img, debug

def print_image(img):
	for line in img:
		print line

def flip_img(img):
	i = 0
	for line in img:
		img[i] = line[::-1]
		i += 1
	return img

def rotate_img(img):
	''' Rotates the image clockwise '''
	rot = []
	for i in range(0, len(img)):
		rot.append("")
		for j in range(0, len(img)):
			rot[i] += img[j][i]
	return flip_img(rot)

def flatten_img(img):
	s = ""
	for line in img:
		s += line + '/'
	return s[:-1]

def unflatten_img(simg):
	img = [""]
	i = 0;
	for c in simg:
		if c == '/':
			img.append("")
			i += 1
		else:
			img[i] += c
	return img

def split(img, l=2):
	parts = []
	for i in range(0,len(img),l):
		for j in range(0,len(img),l):
			tmp = []
			for k in range(0,l):
				tmp.append(img[i:i+l][k][j:j+l])
			parts.append(tmp)
	return parts

def merge_img(imgs):
	n = np.sqrt(len(imgs))
	img = []
	row = -1
	for i in range(0,len(imgs)):
		if i%n==0:
			img.append(imgs[i])
			row += 1
		else:
			for j in range(0,len(imgs[i])):
				img[row][j] += imgs[i][j]

	return list(itertools.chain.from_iterable(img))

def enhance(img, k, conv):
	img = split(img, k)
	new_img = []
	for item in img:
		simg = flatten_img(item)
		tmp = item[:]
		i = 0
		while not simg in conv:
			if i == 4:
				tmp = flip_img(tmp)
			if i < 8:
				tmp = rotate_img(tmp)
			else:
				break
			i+=1
			simg = flatten_img(tmp)
		simg = conv[simg][:-1]
		new_img.append(unflatten_img(simg))
	return merge_img(new_img)

def calculate_on(img):
	return flatten_img(img[:]).count('#')

conv = read_input()
img, debug = init_image()
for i in range(0,18):
	if i == 5:
		print "Part1;", calculate_on(img)
	if len(img)%2 == 0:
		img = enhance(img, 2, conv)
	elif len(img)%3 == 0:
		img = enhance(img, 3, conv)
	else:
		print "??"

print "Part2:", calculate_on(img)