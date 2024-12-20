#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <fstream>
#include <queue>


using namespace std;


const int MAXN = 100;
const int INF = 1000000000; // ���������-�������������


struct edge {
   int a, b, cap, flow; // ��������� ��� �������� ����� �����
};


int n=6, s=0, t=5, d[MAXN], ptr[MAXN];
vector<edge> e; // ������ ��� �������� ���� ����
vector<int> g[MAXN]; // ������ ��������� ��� �����


// ������� ��� ���������� ����� � ����
void add_edge (int a, int b, int cap) {
   edge e1 = { a, b, cap, 0 }; // ������ �����
   edge e2 = { b, a, 0, 0 }; // �������� ����� � ������� ���������� ������������
   g[a].push_back ((int) e.size());
   e.push_back (e1);
   g[b].push_back ((int) e.size());
   e.push_back (e2);
}


// ������� ��� ���������� ������ � ������ (BFS)
bool bfs() {
   queue<int> q;
   q.push(s);
   memset (d, -1, n * sizeof d[0]); // ������������� ������� ����������
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
   return d[t] != -1; // ���������� true, ���� �������� �����
}


// ������� ��� ���������� ������ � ������� (DFS)
int dfs (int v, int flow) {
   if (!flow)  return 0; // ���� ����� ����� ����, ���������� 0
   if (v == t)  return flow; // ���� �������� �����, ���������� �����
   for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
       int id = g[v][ptr[v]],
           to = e[id].b;
       if (d[to] != d[v] + 1)  continue; // �������� ������
       int pushed = dfs (to, min(flow, e[id].cap - e[id].flow)); // ����������� ����� DFS
       if (pushed) {
           e[id].flow += pushed; // ���������� ������
           e[id+1].flow -= pushed; // ���������� ��������� ������
           return pushed;
       }
   }
   return 0;
}


// ������� ��� ���������� ��������� ������
int dinic() {
   int flow = 0;
   for (;;) {
       if (!bfs())  break; // ���� �� ������� ��������� ������� �����, �������
       memset(ptr, 0, n * sizeof ptr[0]); // ������������� ����������
       while (int pushed = dfs (s, INF))
           flow += pushed; // ��������� ��������� �����
   }
   return flow; // ���������� ������������ �����
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
       add_edge(from-1, to-1, weight); // ��������� ����� � ����
   }


   // ����� �����
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
   int answ = dinic(); // ��������� ������������ �����
   cout << answ << endl;


   return 0;
}


