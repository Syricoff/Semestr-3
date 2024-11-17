import numpy as np
import matplotlib.pyplot as plt


# Матрица 6х6 с 1 на границе и 0 внутри
matrix_1 = np.ones((6, 6), dtype="int")
matrix_1[1:-1, 1:-1] = 0
rank_1 = np.linalg.matrix_rank(matrix_1)
print("Первая матрица:")
print(matrix_1)
print(f"Ранг первой матрицы: {rank_1}")

# Матрица 6х6 с 0 на границе и 1 внутри
matrix_2 = np.zeros((6, 6), dtype="int")
matrix_2[1:-1, 1:-1] = 1
rank_2 = np.linalg.matrix_rank(matrix_2)
print("\nВторая матрица:")
print(matrix_2)
print(f"Ранг второй матрицы: {rank_2}")

# Третья матрица - произведение первых двух
matrix_3 = np.dot(matrix_1, matrix_2)
rank_3 = np.linalg.matrix_rank(matrix_3)
print("\nТретья матрица:")
print(matrix_3)
print(f"Ранг третьей матрицы: {rank_3}")

# Построение круговой диаграммы рангов матриц
labels = ['Матрица №1', 'Матрица №2', 'Матрица №3']
sizes = [rank_1, rank_2, rank_3]
max_index = sizes.index(max(sizes))
colors = ['red', 'green', 'blue']
explode = tuple([0 if i != max_index else 0.1 for i in range(len(sizes))])


def absolute_value(val):
    """Вычисление абсолютного значения из процентного"""
    a = int(np.round(val / 100 * np.array(sizes).sum(), 0))
    return a


plt.pie(sizes, explode=explode, labels=labels, colors=colors, shadow=True, autopct=absolute_value, startangle=90)
plt.title("Круговая диаграмма рангов матриц")
plt.show()
