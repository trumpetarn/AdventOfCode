"""
Day 21

https://adventofcode.com/2024/day/21
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from tqdm import tqdm

"""
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+

"""
NPAD = [["7", "8", "9"], ["4", "5", "6"], ["1", "2", "3"], ["", "0", "A"]]
"""
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
"""
moves = {
    ("<", "<"): "A",
    ("<", ">"): ">>A",
    ("<", "^"): ">^A",
    ("<", "v"): ">A",
    ("<", "A"): ">>^A",
    (">", "<"): "<<A",
    (">", ">"): "A",
    (">", "^"): "<^A",
    (">", "v"): "<A",
    (">", "A"): "^A",
    ("^", "<"): "v<A",
    ("^", ">"): "v>A",
    ("^", "^"): "A",
    ("^", "v"): "vA",
    ("^", "A"): ">A",
    ("v", "<"): "<A",
    ("v", ">"): ">A",
    ("v", "^"): "^A",
    ("v", "v"): "A",
    ("v", "A"): "^>A",
    ("A", "<"): "v<<A",
    ("A", ">"): "vA",
    ("A", "^"): "<A",
    ("A", "v"): "<vA",
    ("A", "A"): "A",
}

cache = {}


def npad_to_arrow(p1, p2) -> str:
    if p1 == p2:
        return "A"
    for i, row in enumerate(NPAD):
        if p1 in row:
            r1 = (i, row.index(p1))
        if p2 in row:
            r2 = (i, row.index(p2))
    s = ""
    # Always move up first to avoid pointing towards "void"
    if max(r1[0], r2[0]) == 3 and min(r1[1], r2[1]) == 0:
        if r1[0] > r2[0]:
            s += "^" * abs(r1[0] - r2[0])
        if r1[1] < r2[1]:
            s += ">" * abs(r1[1] - r2[1])
        if r1[1] > r2[1]:
            s += "<" * abs(r1[1] - r2[1])
        if r1[0] < r2[0]:
            s += "v" * abs(r1[0] - r2[0])
    else:  # If no risk of pointing towards void, end as close to 'A' as possible
        if r1[1] > r2[1]:
            s += "<" * abs(r1[1] - r2[1])
        if r1[0] < r2[0]:
            s += "v" * abs(r1[0] - r2[0])
        if r1[0] > r2[0]:
            s += "^" * abs(r1[0] - r2[0])
        if (
            r1[1] < r2[1]
        ):  # End on right over up since more other arrows are on the bottom row
            s += ">" * abs(r1[1] - r2[1])

    return s + "A"


def foo(p1, p2, N) -> int:
    if (p1, p2, N) in cache:
        return cache[(p1, p2, N)]
    if N == 0:
        return 1
    ns = moves[(p1, p2)]
    ret = foo("A", ns[0], N - 1)
    for i, p in enumerate(ns[:-1]):
        ret += foo(p, ns[i + 1], N - 1)
    cache[(p1, p2, N)] = ret
    return ret


def shortest_seq_len(arrows, N) -> int:
    n = foo("A", arrows[0], N)
    for i, p in enumerate(arrows[:-1]):
        n += foo(p, arrows[i + 1], N)
    return n


def read_input(file_path: str = "./inputs/day21.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def stars(input, npad_robots=2):
    ans = 0
    for p in input:
        cmds = npad_to_arrow("A", p[0])
        for i, n in enumerate(p[:-1]):
            cmds += npad_to_arrow(n, p[i + 1])
        cmd2 = moves[("A", cmds[0])]
        for i, pp in enumerate(cmds[:-1]):
            cmd2 += moves[(pp, cmds[i + 1])]
        ans += int(p[:-1]) * shortest_seq_len(cmds, npad_robots)
    return ans


def main():
    input = read_input()
    ans1 = stars(input)
    print("Star 1:", ans1)
    ans2 = stars(input, 25)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
