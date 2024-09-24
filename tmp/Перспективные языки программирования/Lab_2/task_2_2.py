import random as rand

size = int(input("Введите количество элементов массива: "))
array = [rand.randint(-100, 100) for i in range(size)]
print("Целочисленный массив:\n", array)
print("Максимальный элемент массива: ", max_el := max(array), "[", array.index(max_el), "]", sep="")
