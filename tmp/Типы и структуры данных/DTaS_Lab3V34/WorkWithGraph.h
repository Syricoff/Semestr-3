#ifndef WORK_WITH_GRAPH
#define WORK_WITH_GRAPH
#include "Graph.h"
#include "HelpFunctions.h"
#include "FileLogging.h"
#include "Menu.h"

inline void mPrintGraph(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to display an empty graph");
        return;
    }
    graph->PrintGraph();
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mGraphIsEmpty(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    foutlog.Logging(concat("Function call: ", __func__));
    std::cout << "���� ����: " << (graph->getVertexCount() == 0 ? "��" : "���") << "\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mInsertVertex(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == INT_MAX)
    {
        std::cout << "���� ������� �������!\n";
        ferrlog.Logging("Attempt to add a vertex to a very large graph");
    }
    graph->InsertVertex();
    std::cout << "������� ������� ���������!";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mDeleteVertex(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to remove a vertex from an empty graph");
        return;
    }
    int v = InputInt("������� ����� �������, ������� ���������� �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    graph->DeleteVertex(v);
    std::cout << "������� " << v << " ������� �������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mCreateEdge(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to create an edge in an empty graph");
        return;
    }
    int v1 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int v2 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int w = InputInt("������� ��� �����: ", INT_MIN, INT_MAX, &ferrlog);
    graph->CreateEdge(v1, v2, w);
    std::cout << "����� (" << v1 << ", " << v2 << ") ������� ���������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mCreateArc(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to create an arc in an empty graph");
        return;
    }
    int v1 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int v2 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int w = InputInt("������� ��� �����: ", INT_MIN, INT_MAX, &ferrlog);
    graph->CreateArc(v1, v2, w);
    std::cout << "���� (" << v1 << ", " << v2 << ") ������� ���������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mDeleteEdge(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to remove an edge from an empty graph");
        return;
    }
    int v1 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int v2 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    graph->DeleteEdge(v1, v2);
    std::cout << "����� (" << v1 << ", " << v2 << ") ������� �������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mDeleteArc(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to remove an arc from an empty graph");
        return;
    }
    int v1 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int v2 = InputInt("������� ����� ������ �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    graph->DeleteArc(v1, v2);
    std::cout << "���� (" << v1 << ", " << v2 << ") ������� �������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mFillRandomly(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to fill an empty graph with random numbers");
        return;
    }
    int minw = InputInt("������� ����������� ���: ", INT_MIN, INT_MAX, &ferrlog);
    int maxw = InputInt("������� ������������ ���: ", INT_MIN, INT_MAX, &ferrlog);
    graph->FillRandomly(minw, maxw);
    std::cout << "������� ����� ��������� ���������� �������!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mBreadthFirstSearch(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to apply a BFS in an empty graph");
        return;
    }
    int v = InputInt("������� ����� �������, � ������� ���� �������� �����: ", 0, graph->getVertexCount() - 1, &ferrlog);
    std::cout << graph->BreadthFirstSearch(v) << "\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mDepthFirstSearch(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to apply a DFS in an empty graph");
        return;
    }
    int v = InputInt("������� ����� �������, � ������� ���� �������� �����: ", 0, graph->getVertexCount() - 1, &ferrlog);
    std::cout << graph->DepthFirstSearch(v) << "\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mClearGraph(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to clear an empty graph");
        return;
    }
    graph->ClearGraph();
    std::cout << "������ ���� ����!\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mDijkstra(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to apply Dijkstra's algorithm to an empty graph");
        return;
    }
    int v = InputInt("������� ��������� �������: ", 0, graph->getVertexCount() - 1, &ferrlog);
    auto dijksta = graph->Dijkstra(v);
    for (size_t i = 0; i < dijksta.first.size(); i++)
    {
        if (v != int(i))
        {
            std::cout << "���� " << v << "->" << i << ": " << dijksta.second[i] << " ����� ����: " << dijksta.first[i] << "\n";
        }
    }
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mHamiltonianPath(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to find Hamiltonian paths in an empty graph");
        return;
    }
    auto hps = graph->HamiltonianPath();
    std::cout << "������������ ����:\n";
    if (hps.empty())
    {
        std::cout << "�� ���������� � ������ �����!\n";
    }
    else
    {
        for (auto i : hps)
        {
            std::cout << i << "\n";
        }
    }
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mFordFulkerson(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    if (graph->getVertexCount() == 0)
    {
        std::cout << "���� ������!\n";
        ferrlog.Logging("Attempt to apply Dijkstra's algorithm to an empty graph");
        return;
    }
    int s = InputInt("������� �������-�����: ", 0, graph->getVertexCount() - 1, &ferrlog);
    int t = InputInt("������� �������-����: ", 0, graph->getVertexCount() - 1, &ferrlog);
    if (s == t)
    {
        std::cout << "����� � ���� ������ �����������!\n";
        ferrlog.Logging("Source and sink are equal");
    }
    std::cout << "������������ ����� ����� " << graph->FordFulkerson(s, t) << "\n";
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}

inline void mReadGraphFromFile(std::vector<std::any> params)
{
    auto graph = std::any_cast<Graph*>(params[0]);
    auto finpdata = std::any_cast<std::string>(params[1]);
    auto foutlog = std::any_cast<FileLogging>(params[2]);
    auto ferrlog = std::any_cast<FileLogging>(params[3]);
    foutlog.Logging(concat("Function call: ", __func__));
    std::fstream fin(finpdata, std::ios::in);
    Graph::WeightMatrix weightMatrix;
    std::vector<double> buffer;
    if (fin.is_open())
    {
        std::string data;
        while (fin >> data)
        {
            buffer.push_back(data == "inf" ? inf() : std::stoi(data));
        }
        int wmsize = std::sqrt(buffer.size());
        if (wmsize * wmsize == buffer.size())
        {
            for (int i = 0; i < wmsize; i++)
            {
                std::vector<double> v;
                for (int j = 0; j < wmsize; j++)
                {
                    v.push_back(buffer[i * wmsize + j]);
                }
                weightMatrix.push_back(v);
            }
            Graph newGraph(weightMatrix);
            *graph = newGraph;
            std::cout << "���� ������� ������ �� ����� " << finpdata << "!\n";
        }
        else
        {
            std::cout << "������� ����� � ����� �� ����������!\n";
            ferrlog.Logging("Weight matrix is not square");
        }
    }
    else
    {
        std::cout << "������ ��� �������� �����!\n";
        ferrlog.Logging("Error opening file");
    }
    foutlog.Logging(concat("\n", vvtos(graph->getWeightMatrix())));
}
#endif