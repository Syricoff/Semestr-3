import itertools


for k, g in itertools.groupby(input("Введите строку: ")):
    print(k, list(g))
