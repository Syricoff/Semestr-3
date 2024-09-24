#include <string>
#include <iostream>
#include <regex>
#include <algorithm>

class HugeNumber
{
public:
	HugeNumber(bool sign = false, std::string mantissa = "0.0", int order = 0);
	HugeNumber(const HugeNumber& hn);

	bool getSign();
	std::string getMantissa();
	int getOrder();
	void ReadHugeNumber();
	void NormalizeNumber();
	void ChangeOrder(int newOrder = 0);

	friend std::ostream& operator<<(std::ostream& out, const HugeNumber& hn);
	friend bool operator>(const HugeNumber& hn1, const HugeNumber& hn2);
	friend bool operator<(const HugeNumber& hn1, const HugeNumber& hn2);
	friend bool operator==(const HugeNumber& hn1, const HugeNumber& hn2);
	friend bool operator!=(const HugeNumber& hn1, const HugeNumber& hn2);
	friend bool operator>=(const HugeNumber& hn1, const HugeNumber& hn2);
	friend bool operator<=(const HugeNumber& hn1, const HugeNumber& hn2);
	friend HugeNumber operator-(const HugeNumber& hn);
	friend HugeNumber operator/(const HugeNumber& hn, const int n);
	friend HugeNumber operator-(const HugeNumber& hn1, const HugeNumber& hn2);
	friend HugeNumber operator+(const HugeNumber& hn1, const HugeNumber& hn2);

private:
	void RemoveExtraZeros();
	int getIntPartLength();
	int getFracPartLength();

	bool sign;				// Знак числа (false +, true -)
	std::string mantissa;	// Мантисса числа
	int order;				// Порядок
};