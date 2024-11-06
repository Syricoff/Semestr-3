#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stack>

Graph::Graph(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    file >> numCities;
    adjacencyMatrix.resize(numCities, std::vector<int>(numCities, 0));

    for (int i = 0; i < numCities; ++i)
    {
        for (int j = 0; j < numCities; ++j)
        {
            file >> adjacencyMatrix[i][j];
        }
    }
    file.close();
}

int Graph::cityIndex(char city)
{
    return city - 'A';
}

char Graph::indexCity(int index)
{
    return 'A' + index;
}

void Graph::dfs(int startCity, int threshold)
{
    std::vector<bool> visited(numCities, false);
    std::stack<std::pair<int, int>> stack; // (city, currentDistance)
    stack.push({startCity, 0});
    visited[startCity] = true;

    while (!stack.empty())
    {
        auto [city, currentDistance] = stack.top();
        stack.pop();

        for (int i = 0; i < numCities; ++i)
        {
            if (adjacencyMatrix[city][i] > 0)
            {
                int newDistance = currentDistance + adjacencyMatrix[city][i];

                if (newDistance > threshold && !visited[i])
                {
                    std::cout << indexCity(i) << " ";
                }

                if (!visited[i])
                {
                    visited[i] = true;
                    stack.push({i, newDistance});
                }
            }
        }
    }
}

void Graph::findCitiesBeyondDistance(char startCity, int threshold)
{
    int startIndex = cityIndex(startCity);
    std::cout << "Города на расстоянии больше " << threshold << " от города " << startCity << ": ";
    dfs(startIndex, threshold);
    std::cout << std::endl;
}
