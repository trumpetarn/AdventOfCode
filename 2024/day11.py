from tqdm import tqdm


def star1(N):
    # input = [125, 17]
    input = [4329, 385, 0, 1444386, 600463, 19, 1, 56615]
    seen = set()
    hist = {}
    for v in input:
        seen.add(v)
        hist[v] = [0]

    for i in range(N):
        new_input = []
        for x in input:
            if x == 0:
                new_input.append(1)
            else:
                sx = str(x)
                if len(sx) % 2 == 0:
                    new_input.append(int(sx[: len(sx) // 2]))
                    new_input.append(int(sx[len(sx) // 2 :]))
                else:
                    new_input.append(x * 2024)
        input = new_input
    #        input = []
    #        for v in new_input:
    #            if v in seen:
    #                hist[v].append(i)
    #            else:
    #                input.append(v)
    #                hist[v] = [i]
    #        seen.update(new_input)

    print(hist)
    return len(new_input)


def main():

    print("Star 1:", star1(6))
    print("Star 2:", 0)


if __name__ == "__main__":
    main()
