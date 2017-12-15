def equals(a,b):
  return a == b

def not_equal(a,b):
  return a != b

def larger_than(a,b):
  return a > b

def less_than(a,b):
  return a < b

def less_than_equal(a,b):
  return a <= b

def larger_than_equal(a,b):
  return a >= 
b
def init_memory(instructions):
	memory = [[],[]]
	for name in instructions:
		if not name[0] in memory[0]:
			memory[0].append(name[0])
			memory[1].append(0)
	return memory
	

def tasks():
  file = open('inputs/input_day8.txt')
  instructions = []
  for line in file:
  	instructions.append(line.split(' '))
	
  mem= init_memory(instructions)
  operations = {'==' : equals,
                '!=' : not_equal,
                '>' : larger_than,
                '<' : less_than,
                '<=' : less_than_equal,
                '>=' : larger_than_equal}
  maximum = ('name', 0)              
  for instr in instructions:
    #instr[0] : name      #instr[1] : inc/dec (+/-)
    #instr[2] : val       #instr[4] : comp_name 
    #instr[5] : operation #instr[6] : comp_val
    comp_id = mem[0].index(instr[4])
    if (operations[instr[5]](mem[1][comp_id],int(instr[6]))):
      idx = mem[0].index(instr[0])
      if (instr[1] == 'inc'):
        mem[1][idx] = mem[1][idx] + int(instr[2])
      else:
        mem[1][idx] = mem[1][idx] - int(instr[2])
    if max(mem[1]) > maximum[1]:
      name = mem[0][mem[1].index(max(mem[1]))]
      maximum = (name, max(mem[1]))
  print "Task1:", max(mem[1])
  print "Task2:", maximum

tasks()