from tqdm import tqdm


def stones(N):
    input = [125, 17]
    input = [4329, 385, 0, 1444386, 600463, 19, 1, 56615]
    data = dict()
    for v in input:
        data[v] = 1
    for i in tqdm(range(N)):
        new = []
        for x in data:
            if data[x] > 0:
                n = data[x]
                data[x] = 0
                if x == 0:
                    new += [(1, n)]
                else:
                    sx = str(x)
                    if len(sx) % 2 == 0:
                        a = int(sx[: len(sx) // 2])
                        b = int(sx[len(sx) // 2 :])
                        new += [(a, n), (b, n)]
                    else:
                        new += [(x * 2024, n)]

        for v, n in new:
            data[v] = data.get(v, 0) + n

    return data


def main():
    a = stones(25)
    b = stones(75)

    print("Star 1:", sum([x for x in a.values()]))
    print("Star 2:", sum([x for x in b.values()]))


if __name__ == "__main__":
    main()
