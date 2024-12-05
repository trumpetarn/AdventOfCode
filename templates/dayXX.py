"""
Day XX
"""

from typing import List, Tuple, Dict, Set, Optional


def parse_input(file_path: str = "inputs/dayXX.txt") -> List[str]:
    f = open(file_path, "r")
    return [line.strip().split("\n") for line in f]


def star1(input):
    return input


def star2(input):
    return input


def main():
    input = parse_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
