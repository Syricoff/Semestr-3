#include <iostream>
#include <limits>
#include "Tools.h"



#ifdef _WIN32
#include <windows.h>
#endif

void СlearScreen() {
#ifdef _WIN32
    // Очистка экрана для Windows
    system("cls");
#else
    // Очистка экрана для Linux/Unix
    system("clear");
#endif
}

void WaitForEnter()
{
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Ожидание ввода
}