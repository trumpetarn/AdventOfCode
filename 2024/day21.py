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
NPAD = [['7', '8', '9'],['4', '5', '6'],['1', '2', '3'], ['', '0', 'A']]
"""
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
"""  
ARROW = [['', '^', 'A'],['<', 'v', '>']]
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
    # Always move right first to avoid pointing towards "void"
    if max(r1[0], r2[0]) == 3 and min(r1[1], r2[1]) == 0:
        if r1[0] > r2[0]:
            s += "^"*abs(r1[0]-r2[0])
        if r1[1] < r2[1]:
            s += ">"*abs(r1[1]-r2[1])
        if r1[1] > r2[1]:
            s += "<"*abs(r1[1]-r2[1])
        if r1[0] < r2[0]:
            s += "v"*abs(r1[0]-r2[0])
    else: # If no risk of pointing towards void, end as close to 'A' as possible
        if r1[1] > r2[1]:
            s += "<"*abs(r1[1]-r2[1])
        if r1[0] < r2[0]:
            s += "v"*abs(r1[0]-r2[0])
        if r1[1] < r2[1]:
            s += ">"*abs(r1[1]-r2[1])
        if r1[0] > r2[0]:
            s += "^"*abs(r1[0]-r2[0])
    return s+"A"

def shortest_seq_len(arrows, N) -> int:
    for _ in range(N):
        arrows = "A" + arrows
        s = ""
        for i,p1 in enumerate(arrows[:-1]):
            p2 = arrows[i+1]
            if p1 == p2:
                s += "A"
                continue
            for i, row in enumerate(ARROW):
                if p1 in row:
                    r1 = (i, row.index(p1))
                if p2 in row:
                    r2 = (i, row.index(p2))

            # Always move right first to avoid pointing towards "void"
            if min(r1[0], r2[0]) == 0 and min(r1[1], r2[1]) == 0:
                if r1[0] > r2[0]:
                    s += "^"*abs(r1[0]-r2[0])
                if r1[0] < r2[0]:
                    s += "v"*abs(r1[0]-r2[0])
                if r1[1] < r2[1]:
                    s += ">"*abs(r1[1]-r2[1])
                if r1[1] > r2[1]:
                    s += "<"*abs(r1[1]-r2[1])
            else: # If no risk of pointing towards void, end as close to 'A' as possible
                if r1[1] > r2[1]:
                    s += "<"*abs(r1[1]-r2[1])
                if r1[0] < r2[0]:
                    s += "v"*abs(r1[0]-r2[0])
                if r1[1] < r2[1]:
                    s += ">"*abs(r1[1]-r2[1])
                if r1[0] > r2[0]:
                    s += "^"*abs(r1[0]-r2[0])
            s+= "A"
        arrows = s
    return len(arrows)


def read_input(file_path: str = "./inputs/day21.example") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f

def stars(input, npad_robots = 2):
    ans = 0
    for p in input:
        cmds = npad_to_arrow('A', p[0])
        for i,n in enumerate(p[:-1]):
            cmds += npad_to_arrow(n, p[i+1])
        ans += int(p[:-1])*shortest_seq_len(cmds, npad_robots)
    return ans



def main():
    input = read_input()
    ans1 = stars(input)
    print("Star 1:", ans1)
    ans2 = stars(input, 25)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()





