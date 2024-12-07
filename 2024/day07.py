"""
Day 07
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from tqdm import tqdm


def read_input(file_path: str = "inputs/day07.txt") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def star1(input):
    ans = 0
    for line in input:
        nums = [int(v.strip(":")) for v in line.split(" ")]
        result = nums[0]
        terms = nums[1:]
        results = [terms[0]]
        for y in terms[1:]:
            new = []
            for x in results:
                new = new + [x + y, x * y]
            results = new
        if result in results:
            ans += result

    return ans


def star2(input):
    ans = 0
    for line in tqdm(input):
        nums = [int(v.strip(":")) for v in line.split(" ")]
        result = nums[0]
        terms = nums[1:]
        results = [terms[0]]
        for y in terms[1:]:
            new = []
            for x in results:
                new = new + [x + y, x * y, int(str(x) + str(y))]
            results = [z for z in new if z <= result]
        if result in results:
            ans += result

    return ans


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
