"""
Day 24

https://adventofcode.com/2024/day/24
"""

from collections import defaultdict
from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path


def read_input(file_path: str = "./inputs/day24.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    return f



def star1(input):
    wires = {}
    for line in input[0].split("\n"):
        w, v = line.split(": ")
        wires[w] = int(v)
    instructions = input[1].split("\n")
    while len(instructions) > 0:
        line = instructions.pop(0)
        op, loc = line.split(" -> ")
        a,b,c = op.split(" ")
        if not a in wires or not c in wires:
            instructions.append(line)
            continue
        match b:
            case "AND":
                wires[loc] = wires[a] & wires[c]
            case "OR":
                wires[loc] = wires[a] | wires[c]
            case "XOR":
                wires[loc] = wires[a] ^ wires[c]
            
    res = 0
    for k,v in wires.items():
        if k.startswith("z"):
            res += v*2**int(k[1:])
    return res


def star2(input):
    N = len(input[0].split("\n")) // 2 # get initial number of wires
    instructions = {}
    faulty_lines = set()
    for line in input[1].split("\n"):
        op, loc = line.split(" -> ")
        a,b,c = op.split(" ")
        instructions[loc] = (a,b,c)
        # For a full adder, all but the last wire writing to z should be XOR
        if loc.startswith("z") and loc != "z"+str(N) and b != "XOR":
            faulty_lines.add(loc)
        # All non-z that is not XOR should have at least one input that is not x or y
        if (not loc.startswith("z")) and b == "XOR":
            if not (a.startswith("x") or c.startswith("x")):
                if not (a.startswith("y") or c.startswith("y")):
                    faulty_lines.add(loc)
    
    for loc,(a,b,c) in instructions.items():
        if b == "XOR":
            # If you have a XOR gate with inputs x, y, there must be another XOR gate with this
            # gate as an input. Search through all gates for an XOR-gate with this gate as an input;
            # if it does not exist, your (original) XOR gate is faulty.
            if a.startswith("x") and c.startswith("y") or a.startswith("y") and c.startswith("x"):
                if (a == "x00" or c == "x00"):
                    continue
                found = False
                for _,(a2,b2,c2) in instructions.items():
                    if b2 != "XOR":
                        continue
                    if a2 == loc or c2 == loc:
                        found = True
                        break
                if not found:
                    print(a,c,a2,c2,loc)
                    faulty_lines.add(loc)
        elif b == "AND":
            # Similarly, if you have an AND-gate, there must be an OR-gate with this gate as an input. 
            # If that gate doesn't exist, the original AND gate is faulty.
            if a.startswith("x") and c.startswith("y") or a.startswith("y") and c.startswith("x"):
                if (a == "x00" or c == "x00"):
                    continue
                found = False
                for _,(a2,b2,c2) in instructions.items():
                    if b2 != "OR":
                        continue
                    if a2 == loc or c2 == loc:
                        found = True
                        break
                if not found:
                    print(a,c,a2,c2,loc)
                    faulty_lines.add(loc)

    return ",".join(sorted(list(faulty_lines)))


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)

if __name__ == "__main__":
    main()
