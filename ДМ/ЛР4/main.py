import numpy as np
import networkx as nx
import matplotlib.pyplot as plt


class Graph:
    def __init__(self, adjacency_matrix):
        self.adjacency_matrix = np.array(adjacency_matrix)
        self.num_vertices = len(adjacency_matrix)

    def is_eulerian(self):
        odd_count = 0
        for i in range(self.num_vertices):
            degree = sum(self.adjacency_matrix[i])
            if degree % 2 != 0:
                odd_count += 1
        if odd_count == 0:
            return "Замкнутый эйлеров граф"
        elif odd_count == 2:
            return "Полуэйлеров граф"
        else:
            return "Не является эйлеровым графом"

    def find_eulerian_circuit(self, start_vertex=None):
        if self.is_eulerian() == "Не является эйлеровым графом":
            return []

        temp_matrix = self.adjacency_matrix.copy()
        eulerian_circuit = []
        current_vertex = start_vertex if start_vertex is not None else 0

        stack = [current_vertex]
        while stack:
            current_vertex = stack[-1]
            next_vertex = self.find_next_vertex(current_vertex, temp_matrix)
            if next_vertex is None:
                eulerian_circuit.append(current_vertex + 1)
                stack.pop()
            else:
                temp_matrix[current_vertex][next_vertex] = 0
                temp_matrix[next_vertex][current_vertex] = 0
                stack.append(next_vertex)

        if eulerian_circuit[0] != eulerian_circuit[-1]:
            eulerian_circuit.append(eulerian_circuit[0])

        return eulerian_circuit

    def find_next_vertex(self, vertex, temp_matrix):
        for next_vertex in range(self.num_vertices):
            if temp_matrix[vertex][next_vertex] > 0:
                return next_vertex
        return None

    def visualize_eulerian_circuit(self, path):
        G = nx.Graph(self.adjacency_matrix)
        pos = {
            0: (2, 3),
            1: (2.5, 2),
            2: (2.75, 0.75),
            3: (2.5, -0.05),
            4: (2, -1),
            5: (1.5, -0.3),
            6: (1.25, 0.75),
            7: (1.5, 2),
        }
        labels = {
            i: str(i + 1) for i in range(self.num_vertices)
        }

        fig, ax = plt.subplots(figsize=(10, 10))
        nx.draw(
            G,
            pos,
            with_labels=True,
            labels=labels,
            node_color="lightblue",
            node_size=700,
            font_size=15,
            ax=ax,
        )

        for i in range(len(path)):
            path_edges = [(path[i] - 1, path[(i + 1) % len(path)] - 1)]
            nx.draw_networkx_edges(
                G, pos, edgelist=path_edges, edge_color="red", width=4, ax=ax
            )
            plt.draw()
            plt.pause(0.5)
            nx.draw(
                G,
                pos,
                with_labels=True,
                labels=labels,
                node_color="lightblue",
                node_size=700,
                font_size=15,
                ax=ax,
            )

        plt.title("Эйлерова цепь")
        plt.show()


if __name__ == "__main__":
    adjacency_matrix = [
        [0, 1, 0, 0, 0, 1, 0, 0],
        [1, 0, 1, 0, 1, 0, 0, 1],
        [0, 1, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 1],
        [0, 1, 0, 1, 0, 1, 0, 1],
        [1, 0, 1, 0, 1, 0, 1, 0],
        [0, 0, 0, 0, 0, 1, 0, 1],
        [0, 1, 0, 1, 1, 0, 1, 0],
    ]

    graph = Graph(adjacency_matrix)

    print(graph.is_eulerian())

    if graph.is_eulerian() != "Не является эйлеровым графом":
        eulerian_circuit = graph.find_eulerian_circuit()

        print("Эйлерова цепь:", eulerian_circuit)
        
        graph.visualize_eulerian_circuit(eulerian_circuit)
    else:
        print("Невозможно найти эйлерову цепь.")
