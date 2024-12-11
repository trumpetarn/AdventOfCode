from tqdm import tqdm


def star1(N):
    input = [125, 17]
    # input = [4329, 385, 0, 1444386, 600463, 19, 1, 56615]

    for _ in range(N):
        new_input = []
        for i in input:
            if i == 0:
                new_input.append(1)
            else:
                si = str(i)
                if len(si) % 2 == 0:
                    new_input.append(int(si[: len(si) // 2]))
                    new_input.append(int(si[len(si) // 2 :]))
                else:
                    new_input.append(i * 2024)
        input = new_input
    return len(new_input)


def main():

    print("Star 1:", star1(25))
    print("Star 2:", 0)


if __name__ == "__main__":
    main()
