"""
Day 16

https://adventofcode.com/2024/day/16
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from enum import Enum
from collections import defaultdict

import heapq


def read_input(file_path: str = "./inputs/day16.in") -> List[str]:
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


def dijkstra(maze, start, end):
    scores = defaultdict(lambda: float("inf"))
    current_dir = (1, 0)
    previous = defaultdict(list)

    scores[start] = 0
    queue = [(0, start, current_dir)]
    min_end_score = float("inf")
    optimal_end_states = set()

    while queue:
        current_score, current_pos, current_dir = heapq.heappop(queue)
        current_state = (current_pos, current_dir)
        if current_score > min_end_score:
            continue

        if current_pos == end:
            if current_score < min_end_score:
                min_end_score = current_score
                optimal_end_states = {current_state}
            elif current_score == min_end_score:
                optimal_end_states.add(current_state)
            continue

        for (x, y), weight, new_dir in get_adjacent(current_pos, current_dir):
            if maze[y][x] == "#":
                continue
            new_state = ((x, y), new_dir)
            new_score = current_score + weight
            if new_score <= scores[new_state]:
                if new_score < scores[new_state]:
                    scores[new_state] = new_score
                    previous[new_state] = [current_state]
                    if new_score < min_end_score:
                        heapq.heappush(queue, (new_score, (x, y), new_dir))
                else:
                    previous[new_state].append(current_state)
    # Collect all tiles that are part of optimal paths
    optimal_tiles = set()
    states_to_process = set(optimal_end_states)
    processed = set()

    while states_to_process:
        pos, dir = states_to_process.pop()
        if (pos, dir) in processed:
            continue

        processed.add((pos, dir))
        optimal_tiles.add((pos))  # Add current position

        # Add all previous states that led to this one with optimal score
        for prev_state in previous[(pos, dir)]:
            if prev_state[0] not in processed:
                states_to_process.add(prev_state)
    return optimal_tiles, min_end_score


def main():
    maze, start, end = read_input()
    optimal, min_score = dijkstra(maze, start, end)
    print("Star 1:", min_score)
    print("Star 2:", len(optimal))


if __name__ == "__main__":
    main()
