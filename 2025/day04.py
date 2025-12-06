"""
Day 04

https://adventofcode.com/2025/day/4
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day04.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    m = []
    for line in f:
        m.append([c for c in line])
    return m


def star1(input):
    yl = len(input)
    xl = len(input[0])
    count=0
    for y,line in enumerate(input):
        for x,c in enumerate(line):
            if c == '@':
                x1 = max(x-1,0)
                x2 = min(x+1,xl)
                y1 = max(y-1,0)
                y2 = min(y+1,yl)
                # Remember to skip counting the value where standing on
                neighbours = [c for v in input[y1:y2+1] for c in v[x1:x2+1]].count('@')-1
                if neighbours < 4:
                    count+=1

    return count


def star2(input):
    yl = len(input)
    xl = len(input[0])
    count=1
    full_count = 0
    while count > 0:
        new_map = input
        count = 0
        for y,line in enumerate(input):
            for x,c in enumerate(line):
                if c == '@':
                    x1 = max(x-1,0)
                    x2 = min(x+1,xl)
                    y1 = max(y-1,0)
                    y2 = min(y+1,yl)
                    # Remember to skip counting the value where standing on
                    neighbours = [c for v in input[y1:y2+1] for c in v[x1:x2+1]].count('@')-1
                    if neighbours < 4:
                        new_map[y][x] = '.'
                        count+=1
        input = new_map
        full_count+=count

    return full_count


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
