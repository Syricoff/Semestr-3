def sum_and_product(arr):
    sum_even_indices = sum(
        arr[i] for i in range(0, len(arr), 2)
    )
    product_odd_indices = 1
    for i in range(1, len(arr), 2):
        product_odd_indices *= arr[i]

    return sum_even_indices, product_odd_indices


array = [1, 2, 3, 4, 5]
sum_even, product_odd = sum_and_product(array)
print("Сумма элементов с чётными номерами:", sum_even)
print("Произведение элементов с нечётными номерами:", product_odd)
