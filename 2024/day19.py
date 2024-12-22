"""
Day 19

https://adventofcode.com/2024/day/19
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day19.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    return f

def is_possible(patterns, design):
    s = []
    ps = patterns.split(", ")
    matched = 0
    bad = set()
    current = ""
    while current != design:
        for p in ps:
            if p == design[matched:matched+len(p)] and (current + p) not in bad:
                matched += len(p)
                #ps = ps[:i] + ps[i+1:]
                s.append(p)
                break
        else:
            if len(s) > 0:
                bad.add(current)
                a = s.pop()
                matched -= len(a)
            else:
                return False
        current = "".join(s)
    return "".join(s) == design

def star1(patterns, designs):
    n = 0
    for d in designs.split("\n"):
        if is_possible(patterns, d):
            n += 1
    return n


def star2(input):
    return 0


def main():
    patterns, designs = read_input()
    ans1 = star1(patterns, designs)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
