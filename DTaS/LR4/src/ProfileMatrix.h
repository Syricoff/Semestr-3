#ifndef PMSS
#define PMSS
#include <vector>
#include <stdexcept>
#include <algorithm>

class ProfileMatrixStorageScheme
{
public:
    using Matrix = std::vector<std::vector<int>>;

    ProfileMatrixStorageScheme(const Matrix& matrix);
    ProfileMatrixStorageScheme(const std::vector<int>& AN, const std::vector<int>& IA);
    Matrix getMatrix() const;
    std::vector<int> getAN() const;
    std::vector<int> getIA() const;
    friend ProfileMatrixStorageScheme operator+(const ProfileMatrixStorageScheme& pmss1, const ProfileMatrixStorageScheme& pmss);

private:
    Matrix matrix;
    std::vector<int> AN;
    std::vector<int> IA;
};
#endif