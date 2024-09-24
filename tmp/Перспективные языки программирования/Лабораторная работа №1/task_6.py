import random
import math
"""n = int(input("Введите количество элементов массива: "))
upp = int(input("Введите границу массива: "))
a = [random.randint(0, upp) for i in range(n)]"""
a = [float(i) for i in input("Введите числа через пробел: ").split()]
n = len(a)
for i in range(n):
    print("A[",i,"]","=", a[i], "\n")
index = 0
for i in range(n - 1):
    if (abs(a[i + 1] - a[i]) < abs(a[index + 1] - a[index])):
        index = i
print("Близкорасположенные числа ",a[index],'',a[index + 1])

input()
