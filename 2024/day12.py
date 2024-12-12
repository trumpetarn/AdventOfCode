"""
Day 10
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import itertools
from collections import deque
from collections import defaultdict


def read_input(file_path: str = "inputs/day12.txt") -> List[List[int]]:
    f = Path(file_path).read_text().strip().split("\n")
    return [[v for v in line] for line in f]


def get_neighbors(p):
    (px, py) = p
    return [(px + 1, py), (px - 1, py), (px, py + 1), (px, py - 1)]


# Thanks to claude for finding regions
def bfs(start, visited, point_set):
    component = []
    queue = deque([start])

    while queue:
        point = queue.popleft()
        if point in visited:
            continue

        visited.add(point)
        component.append(point)

        # Add unvisited neighbors to queue
        for neighbor in get_neighbors(point):
            if neighbor in point_set and neighbor not in visited:
                queue.append(neighbor)

    return component


def get_regions(points):
    regions = []
    visited = set()
    point_set = set(points)

    for point in points:
        if point not in visited:
            region = bfs(point, visited, point_set)
            regions.append(region)
    return regions


def get_sides(region):
    x = {}
    y = {}
    # Use half to avoid collision between to sides having a shared "middle"
    for p1, p2 in region:
        if (p1 - 1, p2) not in region:
            x[p1 - 0.1] = x.get(p1 - 0.1, []) + [p2]
        if (p1 + 1, p2) not in region:
            x[p1 + 0.1] = x.get(p1 + 0.1, []) + [p2]

        if (p1, p2 - 1) not in region:
            y[p2 - 0.1] = y.get(p2 - 0.1, []) + [p1]
        if (p1, p2 + 1) not in region:
            y[p2 + 0.1] = y.get(p2 + 0.1, []) + [p1]
    sides = 0

    for k in x:
        l = x[k]
        if len(l) > 0:
            l.sort()
        prev = l[0]
        tail = l[1:]
        split = 0
        for v in tail:
            if v - 1 != prev:
                split += 1
            prev = v
        sides += 1 + split
    for k in y:
        l = y[k]
        if len(l) > 0:
            l.sort()
        prev = l[0]
        tail = l[1:]
        split = 0
        for v in tail:
            if v - 1 != prev:
                split += 1
            prev = v
        sides += 1 + split

    return sides


def get_perimiter(region):
    perimiter = 0
    for p in region:
        ne = get_neighbors(p)
        for n in ne:
            perimiter += int(not n in region)
    return perimiter


def main():
    input = read_input()
    data = {}

    for i, row in enumerate(input):
        for j, v in enumerate(row):
            data[v] = data.get(v, []) + [(i, j)]

    total_cost = 0
    total_cost2 = 0

    for k in data:
        ks = data[k]
        regions = get_regions(ks)
        cost = 0
        cost2 = 0
        for region in regions:
            area = len(region)
            perimiter = get_perimiter(region)
            sides = get_sides(region)
            cost += area * perimiter
            cost2 += area * sides
        total_cost += cost
        total_cost2 += cost2
    print("Star 1:", total_cost)
    print("Star 2:", total_cost2)


if __name__ == "__main__":
    main()
