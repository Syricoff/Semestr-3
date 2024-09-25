import itertools


print(max(len(
    list(g)) for k, g in itertools.groupby(input("Введите строку: ")
                                           )))
