"""
Day 05
"""

from typing import List, Tuple, Dict, Set, Optional


def read_input(file_path: str = "inputs/day05.txt") -> List[str]:
    f = open(file_path, "r")
    return [line.strip() for line in f]


def star1(rules, updates):
    ruleDict = {}
    res = 0
    res2 = 0
    # key must be before values in list
    for rule in rules:
        r = rule.split("|")
        if ruleDict.get(r[0]) != None:
            ruleDict[r[0]] = ruleDict[r[0]] + [r[1]]
        else:
            ruleDict[r[0]] = [r[1]]
    for line in updates:
        order = line.split(",")
        inOrder = True
        for i, v in enumerate(order):
            r = ruleDict.get(v)
            if r != None:
                s1 = set(r)
                s2 = set(order[:i])
                if len(s1.intersection(s2)) > 0:
                    inOrder = False
                    break
        if inOrder:
            res += int(order[(len(order) - 1) // 2])
        else:
            res2 += star2(order, ruleDict)
    return res, res2


def star2(order, ruleDict):
    ordered = []
    for i, v in enumerate(order):
        r = ruleDict.get(v)
        if r != None:
            s1 = set(r)
            s2 = set(order[:i])
            inter = s1.intersection(s2)
            if len(inter) > 0:
                lowest = 9999999
                for k in inter:
                    id = ordered.index(k)
                    if id < lowest:
                        lowest = id
                ordered.insert(lowest, v)
            else:
                ordered.append(v)
        else:
            ordered.append(v)
    return int(ordered[(len(ordered) - 1) // 2])


def main():
    input = read_input()
    split = input.index("")
    rules = input[0:split]
    updates = input[split + 1 :]
    ans1, ans2 = star1(rules, updates)
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
