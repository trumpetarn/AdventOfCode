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
    ints = [int(v) for v in input]
    data = []
    free = []
    pos = 0
    id = 0
    for i, length in enumerate(ints):
        if i % 2 == 0:
            data.append((pos, length, id))
            id += 1
        else:
            free.append((pos, length))
        pos += length
    for i, (data_pos, data_len, id) in reversed(list(enumerate(data))):
        for j, (free_pos, free_len) in enumerate(free):
            if free_pos < data_pos and free_len >= data_len:
                data[i] = (free_pos, data_len, id)
                free[j] = (
                    free_pos + data_len,
                    free_len - data_len,
                )
                break
    checksum = 0
    for i, (pos, length, id) in enumerate(data):
        checksum += sum([v * id for v in range(pos, pos + length)])
    return checksum


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
