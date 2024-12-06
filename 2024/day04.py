"""
Day 04
"""

from typing import List, Tuple, Dict, Set, Optional


def parse_input(file_path: str = "inputs/day04.txt") -> List[str]:
    f = open(file_path, "r")
    return [list(line.strip()) for line in f]


def star1(input):
    res = 0
    ROWS = len(input)
    COLS = len(input[0])
    for n, line in enumerate(input):
        for i, c in enumerate(line):
            if c == "X":
                if list(input[n][i : i + 4]) == ["X", "M", "A", "S"]:
                    res += 1
                if list(reversed(input[n][i - 3 : i + 1])) == ["X", "M", "A", "S"]:
                    res += 1
                if list([v[i] for v in input][n : n + 4]) == ["X", "M", "A", "S"]:
                    res += 1
                if list(reversed([v[i] for v in input][n - 3 : n + 1])) == [
                    "X",
                    "M",
                    "A",
                    "S",
                ]:
                    res += 1
                if n >= 3 and i >= 3:
                    if [
                        c,
                        input[n - 1][i - 1],
                        input[n - 2][i - 2],
                        input[n - 3][i - 3],
                    ] == ["X", "M", "A", "S"]:
                        res += 1
                if n >= 3 and i < COLS - 3:
                    if [
                        c,
                        input[n - 1][i + 1],
                        input[n - 2][i + 2],
                        input[n - 3][i + 3],
                    ] == ["X", "M", "A", "S"]:
                        res += 1
                if n < ROWS - 3 and i >= 3:
                    if [
                        c,
                        input[n + 1][i - 1],
                        input[n + 2][i - 2],
                        input[n + 3][i - 3],
                    ] == ["X", "M", "A", "S"]:
                        res += 1
                if n < ROWS - 3 and i < COLS - 3:
                    if [
                        c,
                        input[n + 1][i + 1],
                        input[n + 2][i + 2],
                        input[n + 3][i + 3],
                    ] == ["X", "M", "A", "S"]:
                        res += 1

    return res


def star2(input):
    res = 0
    ROWS = len(input)
    COLS = len(input[0])
    for n, line in enumerate(input):
        if n == 0 or n == ROWS - 1:
            continue
        for i, c in enumerate(line):
            if i == 0 or i == COLS - 1:
                continue
            if c == "A":
                x1 = str(input[n - 1][i - 1] + c + input[n + 1][i + 1])
                x2 = str(input[n + 1][i - 1] + c + input[n - 1][i + 1])
                if (x1 == "SAM" or x1 == "MAS") and (x2 == "SAM" or x2 == "MAS"):
                    res += 1
    return res


def main():
    input = parse_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
