"""
Day 05

https://adventofcode.com/2025/day/5
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day05.example") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    f[0] = [v.split('-') for v in f[0].split('\n')]
    f[1] = [int(v) for v in f[1].split('\n')]
    return f


def star1(input):
    fresh = 0
    for id in input[1]:
        for rule in input[0]:
            if int(rule[0])<=id and id<=int(rule[1]):
                fresh+=1
                break
    return fresh


def star2(input):
    new_rules = []
    for i in input[0]:
        for ri, rule in enumerate(new_rules):
            if int(rule[0])<=int(i[0]) and int(i[0])<=int(rule[1]):
                if int(rule[1])<int(i[1]):
                    new_rules[ri][1] = i[1] 
                break
            if int(rule[0])<=int(i[1]) and int(i[1])<=int(rule[1]):
                if int(i[0])<int(rule[0]):
                    new_rules[ri][0] = i[0]
                break
            if int(rule[0])>int(i[0]) and int(i[1])>int(rule[1]):
                new_rules[ri] = i
        else:
            new_rules.append(i)
    ans = 0
    for a,b in new_rules:
        ans += int(b)-int(a)
    print(new_rules)
    return ans


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
