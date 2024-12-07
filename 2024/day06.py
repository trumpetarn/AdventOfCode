"""
Day 06
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import copy

UP = "^"
DOWN = "v"
LEFT = "<"
RIGHT = ">"
DIR = [UP, DOWN, LEFT, RIGHT]
OBSTRUCTION = "#"


def read_input(file_path: str = "inputs/day06.txt") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return [list(line) for line in f]


def find_guard(input):
    for i, line in enumerate(input):
        for j, c in enumerate(line):
            if c in DIR:
                return (i, j)


def get_next(dir: str, pos: Tuple) -> Tuple:
    if dir == UP:
        return (pos[0] - 1, pos[1])
    elif dir == DOWN:
        return (pos[0] + 1, pos[1])
    elif dir == LEFT:
        return (pos[0], pos[1] - 1)
    elif dir == RIGHT:
        return (pos[0], pos[1] + 1)
    else:
        print("get_next(): ERROR, this should not happen", dir)
    return (-1, -1)


def turn(dir):
    if dir == UP:
        return RIGHT
    elif dir == DOWN:
        return LEFT
    elif dir == LEFT:
        return UP
    elif dir == RIGHT:
        return DOWN
    else:
        print("turn(): ERROR, this should not happen")
    return "Q"


def is_inside(pos, R, C):
    return (pos[0] >= 0 and pos[0] < R) and (pos[1] >= 0 and pos[1] < C)


def move(dir, pos, input):
    next = get_next(dir, pos)
    if input[next[0]][next[1]] == ".":
        pos = next
        return next, dir
    elif input[next[0]][next[1]] == OBSTRUCTION:
        return pos, turn(dir)
    else:
        pos = next
    return pos, dir


def fancy_print(input):
    for line in input:
        print("".join(line))


def star1(input):
    pos = find_guard(input)
    ROWS = len(input)
    COLS = len(input[0])
    visited = set()
    visited.add((pos))
    dir = UP
    while is_inside(get_next(dir, pos), ROWS, COLS):
        next, dir = move(dir, pos, input)
        pos = next
        visited.add(pos)

    return visited


def can_loop(input, pos, dir):
    orig_pos = pos
    ROWS = len(input)
    COLS = len(input[0])
    input[pos[0]][pos[1]] = OBSTRUCTION

    pos = find_guard(input)
    visited = set()
    visited.add((pos, dir))
    while is_inside(get_next(dir, pos), ROWS, COLS):
        next, dir = move(dir, pos, input)
        if (next, dir) in visited:
            input[orig_pos[0]][orig_pos[1]] = "."
            return True
        pos = next
        visited.add((pos, dir))
    input[orig_pos[0]][orig_pos[1]] = "."
    return False


def star2(input, visited):
    start_pos = find_guard(input)
    pos = start_pos
    dir = UP
    loop = 0
    for pos in visited:
        if pos == start_pos:
            continue
        if can_loop(input, pos, dir):
            loop += 1

    return loop


def main():
    input = read_input()
    input2 = read_input()
    ans1 = star1(input)
    ans2 = star2(input2, ans1)
    print("Star 1:", len(ans1))
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
