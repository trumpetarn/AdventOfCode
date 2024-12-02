
"""
Day 02: https://adventofcode.com/2024/day/2
"""
       
def checkRules(l, max=3):
    prev = 0
    incr = False
    for i,v in enumerate(l):
        if i == 0:
            prev = v
            continue
        elif i == 1:
            if (prev == v) or abs(prev-v)>max:
                return False
            elif (prev < v):
                incr = True
            else:
                incr = False
        elif(incr):
            if (prev >= v) or abs(prev-v)>max:
                return False
        else:
            if (prev <= v) or abs(prev-v)>max:
                return False
        prev = v
    return True
        

def star1(file):
    N = 0
    for line in file:
        values = line.strip('\n').split(' ')
        l = [int(s) for s in values]
        if checkRules(l):
            N += 1
    return N

def star2(file):
    return file

def __main__():
    day2input = open("/repo/AdventOfCode/2024/inputs/day02.txt", 'r')
    ans1 = star1(day2input)
    ans2 = star2(day2input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)

__main__()