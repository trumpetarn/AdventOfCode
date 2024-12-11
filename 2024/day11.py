from tqdm import tqdm

# input = [125, 17]
input = [4329, 385, 0, 1444386, 600463, 19, 1, 56615]

for _ in tqdm(range(75)):
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
    print(len(new_input))
