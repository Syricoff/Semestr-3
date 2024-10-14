#include "BinTree.h"
#include "CMenu.h"
#include "CMenuItem.h"
#include "MyError.h"
#include "Tools.h"
#include <cmath>
#include <fstream>
#include <iostream>
 
// TODO: Поработать над работой меню, проверить парвильность добавления и вывода значений, глянуть как работает вывод по рядам

std::string ExpressionTree::MyError::m_file = std::string();

using namespace ExpressionTree;

BinTree tree; // Переименованный класс
int argc2;
char **argv2;

#pragma region
int PrintTree()
{
    СlearScreen();
    if (!tree.IsEmpty())
    { // Использование функции проверки на пустоту
        tree.PrintTree();
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    WaitForEnter();
    return 1;
}

int PrintLevelOrder()
{
    СlearScreen();
    if (!tree.IsEmpty())
    { // Использование функции проверки на пустоту
        tree.LevelOrderTraversal();
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    WaitForEnter();
    return 2;
}

int ClearTree()
{
    СlearScreen();
    if (!tree.IsEmpty())
    { // Использование функции проверки на пустоту
        tree.Clear();
        std::cout << "Дерево успешно удалено.\n";
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    WaitForEnter();
    return 3;
}

int RemoveNegative()
{
    СlearScreen();
    if (!tree.IsEmpty())
    { // Использование функции проверки на пустоту
        tree.RemoveNegative();
        std::cout << "Отрицательные элементы удалены.\n";
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    WaitForEnter();
    return 4;
}

int PrintFile()
{
    СlearScreen();
    if (!tree.IsEmpty())
    {
        std::string filename = (argc2 >= 3) ? argv2[2] : "output.txt";
        tree.WriteToFile(filename);
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    WaitForEnter();
    return 5;
}

int Exit()
{
    std::cout << std::endl
              << "Выход из программы" << std::endl;
    return 0;
}
#pragma endregion

const int items_number = 6;
void run(CMenu menu)
{
    try
    {
        while (menu.runCommand())
        {
        }
    }
    catch (const MyError &exception)
    {
        std::cout << "Error: " << exception.getError() << std::endl;
        WaitForEnter();
        СlearScreen();
        run(menu);
    }
}

void ReadFile(const std::string &nameFile = "input.txt")
{
    std::ifstream in(nameFile);
    int number;

    if (!tree.IsEmpty())
    {
        tree.Clear(); // Очистка дерева перед загрузкой новых данных
    }

    if (!in.is_open())
    {
        throw MyError{"File didn't open"};
    }

    while (in >> number)
    {
        tree.Insert(number); // Вставка чисел в дерево
    }
    in.close();
    std::cout << "Данные были импортированы из файла" << std::endl;

    if (tree.IsEmpty())
    {
        throw MyError{"Нет данных для создания дерева"};
    }
}

int main(int argc, char *argv[])
{
    argc2 = argc;
    argv2 = argv;

    try
    {
        MyError::m_file = (argc >= 4) ? std::string(argv[3]) : "exceptions.txt";

        if (argc >= 2)
        {
            ReadFile(argv[1]);
            WaitForEnter();
        }
        else
        {
            ReadFile();
            std::cout << "Используются файлы по умолчанию input.txt, output.txt, exceptions.txt\n";
            WaitForEnter();
        }
    }
    catch (const MyError &exception)
    {
        std::cout << "Error: " << exception.getError() << std::endl;
        WaitForEnter();
        СlearScreen();
    }

    CMenuItem items[items_number]{
        CMenuItem{"Распечатать дерево", PrintTree},
        CMenuItem{"Вывод дерева по уровням", PrintLevelOrder},
        CMenuItem{"Удаление дерева", ClearTree},
        CMenuItem{"Удаление отрицательных элементов", RemoveNegative},
        CMenuItem{"Вывод в файл", PrintFile},
        CMenuItem{"Выход", Exit}};

    CMenu menu("Дерево выражения", items, items_number);
    run(menu);
    return 0;
}
