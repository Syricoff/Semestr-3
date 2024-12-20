#include <iostream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;


bool bfs(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
   int n = residualGraph.size();
   vector<bool> visited(n, false);
   priority_queue<pair<int, int>> pq;


   pq.push({INT_MAX, source});
   visited[source] = true;
   parent[source] = -1;


   while (!pq.empty()) {
       int capacity = pq.top().first;
       int u = pq.top().second;
       pq.pop();


       for (int v = 0; v < n; v++) {
           if (!visited[v] && residualGraph[u][v] > 0) {
               parent[v] = u;
               visited[v] = true;
               int minCapacity = min(capacity, residualGraph[u][v]);
               if (v == sink) {
                   return true;
               }
               pq.push({minCapacity, v});
           }
       }
   }
   return false;
}


int fordFulkerson(const vector<vector<int>>& graph, int source, int sink) {
   int n = graph.size();
   vector<vector<int>> residualGraph = graph;
   vector<int> parent(n);
   int maxFlow = 0;


   while (bfs(residualGraph, source, sink, parent)) {
       int pathFlow = INT_MAX;
       for (int v = sink; v != source; v = parent[v]) {
           int u = parent[v];
           pathFlow = min(pathFlow, residualGraph[u][v]);
       }


       for (int v = sink; v != source; v = parent[v]) {
           int u = parent[v];
           residualGraph[u][v] -= pathFlow;
           residualGraph[v][u] += pathFlow;
       }


       maxFlow += pathFlow;
   }
   return maxFlow;
}


int main() {
   vector<vector<int>> graph = {
       { 0, 30, 40, 20, 0 },
       { 0, 0, 50, 0, 40 },
       { 0, 0, 0, 20, 30 },
       { 0, 0, 0, 0, 30 },
       { 0, 0, 0, 0, 0 }
   };


   int source = 0;
   int sink = 4;


   cout << "Максимально возможный поток: " << fordFulkerson(graph, source, sink) << endl;


   return 0;
}