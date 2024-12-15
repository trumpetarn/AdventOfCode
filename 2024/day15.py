"""
Day 15

https://adventofcode.com/2024/day/15
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from collections import deque


def read_input(file_path: str = "./inputs/day15.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    return f


def parse_input(input):
    rows = input[0].split("\n")
    maze = []
    for i, row in enumerate(rows):
        r = []
        for j, c in enumerate(row):
            if c == "@":
                robot = (j, i)
                r.append("@")
            else:
                r.append(c)
        maze.append(r)
    instructions = []
    for c in input[1]:
        if c == "\n":
            pass
        if c == "<":
            instructions.append((-1, 0))
        elif c == "^":
            instructions.append((0, -1))
        elif c == "v":
            instructions.append((0, 1))
        elif c == ">":
            instructions.append((1, 0))
    return maze, instructions, robot


def parse_input2(input):
    rows = input[0].split("\n")
    maze = []

    for i, row in enumerate(rows):
        r = []
        for j, c in enumerate(row):
            if c == "@":
                robot = (j * 2, i)
                r.append("@")
                r.append(".")
            elif c == "O":
                r.append("[")
                r.append("]")
            else:
                r.append(c)
                r.append(c)
        maze.append(r)

    instructions = []
    for c in input[1]:
        if c == "\n":
            pass
        if c == "<":
            instructions.append((-1, 0))
        elif c == "^":
            instructions.append((0, -1))
        elif c == "v":
            instructions.append((0, 1))
        elif c == ">":
            instructions.append((1, 0))

    return maze, instructions, robot


def star1(input):
    maze, ins, robot = parse_input(input)
    pos_x, pos_y = robot
    R = len(maze)
    C = len(maze[0])
    for ix, iy in ins:
        move = False
        new_x = pos_x + ix
        new_y = pos_y + iy
        if maze[new_y][new_x] == ".":
            move = True
        elif maze[new_y][new_x] == "#":
            pass
        else:
            x = new_x
            y = new_y
            while maze[y][x] != "#":
                x += ix
                y += iy
                if maze[y][x] == ".":
                    move = True
                    break

        if move:
            maze[pos_y][pos_x] = "."
            obj = maze[new_y][new_x]
            maze[new_y][new_x] = "@"
            pos_x = new_x
            pos_y = new_y
            x = new_x
            y = new_y
            while obj == "O":
                x += ix
                y += iy
                obj = maze[y][x]
                maze[y][x] = "O"

    sum = 0
    for i, r in enumerate(maze):
        s = ""
        for j, c in enumerate(r):
            s += c
            if c == "O":
                sum += 100 * i + j
        # print(s)

    return sum


def star2(input):
    maze, ins, robot = parse_input2(input)
    pos_x, pos_y = robot

    for ix, iy in ins:
        new_x = pos_x + ix
        new_y = pos_y + iy
        to_move = set()
        to_move.add((pos_x, pos_y, "@"))
        to_check = [(new_x, new_y)]
        move = True
        while len(to_check) > 0:
            x, y = to_check.pop()
            obj = maze[y][x]
            if (x, y, obj) in to_move or obj == ".":
                pass
            elif obj == "[":
                to_move.add((x, y, obj))
                to_check.append((x + ix, y + iy))
                to_check.append((x + 1, y))
            elif obj == "]":
                to_move.add((x, y, obj))
                to_check.append((x + ix, y + iy))
                to_check.append((x - 1, y))
            elif obj == "#":
                move = False
                break
        if move:
            maze[pos_y][pos_x] = "."
            pos_x = new_x
            pos_y = new_y
            for x, y, c in to_move:
                maze[y][x] = "."
            for x, y, c in to_move:
                maze[y + iy][x + ix] = c
            maze[pos_y][pos_x] = "@"

    sum = 0
    for i, r in enumerate(maze):
        s = ""
        for j, c in enumerate(r):
            s += c
            if c == "[":
                sum += 100 * i + j
        # print(s)
    return sum


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
