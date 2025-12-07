"""
Day 06

https://adventofcode.com/2025/day/6
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import math


def read_input(file_path: str = "./inputs/day06.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    nums = []
    for v in f[:-1]:
        y = [x for x in filter(None, v.split(' '))]
        nums.append(y)
    operands = list(filter(None, f[-1].split(' ')))
    return nums, operands

def read_input2(file_path: str = "./inputs/day06.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    nums = []
    l = []
    for v in f[:-1]:
        y = [v]
        l.append(len(v))
        nums.append(y)
    operands = f[-1]
    return nums, operands


def star1(input):
    ans = 0
    for i,op in enumerate(input[1]):
        vals = [int(x[i]) for x in input[0]]
        if op == '*':
            ans += math.prod(vals)
        elif op == '+':
            ans += sum(vals)

    return ans


def star2(input):
    ans = 0
    vals = []
    oper = ''
    padding = len(input[0][0][0])-len(input[1])
    for i,op in enumerate(input[1]+padding*' '):
        s = ""
        for line in input[0]:
            if line[0][i] != ' ':
                s+=line[0][i]
        if op != ' ':
            oper = op
        if len(s) == 0:
            if oper == '*':
                ans += math.prod(vals)
            if oper == '+':
                ans += sum(vals)
            vals = []
        else:
            vals.append(int(s))
    
    print(vals, oper, i)
    if oper == '*':
        ans += math.prod(vals)
    if oper == '+':
        ans += sum(vals)

    return ans


def main():
    input = read_input()
    input2 = read_input2()
    ans1 = star1(input)
    ans2 = star2(input2)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
