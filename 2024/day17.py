"""
Day 17

https://adventofcode.com/2024/day/17
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
import re
import copy

def read_input(file_path: str = "./inputs/day17.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n\n")
    return f


def computer(registers, program):
    ip = 0
    output = []
    A = registers[0]
    while ip < len(program):
        opcode = program[ip]
        operand = program[ip + 1]
        literal = operand
        combo = -99999999
        match operand:
            case 0 | 1 | 2 | 3:
                combo = operand
            case 4:
                combo = registers[0]
            case 5:
                combo = registers[1]
            case 6:
                combo = registers[2]
            case 7:
                print("Reserved")
            case _:
                print("INVALID")
        # print(opcode, operand, output)
        match opcode:
            case 0:
                # adv
                registers[0] = registers[0] // (2**combo)
                ip += 2
            case 1:
                # bxl
                registers[1] = registers[1] ^ literal
                ip += 2
            case 2:
                registers[1] = combo % 8
                ip += 2
            case 3:
                if registers[0] != 0:
                    ip = literal
                else:
                    ip += 2
            case 4:
                # bxc
                registers[1] = registers[1] ^ registers[2]
                ip += 2
            case 5:
                # out
                output.append(combo % 8)
                ip += 2
            case 6:
                # bdv
                registers[1] = registers[0] // (2**combo)
                ip += 2
            case 7:
                registers[2] = registers[0] // (2**combo)
                ip += 2
    return output


def star1(input):
    regs = input[0].split("\n")
    registers = []
    for l in regs:
        a = re.findall("\d+", l)
        registers.append(int(a[0]))
    b = re.findall("\d+", input[1])
    program = [int(d) for d in b]
    out = computer(registers[:], program)
    return ",".join(map(str, out))

# Assuming that we can build register A (0) backwards in steps of 8
def star2(input):
    regs = input[0].split("\n")
    registers = []
    for l in regs:
        a = re.findall("\d+", l)
        registers.append(int(a[0]))
    b = re.findall("\d+", input[1])
    program = [int(d) for d in b]
    result = copy.deepcopy(program)
    out = []
    A = 0
    j = -1
    while len(out) < len(program):
        for i in range(0, 8):        
            out = computer([A+i, 0, 0], program)
            if out == result[j:]:
                j -= 1
                A = (A+i) << 3
                break
        else: # If no match, go back to the previous value of A plus 1
            A >>= 3
            A += 1
            j += 1
            if j == 0:
                break
    return A >> 3 # to compensate for the last increment

def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2(input)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
