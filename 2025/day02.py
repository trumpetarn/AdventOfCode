"""
Day 02

https://adventofcode.com/2025/day/2
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import textwrap


def read_input(file_path: str = "./inputs/day02.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def star1(input):
    ans = 0
    for pair in input[0].split(','):
        p1,p2 = pair.split('-')
        i = int(p1)
        while i <= int(p2):
            s = str(i)
            a,b = s[:len(s)//2], s[len(s)//2:]
            if a == b:
                #print(p1, p2, s)
                ans += int(s)
            i+=1
    return ans

def isInvalid(i):
    s = str(i)
    if len(set(s)) > len(s)//2:
        return False
    for n in range(len(s)//2):
        parts = textwrap.wrap(s,n+1)
        if len(set(parts))==1:
            return True

    return False

def star2(input):
    ans = 0
    for pair in input[0].split(','):
        p1,p2 = pair.split('-')
        i = int(p1)
        while i <= int(p2):
            if isInvalid(i):
                ans += int(i)
            i+=1
    return ans
    return 0


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
