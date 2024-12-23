"""
Day 13
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import itertools
from collections import deque
from collections import defaultdict
import re
import math
import numpy as np


def read_input(file_path: str = "inputs/day13.txt") -> List[List[int]]:
    f = Path(file_path).read_text().strip()
    A_buttons = re.findall("Button A: X\+(\d*), Y\+(\d*)", f)
    B_buttons = re.findall("Button B: X\+(\d*), Y\+(\d*)", f)
    Prizes = re.findall("Prize: X=(\d*), Y=(\d*)", f)
    l = []
    for i in range(len(A_buttons)):
        a = (int(A_buttons[i][0]), int(A_buttons[i][1]))
        b = (int(B_buttons[i][0]), int(B_buttons[i][1]))
        p = (int(Prizes[i][0]), int(Prizes[i][1]))
        l += [(a, b, p)]
    return l


def solver(input, error=0):
    tokens = 0
    for v in input:
        a, b, p = v
        p1, p2 = (p[0] + error, p[1] + error)
        x1, y1 = a
        x2, y2 = b
        """ 
          M = np.array([[a[0], b[0]], [a[1], b[1]]])
          p = np.array([sum[0] + error, sum[1] + error])
          n, m = np.linalg.solve(M, p)
          Works in theory but floating point math fails us in part 2
          ...
          So real math is needed...
          ...
          By some linear algebra we get 
        """
        m = (p2 * x1 - p1 * y1) / (x1 * y2 - x2 * y1)
        n = (p1 - m * x2) / x1

        if int(m) == m and int(n) == n:
            tokens += 3 * int(n) + int(m)
    return tokens


def main():
    input = read_input()
    print("Star 1:", solver(input))
    print("Star 2:", solver(input, 10000000000000))


if __name__ == "__main__":
    main()
