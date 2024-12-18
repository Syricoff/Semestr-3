#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define MAX_DIGITS 30
#define BASE 10

struct LongNumber
{
    bool is_negative;        // Знак числа
    std::vector<int> digits; // Цифры числа
    int exponent;            // Экспонента

    LongNumber() : is_negative(false), exponent(0) {}

    void readNumber(const std::string &input)
    {
        size_t e_pos = input.find('E');
        if (e_pos == std::string::npos)
        {
            throw std::invalid_argument("Invalid format: missing 'E'");
        }

        std::string mantissa = input.substr(0, e_pos);
        std::string exponent_str = input.substr(e_pos + 1);

        // Определение знака экспоненты
        bool exp_negative = false;
        if (exponent_str[0] == '-')
        {
            exp_negative = true;
            exponent_str = exponent_str.substr(1);
        }
        else if (exponent_str[0] == '+')
        {
            exponent_str = exponent_str.substr(1);
        }

        exponent = std::stoi(exponent_str);
        if (exp_negative)
        {
            exponent = -exponent;
        }

        is_negative = (mantissa[0] == '-');
        if (is_negative || mantissa[0] == '+')
            mantissa = mantissa.substr(1);

        size_t dot_pos = mantissa.find('.');
        if (dot_pos != std::string::npos)
        {
            exponent -= (mantissa.size() - dot_pos - 1);
            mantissa.erase(dot_pos, 1);
        }

        digits.clear();
        for (char c : mantissa)
        {
            if (isdigit(c))
            {
                digits.push_back(c - '0');
            }
            else
            {
                throw std::invalid_argument("Invalid character in number");
            }
        }

        if (digits.size() > MAX_DIGITS)
        {
            digits.resize(MAX_DIGITS);
        }
    }

    LongNumber square() const
    {
        LongNumber result;
        result.is_negative = false;

        std::vector<int> temp_digits(2 * digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i)
        {
            for (size_t j = 0; j < digits.size(); ++j)
            {
                temp_digits[i + j] += digits[i] * digits[j];
                if (temp_digits[i + j] >= BASE)
                {
                    temp_digits[i + j + 1] += temp_digits[i + j] / BASE;
                    temp_digits[i + j] %= BASE;
                }
            }
        }

        // Удаляем лишние нули в конце
        while (temp_digits.size() > 1 && temp_digits.back() == 0)
        {
            temp_digits.pop_back();
        }

        // Сохраняем результат
        result.digits.assign(temp_digits.begin(), temp_digits.begin() + std::min(MAX_DIGITS, int(temp_digits.size())));
        result.exponent = 2 * exponent;

        return result;
    }

    void printNumber() const
    {
        if (is_negative)
            std::cout << "-";
        std::cout << "0.";
        for (size_t i = 0; i < digits.size(); ++i)
        {
            std::cout << digits[i];
        }
        std::cout << " E " << exponent << std::endl;
    }
};

int main()
{
    LongNumber num;
    std::string input;

    std::cout << "Введите число в формате (zn)0.m E N: ";
    std::cin >> input;

    try
    {
        num.readNumber(input);        
        LongNumber result = num.square(); 
        result.printNumber();           
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
