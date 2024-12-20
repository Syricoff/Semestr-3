#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <fstream>
#include <queue>


using namespace std;


const int MAXN = 100;
const int INF = 1000000000; // константа-бесконечность


struct edge {
   int a, b, cap, flow; // структура для хранения ребра графа
};


int n=6, s=0, t=5, d[MAXN], ptr[MAXN];
vector<edge> e; // вектор для хранения всех рёбер
vector<int> g[MAXN]; // список смежности для графа


// функция для добавления ребра в граф
void add_edge (int a, int b, int cap) {
   edge e1 = { a, b, cap, 0 }; // прямое ребро
   edge e2 = { b, a, 0, 0 }; // обратное ребро с нулевой пропускной способностью
   g[a].push_back ((int) e.size());
   e.push_back (e1);
   g[b].push_back ((int) e.size());
   e.push_back (e2);
}


// функция для выполнения поиска в ширину (BFS)
bool bfs() {
   queue<int> q;
   q.push(s);
   memset (d, -1, n * sizeof d[0]); // инициализация массива расстояний
   d[s] = 0;
   while (!q.empty() && d[t] == -1) {
       int v = q.front();
       q.pop();
       for (size_t i=0; i<g[v].size(); ++i) {
           int id = g[v][i],
               to = e[id].b;
           if (d[to] == -1 && e[id].flow < e[id].cap) {
               q.push(to);
               d[to] = d[v] + 1;
           }
       }
   }
   return d[t] != -1; // возвращает true, если достигли стока
}


// функция для выполнения поиска в глубину (DFS)
int dfs (int v, int flow) {
   if (!flow)  return 0; // если поток равен нулю, возвращаем 0
   if (v == t)  return flow; // если достигли стока, возвращаем поток
   for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
       int id = g[v][ptr[v]],
           to = e[id].b;
       if (d[to] != d[v] + 1)  continue; // проверка уровня
       int pushed = dfs (to, min(flow, e[id].cap - e[id].flow)); // рекурсивный вызов DFS
       if (pushed) {
           e[id].flow += pushed; // обновление потока
           e[id+1].flow -= pushed; // обновление обратного потока
           return pushed;
       }
   }
   return 0;
}


// функция для выполнения алгоритма Диница
int dinic() {
   int flow = 0;
   for (;;) {
       if (!bfs())  break; // если не удалось построить уровень графа, выходим
       memset(ptr, 0, n * sizeof ptr[0]); // инициализация указателей
       while (int pushed = dfs (s, INF))
           flow += pushed; // добавляем найденный поток
   }
   return flow; // возвращаем максимальный поток
}


int main() {
   ifstream file("input.txt");
   if (!file) {
       cerr << "Unable to open file";
       return 1;
   }


   int numRelations;
   file >> numRelations;


   vector<vector<int>> adj(MAXN);


   for (int i = 0; i < numRelations; ++i) {
       int from, to, weight;
       file >> from >> to >> weight;
       add_edge(from-1, to-1, weight); // добавляем ребро в граф
   }


   // вывод графа
   cout << "Graph:" << endl;
   for (int i = 0; i < MAXN; ++i) {
       if (g[i].size() == 0) {
           continue;
       }
       cout << i << ": ";
       for (int j = 0; j < g[i].size(); ++j) {
           cout << e[g[i][j]].b << " ";
       }
       cout << endl;
   }
   int answ = dinic(); // вычисляем максимальный поток
   cout << answ << endl;


   return 0;
}


