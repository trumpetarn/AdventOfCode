"""
Day 10
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import itertools


def read_input(file_path: str = "inputs/day10.txt") -> List[List[int]]:
    f = Path(file_path).read_text().strip().split("\n")
    return [[int(v) for v in line] for line in f]


def get_next(top_map: List[List[int]], x: int, y: int, N: int) -> List[Tuple]:
    R = len(top_map)
    C = len(top_map[0])
    next = [
        (max(0, x - 1), y),
        (min(C - 1, x + 1), y),
        (x, max(0, y - 1)),
        (x, min(R - 1, y + 1)),
    ]
    return [p for p in next if p != (x, y) and top_map[p[0]][p[1]] == N]


def compute_path(top_map: List[List[int]], start_x: int, start_y: int) -> List[Tuple]:
    current_pos = [(start_x, start_y)]
    for i in range(1, 10):
        next_pos = []
        for x, y in current_pos:
            next_pos += get_next(top_map, x, y, i)
        current_pos = next_pos
        if len(current_pos) == 0:
            return []

    return current_pos


def main():
    top_map = read_input()
    score = 0
    rating = 0
    for i, line in enumerate(top_map):
        for j, p in enumerate(line):
            if p == 0:
                p = compute_path(top_map, i, j)
                score += len(set(p))
                rating += len(p)

    print("Star 1:", score)
    print("Star 2:", rating)


if __name__ == "__main__":
    main()
