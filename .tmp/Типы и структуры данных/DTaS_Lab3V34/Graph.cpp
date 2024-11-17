#include "Graph.h"

Graph::Graph(const Graph& graph) : weightMatrix(graph.weightMatrix) {}

Graph::Graph(const WeightMatrix& weightMatrix)
{
	for (auto i : weightMatrix)
	{
		if (i.size() != weightMatrix.size())
		{
			throw std::invalid_argument("Weight matrix must be square");
		}
	}
	this->weightMatrix = weightMatrix;
}

Graph::Graph(const size_t n) : weightMatrix(WeightMatrix(n, std::vector<double>(n, inf())))
{}

Graph::WeightMatrix& Graph::getWeightMatrix()
{
	return weightMatrix;
}

std::vector<size_t> Graph::DepthFirstSearch(size_t i) const
{
	std::vector<size_t> path;
	if (getVertexCount() == 1)
	{
		path.push_back(0);
		return path;
	}
	std::vector<bool> visited(getVertexCount());
	std::stack<size_t> currVertices;
	currVertices.push(i);
	while (!currVertices.empty())
	{
		// ����� ������� i �� ����� � �������� � ��� ����������
		i = currVertices.top();
		currVertices.pop();
		if (!visited[i])
		{
			path.push_back(i);
		}
		visited[i] = true;
		for (size_t j = getVertexCount() - 1; j > 0; j--)
		{
			// ���� ���� ����� i -> j � j �� �������� �����,
			if (ExistLink(i, j) && !visited[j])
			{
				// �� ��������� �� � ���� ������� ������
				currVertices.push(j);
			}
		}
	}
	return path;
}

std::vector<size_t> Graph::BreadthFirstSearch(size_t i) const
{
	std::vector<size_t> path;
	if (getVertexCount() == 1)
	{
		path.push_back(0);
		return path;
	}
	std::queue<size_t> currVertices;
	std::vector<bool> visited(getVertexCount());
	currVertices.push(i);
	path.push_back(i);
	visited[i] = true;
	while (!currVertices.empty())
	{
		i = currVertices.front();
		currVertices.pop();
		for (size_t j = 0; j < getVertexCount(); j++)
		{
			if (ExistLink(i, j) && !visited[j])
			{
				if (!visited[j])
				{
					path.push_back(j);
				}
				visited[j] = true;
				currVertices.push(j);
			}
		}
	}
	return path;
}

size_t Graph::getVertexCount() const
{
	return weightMatrix.size();
}

void Graph::ClearGraph()
{
	Graph::WeightMatrix weightMatrix{};
	this->weightMatrix = weightMatrix;
}

void Graph::FillRandomly(const int MIN_WEIGHT, const int MAX_WEIGHT)
{
	srand(time(nullptr));
	for (auto& i : weightMatrix)
	{
		for (auto& j : i)
		{
			j = getRandom(MIN_WEIGHT, MAX_WEIGHT + 1);
			j = (j == MAX_WEIGHT + 1 ? inf() : j);
		}
	}
}

void Graph::InsertVertex()
{
	for (auto& i : weightMatrix)
	{
		i.push_back(inf());
	}
	weightMatrix.push_back(std::vector<double>(weightMatrix.size() + 1, inf()));
}

void Graph::DeleteVertex(const size_t i)
{
	weightMatrix.erase(weightMatrix.begin() + i, weightMatrix.begin() + i + 1);
	for (auto& j : weightMatrix)
	{
		j.erase(j.begin() + i, j.begin() + i + 1);
	}
}

void Graph::CreateArc(const size_t i, const size_t j, const double WEIGHT)
{
	weightMatrix[i][j] = WEIGHT;
}

void Graph::CreateEdge(const size_t i, const size_t j, const double WEIGHT)
{
	weightMatrix[i][j] = weightMatrix[j][i] = WEIGHT;
}

void Graph::DeleteArc(const size_t i, const size_t j)
{
	weightMatrix[i][j] = inf();
}

void Graph::DeleteEdge(const size_t i, const size_t j)
{
	weightMatrix[i][j] = weightMatrix[j][i] = inf();
}

void Graph::PrintGraph(const size_t PRECISION) const
{
	const std::string INF = "inf";
	// ������� ������������ ����� (�� ����� ���������� �������������)
	// � ������� weightMatrix
	// ������ � ��� inf �� -inf
	WeightMatrix newWeightMatrix = weightMatrix;
	for (auto& i : newWeightMatrix)
	{
		std::replace(i.begin(), i.end(), inf(), -inf());
	}
	double maxWeight = getMatrixMaximum(newWeightMatrix);
	std::stringstream ssMaxWeight;
	ssMaxWeight << std::fixed << std::setprecision(PRECISION) << maxWeight;
	size_t lenMaxWeight = ssMaxWeight.str().length();
	bool edgesArePositive = true; // ��� ����� - ������������� �����
	for (auto i : weightMatrix)
	{
		for (auto j : i)
		{
			if (j < 0)
			{
				edgesArePositive = false;
				break;
			}
		}
		if (!edgesArePositive)
		{
			break;
		}
	}
	// ��������� ���������� ����� cellsCount ��� ������ ����� ������� weightMatrix,
	// ����� ������� �������� �����
	size_t cellsCount = std::max(lenMaxWeight, INF.length()) + 2;
	for (auto i : weightMatrix)
	{
		for (auto j : i)
		{
			if (j == inf())
			{
				std::cout << std::setw(cellsCount) << (edgesArePositive ? "0" : INF);
			}
			else
			{
				std::cout << std::setw(cellsCount) << std::fixed << std::setprecision(PRECISION) << j;
			}
		}
		std::cout << "\n";
	}
}

