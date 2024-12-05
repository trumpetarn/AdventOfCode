"""
Day 03
"""
from typing import List, Tuple, Dict, Set, Optional
import re
from pathlib import Path

def read_input(file_path: str = "inputs/day03.txt") -> str:
	ff = Path(file_path).read_text().strip()
	return ff

def star1(input: str) -> str:
	multis = re.findall("mul\((\d+),(\d+)\)", input)
	ans = 0
	for tuple in multis:
		ans += int(tuple[0]) * int(tuple[1])
	return ans

def star2(input):
    multis = re.findall("mul\((\d+),(\d+)\)|(do\(\))|(don't\(\))", input)
    ans = 0
    do = True
    for tuple in multis:
        if tuple[2] != "":
            do = True
        elif tuple[3] != "":
            do = False
        elif do:
            ans += int(tuple[0]) * int(tuple[1])
    return ans

def main():
	input = read_input()
	ans1 = star1(input)
	ans2 = star2(input)
	print("Star 1:", ans1)
	print("Star 2:", ans2)


if __name__ == "__main__":
	main()