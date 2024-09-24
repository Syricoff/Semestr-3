print("a b c f")
for a in range(2):
    for b in range(2):
        for c in range(2):
            f = not(a or b and c) or a
            print(a, b, c, int(f))
