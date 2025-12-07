"""
Day 03

https://adventofcode.com/2025/day/3
"""

from typing import List
from pathlib import Path


def read_input(file_path: str = "./inputs/day03.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def star1(input):
    ans = []
    for line in input:
        large = 0
        pos = 0
        for i, v in enumerate(line[:-1]):
            if int(v) > large:
                pos = i
                large = int(v)
        large2 = 0
        for v in line[pos+1:]:
            if int(v) > large2:
                large2 = int(v)
        ans.append(large*10 + large2)
    return sum(ans)


def star2(input):
    ans = []
    N=12
    for line in input:
        format_line = [int(v) for v in line ]
        idx=0
        val = 0
        for i in range(N):
            window=format_line[idx:len(format_line)-N+i+1]
            if len(window) == 1:
                val = int(str(val)+line[idx:])
                break
            m = max(window)
            idx = format_line.index(m,idx)+1
            val = 10*val + m
        ans.append(val)
        
    return sum(ans)


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
