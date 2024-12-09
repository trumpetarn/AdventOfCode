"""
Day 09
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "inputs/day09.txt") -> List[str]:
    f = Path(file_path).read_text().strip()
    return f


def read_inputx() -> List[str]:
    return "2333133121414131402"


def read_inputy() -> List[str]:
    return "12345"


def star1(input):
    data = []
    id = 0

    for i, c in enumerate(input):
        if i % 2 == 0:
            data += [id] * int(c)
            id += 1
        else:
            data += [-1] * int(c)

    checksum = 0
    pos = -1
    while len(data) > 0:
        pos += 1
        n = data.pop(0)
        if n >= 0:
            checksum += n * pos
        else:
            m = -1
            while len(data) > 0 and m < 0:
                m = data.pop()
            checksum += m * pos
    return checksum


def star2(input):
    data = {}
    id = 0
    free = {}
    pos = 0
    for i, c in enumerate(input):
        N = int(c)
        if i % 2 == 0:
            data[id] = N
            id += 1
            pos += N
        else:
            free[pos] = N
            pos += N
    print(free)
    return data


def main():
    input = read_inputx()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
