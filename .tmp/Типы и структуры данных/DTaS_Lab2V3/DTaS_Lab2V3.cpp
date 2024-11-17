#include <iostream>
#include <cmath>
#include "CMenu.h"
#include "CMenuItem.h"
#include "ExpTree.h"
#include "MyError.h"
#include <fstream>
std::string ExpressionTree::MyError::m_file = std::string();

using namespace ExpressionTree;

ExpTree tree;
std::fstream inp;
std::fstream out;
std::fstream excp;
float task_result = 0;
int argc2;
char** argv2;

#pragma region 
int PrintTree()
{
    system("cls");
    if (tree.getCountElement() != 0)
    {
        std::cout << tree.infixExp;
        tree.printTree();
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    system("pause");
    return 1;
}

int PreOrder()
{
    system("cls");
    tree.preorder_printing();
    system("pause");
    return 2;

}
int InOrder()
{
    system("cls");
    tree.inorder_printing();
    system("pause");
    return 3;
}

int PostOrder()
{
    system("cls");
    tree.postorder_printing();
    system("pause");
    return 4;
}
int ClearTree()
{
    system("cls");
    if (tree.getCountElement() != 0)
    {
        tree.clearTree();
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    system("pause");
    return 5;
}
int PrintFile()
{
    system("cls");
    if (tree.getCountElement() != 0)
    {
        if (argc2 >= 3)
        {
            tree.WriteFile(argv2[2]);
        }
        else
        {
            tree.WriteFile("output.txt");
        }
    }
    else
    {
        std::cout << "Дерево пустое\n";
    }
    system("pause");
    return 6;
}


int Exit()
{
    std::cout << std::endl << "Выход из программы" << std::endl;
    return 0;
}

#pragma endregion

const int items_number = 7;
void run(CMenu menu)
{
    try
    {
        while (menu.runCommand()) {}

    }
    catch (const MyError& exception)
    {
        std::cout << "Error: " << exception.getError() << std::endl;
        system("pause");
        system("cls");
        run(menu);
    }

}

void ReadFile(std::string nameFile = "input.txt")
{
    std::ifstream in;
    std::string line;
    char data;
    if (tree.getCountElement() != 0)
    {
        tree.clearTree();
    }
    in.open(nameFile, std::ios::in);
    if (!in.is_open())
    {
        throw MyError{ "File didn't open" };
    }
    else
    {
        while (in >> data && !in.eof())
        {
            line.push_back(data);
        }
        in.close();
        std::cout << "Данные были импортированы из файла" << std::endl;
    }
    if (tree.IsExpCorrect(line))
    {
        tree.constructTree(line);
    }
    else
    {
        throw MyError{ "Incorrect expression" };
    }

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    argc2 = argc;
    argv2 = argv;
    try
    {
        if (argc >= 4)
        {

            MyError::m_file = std::string(argv[3]);
        }
        else
        {
            MyError::m_file = std::string("exceptions.txt");
        }
        if (argc >= 2)
        {
            ReadFile(argv[1]);
            system("pause");
        }
        else
        {

            ReadFile();
            std::cout << "Используются файлы по умолчанию input.txt, output.txt, exceptions.txt\n";
            system("pause");

        }



    }
    catch (const MyError& exception)
    {
        std::cout << "Error: " << exception.getError() << std::endl;
        system("pause");
        system("cls");
    }

    CMenuItem items[items_number]{
            CMenuItem{"Распечатать дерево", PrintTree},
            CMenuItem{"Префиксная запись", PreOrder},
            CMenuItem{"Инфиксная запись", InOrder},
            CMenuItem{"Постфиксная запись", PostOrder},
            CMenuItem{"Удаление дерева", ClearTree},
            CMenuItem{"Вывод в файл", PrintFile},
             CMenuItem{"Выход", Exit}
    };
    CMenu menu("Дерево выражения", items, items_number);

    run(menu);
    return 0;
}