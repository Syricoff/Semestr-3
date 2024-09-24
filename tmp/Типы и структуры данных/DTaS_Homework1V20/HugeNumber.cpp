#include "HugeNumber.h"

HugeNumber::HugeNumber(bool sign, std::string mantissa, int order) :
	sign(sign), mantissa(mantissa), order(order)
{
	if (mantissa[0] == '.')
	{
		mantissa = "0" + mantissa;
	}
	if (mantissa.find('.') == std::string::npos)
	{
		mantissa += ".0";
	}
}

HugeNumber::HugeNumber(const HugeNumber& hn) :
	sign(hn.sign), mantissa(hn.mantissa), order(hn.order)
{
}

bool HugeNumber::getSign()
{
	return sign;
}

std::string HugeNumber::getMantissa()
{
	return mantissa;
}

int HugeNumber::getOrder()
{
	return order;
}

void HugeNumber::ReadHugeNumber()
{
	bool correct = false;
	std::string num{};
	while (!correct)
	{
		std::cout << "Введите число: ";
		correct = true;
		std::getline(std::cin, num);
		static const std::regex r("^[-+]?[0-9]*[.]?[0-9]+(?:[e][-+]?[0-9]+)?$");
		if (num.length() < 3 || !std::regex_match(num.data(), r))
		{
			std::cout << "Неверная запись числа!" << std::endl;
			correct = false;
		}
	}
	sign = (num[0] == '-');
	size_t eindex = num.find("e");
	mantissa = "";
	for (size_t i = 0; i < eindex; i++)
	{
		if (num[i] != '+' && num[i] != '-')
		{
			mantissa += num[i];
		}
	}
	if (mantissa[0] == '+')
	{
		mantissa.erase(0, 1);
	}
	std::string sorder = "";
	for (size_t i = eindex + 1; i < num.length(); i++)
	{
		sorder += num[i];
	}
	order = std::stoi(sorder);
	if (mantissa.find('.') == std::string::npos)
	{
		mantissa += ".0";
	}
}

std::ostream& operator<<(std::ostream& out, const HugeNumber& hn)
{
	out << (hn.sign ? "-" : "") << hn.mantissa;
	if (hn.order != 0)
	{
		out << "e" << hn.order;
	}
	return out;
}

void HugeNumber::RemoveExtraZeros()
{
	mantissa = mantissa.substr(mantissa.find_first_not_of('0'));        // Удаление лишних нулей в начале
	mantissa = mantissa.substr(0, mantissa.find_last_not_of('0') + 1);  // Удаление лишних нулей в конце
	mantissa = (mantissa[0] == '.' ? "0" : "") + mantissa;
	mantissa += (mantissa[mantissa.length() - 1] == '.' ? "0" : "");
}

void HugeNumber::ChangeOrder(int newOrder)
{
	int delta = order - newOrder;
	for (int i = 0; i <= abs(delta); i++)
	{
		mantissa = "0" + mantissa + "0";
	}
	int indexPoint = mantissa.find('.');
	mantissa.erase(indexPoint, 1);
	mantissa.insert(indexPoint + delta, ".");
	RemoveExtraZeros();
	order = newOrder;
}

bool operator>(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	if (!HN1.sign && HN2.sign)
	{
		return true;
	}
	if (HN1.sign && !HN2.sign)
	{
		return false;
	}
	bool inverse = false;
	if (HN1.sign && HN2.sign)
	{
		inverse = true;
	}
	if (HN1.mantissa.length() > HN2.mantissa.length())
	{
		return !inverse;
	}
	if (HN1.mantissa.length() < HN2.mantissa.length())
	{
		return inverse;
	}
	for (size_t i = 0; i < HN1.mantissa.length(); i++)
	{
		if (HN1.mantissa[i] > HN2.mantissa[i])
		{
			return !inverse;
		}
		if (HN1.mantissa[i] < HN2.mantissa[i])
		{
			return inverse;
		}
	}
	return false;
}

