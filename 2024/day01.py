
"""
Day 01: https://adventofcode.com/2024/day/1
"""

def star(file):
    r,l = [],[]
    for line in file:
        ll = line.strip('\n')
        vals = ll.split(" ")
        r.append(int(vals[0]))
        l.append(int(vals[-1]))
    r.sort()
    l.sort()
    td = ss = 0
    for i, v in enumerate(r):
        dist = r[i]-l[i]
        td += abs(dist)
        ss += v*l.count(v)
    return td, ss

def __main__():
    day1input = open("/repo/AdventOfCode/2024/inputs/day01.txt", 'r')
    ans1, ans2 = star(day1input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)

__main__()