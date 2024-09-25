import random


a = float(input("a: "))
b = float(input("b: "))

X = [[round(random.uniform(a, b), 3) for _ in range(10)] for _ in range(10)]
min_row_index = 0
min_value = X[0][0]
for i in range(10):
    for j in range(10):
        if X[i][j] < min_value:
            min_value = X[i][j]
            min_row_index = i

X[0], X[min_row_index] = X[min_row_index], X[0]
for row in X:
    print(row)

# start
# io(Ввод: a
# Ввод: b)

# block`X =
# матрица 10*10
# из рандомных
# элементов`

# block`min_row_index = 0
# min_value = X[0][0]`

# connect(A)


# for`i = 0(1)9` {
#     for`j = 0(1)9` {
#         if`X[i][j] < min_value` then(да) {
#             block`min_value = X[i][j]`
#             block`min_row_index = i`
#         }
#     }
# }


# connect(A)

# block`меняем местами
# значения первого
# и минимального
# элемента`

# for`row in X` {
#     io`Вывод: row`
# }
# stop
