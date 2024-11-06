#include "Graph.h"
#include <iostream>

int main()
{
    Graph graph("input.txt");

    char startCity;
    int threshold;
    std::cout << "Введите начальный город (A-E) и порог расстояния: ";
    std::cin >> startCity >> threshold;

    graph.findCitiesBeyondDistance(startCity, threshold);

    return 0;
}
