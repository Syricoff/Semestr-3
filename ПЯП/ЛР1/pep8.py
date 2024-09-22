# Задача 1

import random
import itertools
import math


a = float(input("a: "))
b = float(input("b: "))

X = [[random.uniform(a, b) for _ in range(10)] for _ in range(10)]

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


# Задача 2
k = 0
for i in range(100, 1000):
    if i % 15 == 0 and i % 30 != 0:
        print(i)
        k += 1
print(k)


# Задача 3
print(sum([int(digit) for i, digit in enumerate(input(), start=1) if i % 2 != 0]))


# Задача 4
def payout(amount):
    if amount <= 7:
        return "The amount must be greater than 7 rubles."
    for threes in range(0, amount // 3 + 1):
        for fives in range(0, amount // 5 + 1):
            if threes * 3 + fives * 5 == amount:
                return f"Payout: {threes} three-ruble and {fives} five-ruble bills."

    return "It is impossible to pay this amount with only three- and five-ruble bills."


amount = int(input("Enter the amount to be paid (more than 7 rubles): "))
result = payout(amount)
print(result)


# Задача 5
bin_array = [0, 1, 0, 1, 1, 0, 0, 1, 0, 1]
bin_array.sort()
print(*bin_array)

# Задача 6
print(max(len(list(g)) for k, g in itertools.groupby(input("Введите строку: "))))

# Задача 7
inp = map(input("Введите строку: "), lambda s: all(s[i] >= s[i + 1] for i in range(len(s) - 1)) and s.isalpha())
print("Буквы расположены в обратном алфавитном порядке:", inp)

# Задача 8


def f(x):
    return math.sin(x) + math.sin(2 * x**2) + math.sin(3 * x**3)


# Вычисление значений функции для x от 0.0 до 1.2 с шагом 0.1
x = 0.0
while x <= 1.2:
    print(f"f({x:.1f}) = {f(x):.4f}")
    x += 0.1


# Задача 9
IM = []

for i in range(1, 101, 2):
    IM.append(i + 1)
    IM.append(i)

print("Массив IM(100):", *IM)

# Задача 10


def cube_root(x):
    # Начальное приближение
    y = x

    while True:
        y_next = (1/3) * (2 * y + x / (y ** 2))  # Итерационная формула
        if abs(y_next - y) < 1e-5:  # Условие остановки
            break
        y = y_next  # Обновляем значение y

    return y


# Ввод значения x
x = float(input("Введите вещественное число x: "))
result = cube_root(x)
print(f"Приближенное значение кубического корня из {x} равно {result:.6f}")
