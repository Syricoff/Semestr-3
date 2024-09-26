array = [3, 1, 4, 1, 5, 9, 2]
min_index, max_index = array.index(min(array)), array.index(max(array))
array[min_index], array[max_index] = array[max_index], array[min_index]
print("Массив после перестановки:", array)
