#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

class Graph
{
public:
    Graph(const std::string &filename);
    void findCitiesBeyondDistance(char startCity, int threshold);

private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int numCities;
    void dfs(int startCity, int threshold);
    int cityIndex(char city);
    char indexCity(int index);
};

#endif // GRAPH_H