bool operator==(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	if (HN1.sign != HN2.sign)
	{
		return false;
	}
	if (HN1.mantissa.length() != HN2.mantissa.length())
	{
		return false;
	}
	for (size_t i = 0; i < HN1.mantissa.length(); i++)
	{
		if (HN1.mantissa[i] != HN2.mantissa[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	return !(HN1 == HN2);
}

bool operator<(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	return (!(HN1 > HN2)) && (HN1 != HN2);
}

bool operator>=(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	return (HN1 > HN2) || (HN1 == HN2);
}

bool operator<=(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	return (HN1 < HN2) || (HN1 == HN2);
}

HugeNumber operator-(const HugeNumber& hn)
{
	return HugeNumber(!hn.sign, hn.mantissa, hn.order);
}

HugeNumber operator-(const HugeNumber& hn1, const HugeNumber& hn2)
{
	return hn1 + (-hn2);
}

HugeNumber operator+(const HugeNumber& hn1, const HugeNumber& hn2)
{
	HugeNumber HN1 = hn1;
	HugeNumber HN2 = hn2;
	HN1.ChangeOrder();
	HN2.ChangeOrder();

	if (HN1 == (-HN2))
	{
		return HugeNumber();
	}
	if (HN1.sign && HN2.sign)
	{
		return -((-HN1) + (-HN2));
	}
	if (!HN1.sign && HN2.sign && (HN1 < (-HN2)))
	{
		return -((-HN2) - HN1);
	}
	if (HN1.sign && !HN2.sign)
	{
		if (HN2 < (-HN1))
		{
			return -((-HN1) - HN2);
		}
		return HN2 + HN1;
	}

	const int IntPartLength1 = HN1.getIntPartLength();
	const int IntPartLength2 = HN2.getIntPartLength();
	const int FracPartLength1 = HN1.getFracPartLength();
	const int FracPartLength2 = HN2.getFracPartLength();
	const int extraIntZerosLength = abs(IntPartLength1 - IntPartLength2);
	const int extraFracZerosLength = abs(FracPartLength1 - FracPartLength2);

	for (int i = 0; i < extraIntZerosLength; i++)
	{
		if (IntPartLength1 < IntPartLength2)
		{
			HN1.mantissa = "0" + HN1.mantissa;
		}
		else
		{
			HN2.mantissa = "0" + HN2.mantissa;
		}
	}
	for (int i = 0; i < extraFracZerosLength; i++)
	{
		if (FracPartLength1 < FracPartLength2)
		{
			HN1.mantissa += "0";
		}
		else
		{
			HN2.mantissa += "0";
		}
	}
	HN1.mantissa = "0" + HN1.mantissa;
	HN2.mantissa = "0" + HN2.mantissa;
	std::reverse(HN1.mantissa.begin(), HN1.mantissa.end());
	std::reverse(HN2.mantissa.begin(), HN2.mantissa.end());
	int indexPoint = HN1.mantissa.find('.');
	HN1.mantissa.erase(indexPoint, 1);
	HN2.mantissa.erase(indexPoint, 1);

	std::string result = "";
	int mind = 0;
	if (!HN2.sign)
	{
		for (int i = 0; i < HN1.mantissa.length(); i++)
		{
			int digit1 = HN1.mantissa[i] - '0';
			int digit2 = HN2.mantissa[i] - '0';
			int resultDigit = digit1 + digit2 + mind;
			result += std::to_string(resultDigit % 10);
			mind = (resultDigit >= 10);
		}
	}
	else
	{
		for (int i = 0; i < HN1.mantissa.length(); i++)
		{
			int digit1 = HN1.mantissa[i] - '0';
			int digit2 = HN2.mantissa[i] - '0';
			int resultDigit = digit1 - digit2 - mind;
			result += std::to_string((resultDigit + 10) % 10);
			mind = (resultDigit < 0);
		}
	}
	result.insert(indexPoint, ".");
	std::reverse(result.begin(), result.end());
	HugeNumber Result(HN1.sign && HN2.sign, result, HN1.order);
	Result.RemoveExtraZeros();
	return Result;
}

HugeNumber operator/(const HugeNumber& hn, const int n)
{
	if (n == 0)
	{
		throw "Division by zero.";
	}
	HugeNumber HN(hn.sign, hn.mantissa + "000000000000000000000000000", hn.order);
	HN.ChangeOrder();
	std::string ans;
	std::string number = HN.mantissa;
	const int indexPoint = HN.getIntPartLength() - (HN.mantissa[0] - '0' < n);
	HN.mantissa.erase(HN.mantissa.find('.'), 1);
	int carry = 0;
	for (int i = 0; i < HN.mantissa.length(); i++)
	{
		long long cur = (HN.mantissa[i] - '0') + carry * 10;
		HN.mantissa[i] = int(cur / n) + '0';
		carry = int(cur % n);
	}
	HN.mantissa.insert(indexPoint, ".");
	if (HN.mantissa[0] == '.')
	{
		HN.mantissa = "0" + HN.mantissa;
	}
	HN.RemoveExtraZeros();
	return HugeNumber(HN.sign != (n < 0), HN.mantissa, HN.order);
}

void HugeNumber::NormalizeNumber()
{
	if (mantissa[0] == '0' && mantissa[1] == '.')
	{
		mantissa.erase(1, 1);
		int oldLength = mantissa.length();
		RemoveExtraZeros();
		int newLength = mantissa.length();
		int delta = oldLength - newLength;
		order -= delta;
		mantissa = "0." + mantissa;
		return;
	}
	int indexPoint = mantissa.find('.');
	mantissa.erase(indexPoint, 1);
	order += indexPoint;
	mantissa = "0." + mantissa;
	RemoveExtraZeros();
}

int HugeNumber::getIntPartLength()
{
	return mantissa.find('.');
}

int HugeNumber::getFracPartLength()
{
	return mantissa.length() - getIntPartLength() - 1;
}