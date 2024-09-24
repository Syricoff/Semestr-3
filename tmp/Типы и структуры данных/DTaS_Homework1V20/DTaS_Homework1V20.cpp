#include <iostream>
#include "HugeNumber.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	HugeNumber hn1;
	HugeNumber hn2;
	HugeNumber result;

	hn1.ReadHugeNumber();
	hn2.ReadHugeNumber();

	std::cout << "Большое число #1: " << hn1;
	hn1.ChangeOrder();
	std::cout << " = " << hn1;
	hn1.NormalizeNumber();
	std::cout << " = " << hn1 << std::endl;

	std::cout << "Большое число #2: " << hn2;
	hn2.ChangeOrder();
	std::cout << " = " << hn2;
	hn2.NormalizeNumber();
	std::cout << " = " << hn2 << std::endl;

	result = hn1 + hn2;
	std::cout << "Сумма: " << result;
	result.ChangeOrder();
	std::cout << " = " << result;
	result.NormalizeNumber();
	std::cout << " = " << result << std::endl;

	result = result / 2;
	std::cout << "Среднее арифметическое: " << result;
	result.ChangeOrder();
	std::cout << " = " << result;
	result.NormalizeNumber();
	std::cout << " = " << result << std::endl;

	return 0;
}