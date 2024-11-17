#include <iostream>
#include <cmath>
#include <string>
using namespace std;

bool IsDigit(char c);
bool IsPoint(char c);
double Input(string message, double min, double max);
double CalculateC(double a, double x);

int main()
{
	double a{}, x{}, result{};

	a = Input("Enter the number a: ", SHRT_MIN, SHRT_MAX);
	x = Input("Enter the number x: ", SHRT_MIN, SHRT_MAX);
	result = CalculateC(a, x);
	cout << a << endl;
	cout << x << endl;
	cout << "Result y: " << result << endl;
	return 0;
}

double CalculateC(double a, double x)
{
	double result{};
	result = (((320.0 / 4) + (256.0 / 2) - 14.0 * (sin(x - a) / cos(x + a))) / (56 * 2 * log(x - a))) * (3 + 2);
	return result;
}

double Input(string message, double min, double max)
{
	double number = 0;
	bool correct = false;
	while (!correct)
	{
		cout << message;
		string input = "";
		cin >> input;
		correct = (input[0] == '-' || IsDigit(input[0]) || IsPoint(input[0]));
		for (size_t i = 1; i < input.size(); i++)
		{
			correct = IsDigit(input[i]) || IsPoint(input[i]);
			if (!correct)
			{
				break;
			}
		}
		if (!correct)
		{
			cout << "Incorrect number entry!\n";
		}
		if (correct && input.size() > std::to_string(SHRT_MAX).size())
		{
			correct = false;
			cout << "The entered number out of range!\n";
		}
		if (correct)
		{
			number = stod(input);
			if (min > number || max < number)
			{
				correct = false;
				cout << "The entered number out of range!\n";
			}
		}
	}
	return number;
}

bool IsDigit(char c)
{
	return '0' <= c && c <= '9';
}

bool IsPoint(char c)
{
	return c == '.';
}