bool Graph::ExistLink(const size_t i, const size_t j) const
{
	return weightMatrix[i][j] != inf();
}

std::pair<std::vector<double>, std::vector<std::vector<size_t>>> Graph::Dijkstra(const size_t STARTING_VERTEX) const
{
	// ����� ��� �������, �� ������� ���������� ������ ��� ��� ��� paths, ��� ��������,
	// ��� �� � ��� ������� ������� ������
	const size_t MARK = getVertexCount() + 1;
	std::vector<double> shortestPaths(getVertexCount(), inf());
	// ���� paths[i] = j != MARK, �� �� ������� j ����� ������� �������� � ������� i
	// ���� paths[i] = j = MARK, �� � ������� i ������ ������� ��������
	std::vector<size_t> paths(getVertexCount());
	std::vector<bool> traversed(getVertexCount()); // ���������� �������
	size_t currVertex = STARTING_VERTEX;
	shortestPaths[currVertex] = 0;
	bool exit = false;
	while (!exit)
	{
		traversed[currVertex] = (currVertex != MARK);
		for (size_t i = 0; i < getVertexCount(); i++)
		{
			if (ExistLink(currVertex, i) && !traversed[i])
			{
				if (shortestPaths[currVertex] + weightMatrix[currVertex][i] < shortestPaths[i])
				{
					paths[i] = currVertex;
					shortestPaths[i] = shortestPaths[currVertex] + weightMatrix[currVertex][i];
				}
			}
		}
		currVertex = MARK; // �������� �������, ����� ���������, ���������� �� ���
		double minPath = inf();
		for (size_t i = 0; i < getVertexCount(); i++)
		{
			if (!traversed[i])
			{
				if (shortestPaths[i] < minPath)
				{
					minPath = shortestPaths[i];
					currVertex = i;
				}
			}
		}
		exit = (std::all_of(traversed.begin(), traversed.end(), [](bool v) { return v; })) || (currVertex == MARK);
	}
	std::replace_if(paths.begin(), paths.end(), [&traversed](size_t i) { return !traversed[i]; }, MARK);
	// �������� ����
	std::vector<std::vector<size_t>> directPaths;
	for (size_t i = 0; i < getVertexCount(); i++)
	{
		size_t v = i;
		std::vector<size_t> path{v};
		while (v != STARTING_VERTEX)
		{
			v = paths[v];
			path.insert(path.begin(), v);
			if (v == MARK)
			{
				path.clear();
				break;
			}
		}
		directPaths.push_back(path);
	}
	return std::make_pair(shortestPaths, directPaths);
}

std::vector<std::vector<size_t>> Graph::HamiltonianPath() const
{
	std::vector<std::vector<size_t>> paths;
	std::vector<size_t>	vertices(getVertexCount());
	std::iota(vertices.begin(), vertices.end(), 0);
	do
	{
		bool valid = true;
		for (size_t i = 0; i < vertices.size() - 1; i++)
		{
			if (!ExistLink(vertices[i], vertices[i + 1]))
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			paths.push_back(vertices);
		}
	} while (std::next_permutation(vertices.begin(), vertices.end()));
	return paths;
}

int Graph::BFSforFordFulkerson(const int s, const int target, std::vector<int>& parent, std::vector<std::vector<int>>& graph) const
{

	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;
	std::queue<std::pair<int, int>> q;
	q.push({ s, INT_MAX });
	while (!q.empty())
	{
		int u = q.front().first;
		int cap = q.front().second;
		q.pop();
		for (int v = 0; v < getVertexCount(); v++)
		{
			if (u != v && graph[u][v] != 0 && parent[v] == -1)
			{
				parent[v] = u;
				int min_cap = std::min(cap, graph[u][v]);
				if (v == target)
				{
					return min_cap;
				}
				q.push({ v, min_cap });
			}
		}
	}
	return 0;
}

int Graph::FordFulkerson(const int s, const int t) const
{
	const int V = getVertexCount();
	std::vector<std::vector<int>> rGraph(V, std::vector<int>(V)); // ���������� ���������� �����������
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			rGraph[i][j] = (weightMatrix[i][j] == inf() ? 0 : weightMatrix[i][j]);
		}
	}
	return FordFulkerson(s, t, rGraph);
}

int Graph::FordFulkerson(const int s, const int t, std::vector<std::vector<int>>& graph) const
{
	std::vector<int> parent(getVertexCount(), -1);
	int max_flow = 0;
	int min_cap = 0;
	while (min_cap = BFSforFordFulkerson(s, t, parent, graph))
	{
		max_flow += min_cap;
		int v = t;
		while (v != s)
		{
			int u = parent[v];
			graph[u][v] -= min_cap;
			graph[v][u] += min_cap;
			v = u;
		}
	}
	return max_flow;
}