"""
Day 14
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import re
import math
from PIL import Image
import numpy as np

WIDTH = 101
HEIGHT = 103


def read_input(file_path: str = "inputs/day14.txt") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    input = []
    for line in f:
        a, b, c, d = re.findall("(-?\d+)", line)
        input.append((int(a), int(b), int(c), int(d)))
    return input


def update_positions(robots):
    for i, (px, py, vx, vy) in enumerate(robots):
        x = (px + vx) % WIDTH
        y = (py + vy) % HEIGHT
        robots[i] = (x, y, vx, vy)


def map2image(robots, fname="img.png"):
    img = []
    for y in range(HEIGHT):
        s = []
        for x in range(WIDTH):
            s.append((robots.get((x, y), 0) > 0) * 255)
        img.append(s)
    Image.fromarray(np.array(img, dtype=np.uint8)).save(fname)


def get_safety_factor(robots):
    Q1 = 0
    Q2 = 0
    Q3 = 0
    Q4 = 0
    centre_x = math.floor(WIDTH / 2)
    centre_y = math.floor(HEIGHT / 2)
    for k in robots:
        x, y = k
        if x < centre_x and y < centre_y:
            Q1 += robots[k]
        elif x > centre_x and y < centre_y:
            Q2 += robots[k]
        elif x < centre_x and y > centre_y:
            Q3 += robots[k]
        elif x > centre_x and y > centre_y:
            Q4 += robots[k]
    return Q1 * Q2 * Q3 * Q4


def solve(input, seconds=100, make_image=False, iname_offset=0):
    for i in range(1, seconds + 1):
        update_positions(input)
        if make_image:
            robots = {}
            for px, py, _, _ in input:
                robots[(px, py)] = robots.get((px, py), 0) + 1
            map2image(robots, "images/" + str(i + iname_offset) + "_sec.png")
    if not (make_image):
        robots = {}
        for px, py, _, _ in input:
            robots[(px, py)] = robots.get((px, py), 0) + 1
    return get_safety_factor(robots)


def main():
    input = read_input()
    ans1 = solve(input)
    print("Star 1:", ans1)
    print("Star 2: Look in images and find a christmas tree")
    solve(input, 10000, True, 100)


if __name__ == "__main__":
    main()
