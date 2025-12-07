"""
Day 05

https://adventofcode.com/2025/day/5
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day05.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    f[0] = [v.split('-') for v in f[0].split('\n')]
    f[0] = [(int(a),int(b)) for a,b in f[0]]
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
    sort_rules = sorted(input[0])
    new_rules = []
    for ixx in sort_rules:
        flag = True
        while flag:
            print("a")
            flag = False
            for ri, new_rule in enumerate(new_rules):
                if int(new_rule[0])>int(ixx[0]) and int(ixx[1])>int(new_rule[1]):
                    new_rules[ri] = ixx
                    flag = True
                    break
                if int(new_rule[0])<=int(ixx[0]) and int(ixx[0])<=int(new_rule[1]):
                    if int(new_rule[1])<int(ixx[1]):
                        new_rules[ri] = (new_rule[0], ixx[1]) 
                        flag = True
                    break
                if int(new_rule[0])<=int(ixx[1]) and int(ixx[1])<=int(new_rule[1]):
                    if int(ixx[0])<int(new_rule[0]):
                        new_rules[ri] = (ixx[0], new_rule[1])
                        flag = True
                    break
            else:
                new_rules.append(ixx)
            # print(ixx, new_rules)
    ans = 0
    for a,b in new_rules:
        ans += int(b)-int(a)+1
    # print(new_rules)
    return ans


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
