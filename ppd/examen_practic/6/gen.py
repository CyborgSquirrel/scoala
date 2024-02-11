import random

for i in range(5):
    with open(str(i), "w") as f:
        for _ in range(50):
            id_ = random.randint(0, 100)
            serviciu = random.randint(1, 4)
            f.write(f"{id_} {serviciu}\n")
