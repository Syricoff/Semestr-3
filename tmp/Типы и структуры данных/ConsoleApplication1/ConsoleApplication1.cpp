#include <iostream>
#include <ctime>
using namespace std;


int* GetRandomArr(int size)
{
    int* arr = new int[size];
    srand(time(nullptr));
    int num;
    for (int i = 0; i < size; i++)
    {
        num = rand() % 20 + 1;
        arr[i] = num;
    }
    return arr;
}

bool inArray(int* arr, int need, int count)
{
    for (int i = 0; i < count; ++i)
        if (arr[i] == need)
            return true;
    return false;
}
int* uniq(int* arr, int size, int& newSize)
{
    int* localArr = new int[size] { 0 };
    for (int i = 0; i < size; ++i)
    {
        if (inArray(localArr - newSize, arr[i], size))
            continue;
        ++newSize;
        *localArr++ = arr[i];
    }
    return localArr - newSize;
}

int main()
{
    int size{};
    cout << "Введите размер массива: ";
    cin >> size;
    //int* arr = GetRandomArr(size);
    //for (int i = 0; i < 10; ++i)
    //    cout << arr[i] << " ";
    //cout << endl;
    //int newSize = 0;
    //int* newArr = uniq(arr, size, newSize);
    //for (int i = 0; i < newSize; ++i)
    //    cout << newArr[i] << " ";
    return 0;
    //delete[] arr;
}