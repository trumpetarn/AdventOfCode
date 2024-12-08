"""
Day 08
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "inputs/day08.txt") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def parse_input(input):
    antennas = {}
    for i, line in enumerate(input):
        for j, c in enumerate(line):
            if c != ".":
                if c in antennas:
                    antennas[c] = antennas[c] + [(i, j)]
                else:
                    antennas[c] = [(i, j)]
    return antennas, i + 1, j + 1


def find_antinodes(antennas, R, C):
    antinodes = []
    for n in antennas:
        for m in antennas:
            if n == m:
                continue
            x = n[0] + n[0] - m[0]
            y = n[1] + n[1] - m[1]
            if (x >= 0 and x < R) and (y >= 0 and y < C):
                antinodes.append((x, y))
    return antinodes


def find_resonant_antinodes(antennas, R, C):
    antinodes = []
    for n in antennas:
        for m in antennas:
            if n == m:
                continue
            x = n[0] + n[0] - m[0]
            y = n[1] + n[1] - m[1]
            while (x >= 0 and x < R) and (y >= 0 and y < C):
                antinodes.append((x, y))
                x = x + n[0] - m[0]
                y = y + n[1] - m[1]
            if len(antinodes) > 0:
                antinodes.append(n)
                antinodes.append(m)
    return antinodes


def fancy_print(antennas, antinodes, R, C):
    for i in range(R):
        row = ""
        for j in range(C):
            is_antenna = False
            for key in antennas:
                if (i, j) in antennas[key]:
                    row += key
                    is_antenna = True
                    break
            if not is_antenna:
                if (i, j) in antinodes:
                    row += "#"
                else:
                    row += "."
        print(row)


def star1(antennas, R, C):
    antinodes = set()
    all_antennas = set()
    for key in antennas:
        all_antennas.update(antennas[key])
        antinodes.update(find_antinodes(antennas[key], R, C))
    fancy_print(antennas, antinodes, R, C)
    return len(antinodes)


def star2(antennas, R, C):
    antinodes = set()
    all_antennas = set()
    for key in antennas:
        all_antennas.update(antennas[key])
        antinodes.update(find_resonant_antinodes(antennas[key], R, C))
    fancy_print(antennas, antinodes, R, C)
    return len(antinodes)


def main():
    input = read_input()
    antennas, ROWS, COLS = parse_input(input)
    ans1 = star1(antennas, ROWS, COLS)
    ans2 = star2(antennas, ROWS, COLS)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
