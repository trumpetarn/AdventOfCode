"""
Day 01

https://adventofcode.com/2025/day/1
"""

from typing import List
from pathlib import Path


def read_input(file_path: str = "./inputs/day01.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def star1(input):
    POS = 50
    pwd = 0
    for line in input:
        N = int(line[1:])
        if line[0] == 'R':
            POS += N
        elif line[0] == 'L':
            POS -= N
        POS %=  100
        if POS == 0:
            pwd+=1
    return pwd


def star2(input):
    POS = 50
    pwd = 0
    for line in input:
        N = int(line[1:])
        if line[0] == 'R':
            POS += N
            if POS >= 100:
                pwd += POS//100
        elif line[0] == 'L':
            if POS==0:
                POS=100 # Special handling since we stopped at 0
            POS -= N
            if POS <= 0:
                pwd += 1+abs(POS)//100
        POS %=  100
        print(POS, pwd)
    return pwd


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
