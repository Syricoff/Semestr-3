import random as rand

size = int(input("Введите количество элементов массива: "))
array_1 = [rand.randint(-100, 100) for i in range(size)]
print("Исходный массив: \n", array_1)
array_2 = [i for i in array_1 if i % 2]
print("Конечный массив: \n", sorted(array_2, reverse=True))
