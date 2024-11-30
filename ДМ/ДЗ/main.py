import numpy as np
import networkx as nx

# Матрица смежности
adjacency_matrix = np.array([
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1],
    [0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0],
    [0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1],
    [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0],
    [0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
    [0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1],
    [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1],
    [1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1],
    [0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0]
])

# Создание графа из матрицы смежности
G2 = nx.from_numpy_array(adjacency_matrix)
G2 = nx.relabel_nodes(G2, {i: i + 1 for i in range(len(G2.nodes()))})

# Функция для определения рода графа
def compute_genus(graph):
    num_nodes = graph.number_of_nodes()
    num_edges = graph.number_of_edges()
    
    # Проверка, является ли граф полным
    if num_edges == (num_nodes * (num_nodes - 1)) // 2 and num_nodes >= 5:
        return 1  # Для K5 род равен 1
    return 0  # Для других графов нужно больше анализа

# Функция для определения толщины графа
def compute_thickness(graph):
    return nx.thickness(graph)

# Функция для определения числа пересечений
def compute_crossing_number(graph):
    return nx.crossing_number(graph)

# Вычисление свойств графа
genus = compute_genus(G2)
thickness = compute_thickness(G2)
crossing_number = compute_crossing_number(G2)

# Вывод результатов
print(f"Род графа G2: {genus}")
print(f"Толщина графа G2: {thickness}")
print(f"Число пересечений графа G2: {crossing_number}")
