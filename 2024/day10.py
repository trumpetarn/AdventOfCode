"""
Day 10
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import itertools


def read_input(file_path: str = "inputs/day10.txt") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def parse_input(input):
    m = []
    for line in input:
        l = []
        for v in line:
            l.append(int(v))
        m.append(l)
    return m


def get_next_diag(top_map, x, y):
    R = len(top_map)
    C = len(top_map[0])
    xx = list(range(max(0, x - 1), min(x + 2, C)))
    yy = list(range(max(0, y - 1), min(y + 2, R)))
    return list(itertools.product(xx, yy))


def get_next(top_map, x, y, N):
    R = len(top_map)
    C = len(top_map[0])
    next = [
        (max(0, x - 1), y),
        (min(C - 1, x + 1), y),
        (x, max(0, y - 1)),
        (x, min(R - 1, y + 1)),
    ]
    return [p for p in next if p != (x, y) and top_map[p[0]][p[1]] == N]


def compute_score(top_map, start_x, start_y):
    current_pos = [(start_x, start_y)]
    for i in range(1, 10):
        next_pos = []
        for x, y in current_pos:
            next_pos += get_next(top_map, x, y, i)
        current_pos = next_pos
        if len(current_pos) == 0:
            break

    return len(set(current_pos))


def compute_score2(top_map, start_x, start_y):
    current_pos = [(start_x, start_y)]
    for i in range(1, 10):
        next_pos = []
        for x, y in current_pos:
            next_pos += get_next(top_map, x, y, i)
        current_pos = next_pos
        if len(current_pos) == 0:
            break

    return len((current_pos))


def star1(top_map):
    score = 0
    for i, line in enumerate(top_map):
        for j, p in enumerate(line):
            if p == 0:
                score += compute_score(top_map, i, j)
    return score


def star2(top_map):
    score = 0
    for i, line in enumerate(top_map):
        for j, p in enumerate(line):
            if p == 0:
                score += compute_score2(top_map, i, j)
    return score


def main():
    input = read_input()
    top_map = parse_input(input)
    ans1 = star1(top_map)
    ans2 = star2(top_map)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
