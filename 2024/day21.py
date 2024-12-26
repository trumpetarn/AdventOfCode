"""
Day 21

https://adventofcode.com/2024/day/21
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
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
def shortest_path(p1, p2, keys=NPAD) -> str:
    if p1 == p2:
        return "A"
    for i, row in enumerate(keys):
        if p1 in row:
            r1 = (i, row.index(p1))
        if p2 in row:
            r2 = (i, row.index(p2))
    s = ""

    # Always move right first to avoid pointing towards "void"
    if keys == ARROW and min(r1[0], r2[0]) == 0 and min(r1[1], r2[1]) == 0:
        if r1[0] > r2[0]:
            s += "^"*abs(r1[0]-r2[0])
        if r1[0] < r2[0]:
            s += "v"*abs(r1[0]-r2[0])
        if r1[1] < r2[1]:
            s += ">"*abs(r1[1]-r2[1])
        if r1[1] > r2[1]:
            s += "<"*abs(r1[1]-r2[1])
    elif keys == NPAD and max(r1[0], r2[0]) == 3 and min(r1[1], r2[1]) == 0:
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


def read_input(file_path: str = "./inputs/day21.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f


def star1(input):
    answers = []
    for p in input:
        cmds = shortest_path('A', p[0])
        for i,n in enumerate(p[:-1]):
            cmds += shortest_path(n, p[i+1])
        
        # Robot 2
        cmd2 = shortest_path('A', cmds[0], ARROW)
        for i,n in enumerate(cmds[:-1]):
            cmd2 += shortest_path(n, cmds[i+1], ARROW)
        
        # Robot 3
        cmd3 = shortest_path('A', cmd2[0], ARROW)
        for i,n in enumerate(cmd2[:-1]):
            cmd3 += shortest_path(n, cmd2[i+1], ARROW)
        answers.append(len(cmd3)*int(p[:-1]))
    print(answers)
    return sum(answers)


def star2(input):
    ans = 0
    for p in input:
        cmds = shortest_path('A', p[0])
        for i,n in enumerate(p[:-1]):
            cmds += shortest_path(n, p[i+1])
        for j in range(0,2):
            cmd2 = shortest_path('A', cmds[0], ARROW)
            for i,n in enumerate(cmds[:-1]):
                cmd2 += shortest_path(n, cmds[i+1], ARROW)
            cmds = cmd2
        ans += len(cmd2)*int(p[:-1])
    return ans



def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()





