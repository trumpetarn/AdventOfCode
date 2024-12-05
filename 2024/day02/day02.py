
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
        

def star1(lists):
    N1_safe = 0
    N2_safe = 0
    for l in lists:
        if checkRules(l):
            N1_safe += 1
        else:
            for i in range(len(l)):
                print(i)
                if checkRules(l[:i] + l[i+1:]):
                    N2_safe += 1
                    break
    return N1_safe, N1_safe+N2_safe

def star2(lists):
    N_safe = 0
    for l in lists:
        if checkRules(l):
            N_safe += 1
        else:
            for i in range(len(l)):
                if checkRules(l[:i] + l[i+1:]):
                    N_safe += 1
                    break
    return N_safe

def main():
    day2input = open("/repo/AdventOfCode/2024/inputs/day02.txt", 'r')
    lists = []
    for line in day2input:
        values = line.strip('\n').split(' ')
        l = [int(s) for s in values]
        lists.append(l)
    ans1, ans2 = star1(lists)
    print("Star 1:", ans1)
    print("Star 2:", ans2)

if __name__ == "__main__":
    main()