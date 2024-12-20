#include <iostream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;


// ������� ��� ���������� BFS � ������ ����������� �������������� ����
bool bfs(const vector<vector<int>>& residualGraph, int s, int t, vector<int>& parent) {
   int n = residualGraph.size();
   vector<bool> visited(n, false);
   queue<int> q;


   q.push(s);
   visited[s] = true;
   parent.assign(n, -1);


   while (!q.empty()) {
       int u = q.front();
       q.pop();


       for (int v = 0; v < n; v++) {
           if (!visited[v] && residualGraph[u][v] > 0) {
               q.push(v);
               parent[v] = u;
               visited[v] = true;
               if (v == t)
                   return true;
           }
       }
   }
   return false;
}


// �������� ��������-����� ��� ���������� ������������� ������
int edmondsKarp(const vector<vector<int>>& graph, int s, int t) {
   int n = graph.size();
   vector<vector<int>> residualGraph = graph;
   vector<int> parent(n);
   int maxFlow = 0;


   while (bfs(residualGraph, s, t, parent)) {
       // ����� ����������� ���������� ���������� ����������� ����� ����, ���������� BFS
       int pathFlow = INT_MAX;
       for (int v = t; v != s; v = parent[v]) {
           int u = parent[v];
           pathFlow = min(pathFlow, residualGraph[u][v]);
       }


       // �������� ���������� ���������� ����������� ���� � �������� ����
       for (int v = t; v != s; v = parent[v]) {
           int u = parent[v];
           residualGraph[u][v] -= pathFlow;
           residualGraph[v][u] += pathFlow;
       }


       // �������� ����� ���� � ������ ������
       maxFlow += pathFlow;
   }
   return maxFlow;
}


int main() {
   // ������ �����, ��������������� � ���� ������� ���������
   vector<vector<int>> graph = {
       { 0, 30, 40, 20, 0 },
       { 0, 0, 50, 0, 40 },
       { 0, 0, 0, 20, 30 },
       { 0, 0, 0, 0, 30 },
       { 0,  0,  0,  0,  0,  0 }
   };


   int source = 0;
   int sink = 4;


   cout << "����������� ��������� �����: " << edmondsKarp(graph, source, sink) << endl;


   return 0;
}

