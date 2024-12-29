"""
Day 20

https://adventofcode.com/2024/day/20
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import heapq
from collections import defaultdict


def read_input(file_path: str = "./inputs/day20.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    maze = []
    for line in f:
        a = []
        for c in line:
            a.append(c)
        maze.append(a)
    return maze


def find_start_end(maze):
    for row in maze:
        if "S" in row:
            start = (maze.index(row), row.index("S"))
        if "E" in row:
            end = (maze.index(row), row.index("E"))
    return start, end


def dijkstra(maze, start, end):
    heap = []
    heapq.heappush(heap, (0, [start], start))
    visited = set()
    while heap:
        cost, path, pos = heapq.heappop(heap)
        if pos == end:
            return cost, path
        if (pos) in visited:
            continue
        visited.add(pos)
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            x, y = pos
            x += dx
            y += dy
            inside = x < len(maze) and y < len(maze[0]) and x >= 0 and y >= 0
            if inside and maze[x][y] != "#" and (x, y) not in visited:
                heapq.heappush(heap, (cost + 1, path + [(x, y)], (x, y)))
    return -1


def cheater(path, max_score, t):
    a = defaultdict(lambda: float("inf"))
    N = len(path) - 1
    for i, (x, y) in enumerate(path):
        a[(x, y)] = N - i
    cheats = set()
    for i, (x, y) in enumerate(path):
        for dx in range(-t, t + 1):
            for dy in range(-t, t + 1):
                psecs = abs(dx) + abs(dy)
                if psecs > t:
                    continue
                x1, y1 = x + dx, y + dy
                if (i + a[(x1, y1)] + psecs) < max_score and (
                    x,
                    y,
                    x1,
                    y1,
                ) not in cheats:
                    cheats.add((x, y, x1, y1))
    return cheats


def main():
    input = read_input()
    start, end = find_start_end(input)
    _, path = dijkstra(input, start, end)
    cheats = cheater(path, len(path) - 100, 2)
    print("Star 1:", len(cheats))
    cheats = cheater(path, len(path) - 100, 20)
    print("Star 2:", len(cheats))


if __name__ == "__main__":
    main()
