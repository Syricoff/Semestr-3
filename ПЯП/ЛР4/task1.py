import numpy as np
import matplotlib.pyplot as plt

matrix = np.arange(25).reshape(5, 5)
det_initial = np.linalg.det(matrix)

array = np.arange(2, 17)
print(array)
array[(array >= 2) & (array <= 5)] *= -1
print(array)

mean_value = np.mean(array)

matrix_adjusted = matrix - mean_value

det_final = np.linalg.det(matrix_adjusted)

labels = ['Исходная матрица', 'Итоговая матрица']
det_values = [det_initial, det_final]

plt.bar(labels, det_values, color=['blue', 'orange'])
plt.ylabel('Определитель')
plt.title('Сравнение определителей матриц')
plt.show()
