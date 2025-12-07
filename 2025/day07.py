"""
Day 07

https://adventofcode.com/2025/day/7
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day07.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f

def star(input):
    pos = [(input[0].index("S"),1)]
    width = len(input[0])
    split = 0
    for line in input[1:]:
        new_pos = []
        for p,n in pos:
            if line[p]=="^":
                split += 1
                if p > 0 and line[p-1] != '^':
                    new_pos.append((p-1,n))
                if p < width and line[p+1] != '^':
                    new_pos.append((p+1,n))
            elif line[p]=='.':
                new_pos.append((p,n))
        pos = []
        for np in new_pos:
            for i,p in enumerate(pos):
                if np[0] == p[0]:
                    pos[i] = (p[0],p[1]+np[1])
                    break
            else:
                pos.append(np)
    ans = 0
    for a,b in pos:
        ans += b
    return split, ans


def main():
    input = read_input()
    ans1, ans2 = star(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
