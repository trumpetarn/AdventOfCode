"""
Day 25

https://adventofcode.com/2024/day/25
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day25.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    return f


def star1(input):
    keys = []
    locks = []
    for schema in input:
        key, lock = [], []
        # Transpose the schema to get the columns
        for l in list(map(list, zip(*schema.split("\n")))):
            if schema[0] == "#":
                key.append(l.count("#") - 1)
            else:
                lock.append(l.count("#") - 1)
        if len(key) > 0:
            keys.append(key)
        else:
            locks.append(lock)
    no_overlap = 0
    for k in keys:
        for l in locks:
            for i in range(len(k)):
                if k[i] + l[i] > 5:
                    break
            else:
                no_overlap += 1
    return no_overlap


def star2():
    return "We're done! We found the Chief Historian 🌟"


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2()
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
