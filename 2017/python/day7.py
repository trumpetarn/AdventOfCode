#class program

def populate_lists(file):
  bottoms = []
  topMembers = []
  lines = []
  for line in file:
    tmp = line[:-1].replace(',','').split(' ')
    lines.append(tmp)
    if "->" in tmp:
      bottoms.append(tmp[0])
      topMembers = topMembers + tmp[3:]
  return bottoms, topMembers, lines

def find_index(name, data):
  for i, line in enumerate(data):
    if name in line[0]:
      return i
  print "Oj"
  return -1

def compute_tree(name, data):
  ret = 0
  i = find_index(name, data)
  num_of_childs = 0
  isBalanced = True
  if "->" in data[i]:
    for name in data[i][3:]:
      val,isBalanced = compute_tree(name, data)
      if num_of_childs > 0 and isBalanced:
        if val != ret/num_of_childs:
          diff = val - ret/num_of_childs
          idx = find_index(name,data)
          bal = int(data[idx][1][1:-1])-diff
          print name,"is imbalanced by",diff,", it should weigh",bal,"to be balanced. (", val, "->", ret/num_of_childs, ")"
          isBalanced = False
      ret = ret + val
      num_of_childs = num_of_childs + 1
  return ret + int(data[i][1][1:-1]), isBalanced
  

def task1(bottoms, top):
  for name in bottoms:
    if not name in top:
      print "Task1:",name
      return name
  
def task2(name, lines):
  compute_tree(name, lines)

def __main__():
  file = open('../new_inputs/input_day7.txt')
  bottoms, top, lines = populate_lists(file)
  name = task1(bottoms, top)
  task2(name, lines)

__main__()

