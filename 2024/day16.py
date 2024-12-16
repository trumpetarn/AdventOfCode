"""
Day 16

https://adventofcode.com/2024/day/16
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from enum import Enum

import heapq


def read_input(file_path: str = "./inputs/day16.example") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    maze = []
    start = (-1, -1)
    end = (-1, -1)
    for i, line in enumerate(f):
        row = []
        for j, c in enumerate(line):
            if c == "S":
                start = (j, i)
                row.append(".")
            elif c == "E":
                end = (j, i)
                row.append(c)
            else:
                row.append(c)
        maze.append(row)
    return maze, start, end


DIR = [(1, 0), (0, 1), (-1, 0), (0, -1)]


def get_adjacent(pos, dir):
    x, y = pos
    adj = []
    if dir == (1, 0) or dir == (-1, 0):
        adj.append(((x + dir[0], y), 1, dir))
        adj.append(((x, y - 1), 1001, (0, -1)))
        adj.append(((x, y + 1), 1001, (0, 1)))
    else:
        adj.append(((x + 1, y), 1001, (1, 0)))
        adj.append(((x - 1, y), 1001, (-1, 0)))
        adj.append(((x, y + dir[1]), 1, dir))

    return adj


def dijkstra(maze, start):
    scores = {}
    paths = {}
    for y, row in enumerate(maze):
        for x, _ in enumerate(row):
            scores[(x, y)] = float("inf")
            paths[(x, y)] = []
    scores[start] = 0
    paths[start] = [start]
    current_dir = (1, 0)
    queue = [(0, start, current_dir)]
    while queue:
        current_score, current_pos, current_dir = heapq.heappop(queue)
        if current_score > scores[current_pos]:
            continue

        for adjacent, weight, new_dir in get_adjacent(current_pos, current_dir):
            x, y = adjacent
            score = current_score + weight
            if maze[y][x] != "#":
                if score <= scores.get(adjacent, float("inf")):
                    scores[adjacent] = score
                paths[adjacent] = paths[current_pos] + [adjacent]
                heapq.heappush(queue, (score, adjacent, new_dir))
    return scores


def main():
    maze, start, end = read_input()
    scores = dijkstra(maze, start)
    print("Star 1:", scores[end])
    print("Star 2:")
    print(len([k for k in scores if scores[k] < scores[end]]))


if __name__ == "__main__":
    main()
