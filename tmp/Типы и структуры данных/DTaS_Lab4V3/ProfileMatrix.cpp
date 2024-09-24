#include "ProfileMatrix.h"

ProfileMatrixStorageScheme::ProfileMatrixStorageScheme(const Matrix& _matrix)
{
    // проверка на симметричность
    for (auto i : _matrix)
    {
        if (i.size() != _matrix.size())
        {
            throw std::invalid_argument("Matrix must be symmetrical");
        }
    }

    const int N = _matrix.size(); // порядок матрицы

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (_matrix[i][j] != _matrix[j][i])
            {
                throw std::invalid_argument("Matrix must be symmetrical");
            }
        }
    }

    matrix = _matrix;

    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        bool begin = false;
        for (int j = 0; j <= i; j++)
        {
            if (matrix[i][j] != 0)
            {
                begin = true;
            }
            if (begin)
            {
                cnt++;
                AN.push_back(matrix[i][j]);
            }
        }
        IA.push_back(cnt);
    }
}

ProfileMatrixStorageScheme::ProfileMatrixStorageScheme(const std::vector<int>& _AN, const std::vector<int>& _IA)
{
    AN = _AN;
    IA = _IA;
    // конструируем матрицу matrix из AN и IA
    const int N = IA.size(); // порядок матрицы
    matrix = std::vector<std::vector<int>>(N, std::vector<int>(N));
    matrix[0][0] = AN[0];
    // заполним половину матрицы
    for (int i = 1; i < N; i++)
    {
        for (int j = IA[i - 1]; j < IA[i]; j++)
        {
            int m = IA[i] - IA[i - 1];    // количество элементов в i-ой строке, начиная с первого ненулевого до диагонального включительно
            int jmini = i - m + 1;        // стобцовый индекс первого ненулевого элемента в i-ой строке
            matrix[i][jmini + j - IA[i - 1]] = AN[j];
        }
    }
    // сделаем матрицу симметричной, заполнив вторую половину матрицы
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i > j)
            {
                matrix[j][i] = matrix[i][j];
            }
        }
    }
}

ProfileMatrixStorageScheme::Matrix ProfileMatrixStorageScheme::getMatrix() const
{
    return matrix;
}

std::vector<int> ProfileMatrixStorageScheme::getAN() const
{
    return AN;
}

std::vector<int> ProfileMatrixStorageScheme::getIA() const
{
    return IA;
}

ProfileMatrixStorageScheme operator+(const ProfileMatrixStorageScheme& pmssA, const ProfileMatrixStorageScheme& pmssB)
{
    auto A = pmssA.getMatrix();
    auto B = pmssB.getMatrix();

    auto ANA = pmssA.getAN();
    auto IAA = pmssA.getIA();

    auto ANB = pmssB.getAN();
    auto IAB = pmssB.getIA();

    if (A.size() != B.size())
    {
        throw std::invalid_argument("Matrices must be of the same order");
    }

    const int N = A.size();
    std::vector<int> ANC;
    std::vector<int> IAC;
    ANC.push_back(ANA[0] + ANB[0]);
    for (int i = 1; i < N; i++)
    {
        std::vector<int> striA; // строка i матрицы A
        std::vector<int> striB; // строка i матрицы B

        for (int j = IAA[i - 1]; j < IAA[i]; j++)
        {
            striA.push_back(ANA[j]);
        }

        for (int j = IAB[i - 1]; j < IAB[i]; j++)
        {
            striB.push_back(ANB[j]);
        }

        std::vector<int> mnstri = (striA.size() > striB.size() ? striB : striA); // вектор с минимальной длиной из striA и striB
        std::vector<int> mxstri = (striA.size() > striB.size() ? striA : striB); // вектор с максимальной длиной из striA и striB

        std::reverse(mnstri.begin(), mnstri.end());
        std::reverse(mxstri.begin(), mxstri.end());

        for (int j = 0; j < mnstri.size(); j++)
        {
            mxstri[j] += mnstri[j];
        }
        std::reverse(mxstri.begin(), mxstri.end());
        for (auto j : mxstri)
        {
            ANC.push_back(j);
        }
        IAC.push_back(ANC.size());
    }
    IAC.insert(IAC.begin(), 1);
    ProfileMatrixStorageScheme pmssC(ANC, IAC);
    return pmssC;
}