"""
Day 23

https://adventofcode.com/2024/day/23
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from collections import defaultdict, deque


def read_input(file_path: str = "./inputs/day23.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return f

graph = defaultdict(list)
def star1(input):
    for line in input:
        line = line.split("-")
        graph[line[0]].append(line[1])
        graph[line[1]].append(line[0])
    triples = []
    for k, v in graph.items():
        if not k.startswith("t"):
            continue
        for node in v:
            for n in graph[node]:
                if k in graph[n]:
                    next = sorted([k, node, n])
                    if next not in triples:
                        triples.append(next)
    return len(triples)

import networkx as nx
def star2():
    G = nx.Graph()
    for k, v in graph.items():
        for node in v:
            G.add_edge(k, node)
    clqs = nx.find_cliques(G)
    l = max(clqs, key=len)
    return ",".join(sorted(l))


def main():
    input = read_input()
    ans1 = star1(input)
    ans2 = star2()
    print("Star 1:", ans1)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
