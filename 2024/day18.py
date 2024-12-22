"""
Day 18

https://adventofcode.com/2024/day/18
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import re
from collections import defaultdict
import heapq

WIDTH = 71
HEIGHT = 71
START = (0,0)
GOAL = (WIDTH - 1, HEIGHT - 1)
BYTES = 1024
def read_input(file_path: str = "./inputs/day18.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    l =[re.findall(r'\d+', x) for x in f]
    return [(int(x), int(y)) for x, y in l]


def dijkstra(start, end, obstacles):
    heap = []
    heapq.heappush(heap, (0, start))
    visited = set()
    while heap:
        cost, pos = heapq.heappop(heap)
        if pos == end:
            return cost
        if pos in visited:
            continue
        visited.add(pos)
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            x, y = pos
            x += dx
            y += dy
            if 0 <= x < WIDTH and 0 <= y < HEIGHT and (x,y) not in obstacles:
                heapq.heappush(heap, (cost + 1, (x, y)))

def star1(input):
    return dijkstra(START, GOAL, input[:BYTES])


def star2(input):
    MAX = len(input)
    MIN = BYTES
    i = MIN
    # Divide and conquer to find when the path becomes blocked
    while MIN+1 < MAX:
        res = dijkstra(START, GOAL, input[:i])
        if res is None:
            MAX = i
        else:
            MIN = i
        i = (MAX + MIN) // 2
    return input[i]


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
