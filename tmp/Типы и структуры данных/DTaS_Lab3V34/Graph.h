#ifndef GRAPH
#define GRAPH
#include <vector>
#include <iostream>
#include <exception>
#include <stack>
#include <queue>
#include <iomanip>
#include <sstream>
#include <numeric>
#include "HelpFunctions.h"

class Graph
{
public:
	// ������� �����
	using WeightMatrix = std::vector<std::vector<double>>;

	Graph(const Graph& graph);
	Graph(const WeightMatrix& weightMatrix);
	Graph(const size_t n);

	WeightMatrix& getWeightMatrix();
	void ClearGraph();
	void FillRandomly(const int MIN_WEIGHT = 1, const int MAX_WEIGHT = 1);
	size_t getVertexCount() const;
	void InsertVertex();
	void DeleteVertex(const size_t i);
	// ������� ����
	void CreateArc(const size_t i, const size_t j, const double WEIGHT = 1);
	// ������� �����
	void CreateEdge(const size_t i, const size_t j, const double WEIGHT = 1);
	// ������� ����
	void DeleteArc(const size_t i, const size_t j);
	// ������� �����
	void DeleteEdge(const size_t i, const size_t j);
	// ����� ������� ����� � ��������� ����� PRECISION
	void PrintGraph(const size_t PRECISION = 0) const;

	// ����� � �������, ������� � ������� i (���������� ����)
	std::vector<size_t> DepthFirstSearch(size_t i = 0) const;
	// ����� � ������, ������� � ������� i (���������� ����)
	std::vector<size_t> BreadthFirstSearch(size_t i = 0) const;
	// �������� ��������, ������������ ���� ��������: ������ ���������� �����(����)
	// � ������ �����
	std::pair<std::vector<double>, std::vector<std::vector<size_t>>> Dijkstra(const size_t STARTING_VERTEX = 0) const;
	// ���������� ������ ������������� ����� ����� - ������� ����� (�.�. ��� ������), 
	// ���������� ����� ������ ������� ����� ������ ���� ���
	std::vector<std::vector<size_t>> HamiltonianPath() const;
	// ���������� ������������ ����� �� ������ s � ���� t
	int FordFulkerson(const int s, const int t) const;

private:
	WeightMatrix weightMatrix{};
	// ���������� �� ����� ����� ��������� i � j
	bool ExistLink(const size_t i, const size_t j) const;
	int FordFulkerson(const int s, const int t, std::vector<std::vector<int>>& graph) const;
	int BFSforFordFulkerson(const int s, const int t, std::vector<int>& parent, std::vector<std::vector<int>>& graph) const;
};
#endif