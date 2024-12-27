"""
Day 22

https://adventofcode.com/2024/day/22
"""

from typing import List, Tuple, Dict, Set, Optional
from pathlib import Path
from collections import defaultdict
from tqdm import tqdm

def read_input(file_path: str = "./inputs/day22.in") -> List[str]:
    f = Path(file_path).read_text().strip().split("\n")
    return [int(d) for d in f]


def next_secret(old):
    old = (old ^ (old * 64)) % 16777216
    old = (old ^ (old // 32)) % 16777216
    return (old ^ (old * 2048)) % 16777216

def generate_secrets(start, n=2000):
    secrets = [start]
    for _ in range(n):
        start = next_secret(start)
        secrets.append(start)
    return secrets

def star1(input):
    sum = 0
    for n in input:
        secrets = generate_secrets(n)
        sum += secrets[-1]
    return sum

def get_prices(secrets):
    a = int(str(secrets[0])[-1])
    b = int(str(secrets[1])[-1])
    c = int(str(secrets[2])[-1])
    d = int(str(secrets[3])[-1])
    prices = defaultdict(int)

    for s in secrets[4:]:
        p = int(str(s)[-1])
        if (b-a,c-b,d-c,p-d) not in prices: # only add the first occurence of a sequence
            prices[(b-a,c-b,d-c,p-d)] = p   
        a = b
        b = c
        c = d
        d = p

    return prices

def find_first(a,b,c,d,prices):
    for i,p in enumerate(prices[1:-5]):
        if p[1]==a and prices[i+1][1]==b and prices[i+2][1]==c and prices[i+3][1]==d:
            return prices[i+3][0]
    return 0
        

def star2(input):
    prices = defaultdict(int)
    for n in input:
        s = generate_secrets(n)
        p = get_prices(s)
        for k,v in p.items():
            prices[k] += v
    max = 0
    seq = ()
    for k,v in prices.items():
        if v > max:
            max = v
            seq = k
    return max, seq


def main():
    input = read_input()
    ans1 = star1(input)
    print("Star 1:", ans1)
    ans2 = star2(input)
    print("Star 2:", ans2)


if __name__ == "__main__":
    main()
