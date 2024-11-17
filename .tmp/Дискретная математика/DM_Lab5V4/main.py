class Graph:

    def __init__(self, adj):
        self.adj = adj
        self.v = len(adj)
        self.vlist = []

    def add_edge(self, a, b):
        self.adj[a][b] = 1
        self.adj[b][a] = 1
        if a == b:
            self.adj[a][b] = 2

    def BFS(self, start):
        visited = [False] * self.v
        q = [start]
        visited[start] = True

        while q:
            vis = q[0]
            self.vlist.append(vis)
            q.pop(0)
            for i in range(self.v):
                if (self.adj[vis][i] != 0 and
                        (not visited[i])):
                    q.append(i)
                    visited[i] = True


G_1 = [[0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
       [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
       [0, 0, 0, 0, 0, 0, 1, 1, 0, 0],
       [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
       [0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
       [0, 0, 0, 0, 1, 0, 0, 1, 1, 0],
       [0, 0, 1, 0, 0, 0, 0, 1, 1, 0],
       [0, 0, 1, 0, 0, 1, 1, 0, 0, 0],
       [0, 0, 0, 0, 0, 1, 1, 0, 0, 0],
       [0, 0, 0, 1, 0, 0, 0, 0, 0, 0], ]

dop_G_1 = G_1

for i in range(len(G_1)):
    for j in range(len(G_1)):
        e = 1
        if i == j:
            e = 2
        if G_1[i][j] == e:
            dop_G_1[i][j] = 0
        if G_1[i][j] == 0:
            dop_G_1[i][j] = e

G_0 = [[0 for _ in range(len(G_1))] for _ in range(len(G_1))]

a = Graph(dop_G_1)
b = Graph(G_0)

a.BFS(0)

for i in range(len(a.vlist) - 1):
    b.add_edge(a.vlist[i], a.vlist[i + 1])

print(*b.adj, sep='\n')
