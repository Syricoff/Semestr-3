#include <iostream>
#include <ctime>
#include <random>
#include "ProfileMatrix.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
    out << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        out << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    out << "]";
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& vv)
{
    int max_length = 0;
    for (auto v : vv)
    {
        max_length = std::to_string(*std::max_element(v.begin(), v.end())).length();
    }
    max_length += 2;
    for (auto v : vv)
    {
        for (auto i : v)
        {
            std::cout << std::setw(max_length) << i;
        }
        std::cout << "\n";
    }
    return out;
}

inline int getRandom(const int _min, const int _max)
{
    return rand() % (_max - _min + 1) + _min;
}

std::vector<std::vector<int>> getBandMatrix(const int N)
{
    std::vector<std::vector<int>> matrix(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int bandwidth = getRandom(1, N / 2);
            if (i >= j)
            {
                matrix[i][j] = matrix[j][i] = (j <= i - bandwidth ? 0 : rand() % 100);
                if (rand() % 5 == 0 && i != j)
                {
                    matrix[i][j] = matrix[j][i] = 0;
                }
            }
        }
    }
    return matrix;
}

int main()
{
    srand(time(nullptr));
    ProfileMatrixStorageScheme::Matrix matrixA = getBandMatrix(10);
    ProfileMatrixStorageScheme::Matrix matrixB = getBandMatrix(10);
    ProfileMatrixStorageScheme pmssA(matrixA);
    ProfileMatrixStorageScheme pmssB(matrixB);

    std::cout << "matrix A = \n" << pmssA.getMatrix();
    std::cout << "ANA = " << pmssA.getAN() << "\n";
    std::cout << "IAA = " << pmssA.getIA() << "\n\n";

    std::cout << "matrix B = \n" << pmssB.getMatrix();
    std::cout << "ANB = " << pmssB.getAN() << "\n";
    std::cout << "IAB = " << pmssB.getIA() << "\n\n";

    ProfileMatrixStorageScheme pmssC = pmssA + pmssB;
    std::cout << "matrix C = A + B =\n" << pmssC.getMatrix();
    std::cout << "ANC = " << pmssC.getAN() << "\n";
    std::cout << "IAC = " << pmssC.getIA() << "\n";

    return 0;
}