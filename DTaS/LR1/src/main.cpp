#include "CMenu.h"
#include "CMenuItem.h"
#include "DoubleList.h"
#include "FileLogging.h"
#include "MyError.h"
#include <climits>
#include <sstream>
#include <string>
#include <vector>

enum Points
{
    CREATE_LIST = 1,
    PRINT_LIST,
    INSERT_IN_LIST,
    DELETE_FROM_LIST,
    CLEAR_LIST,
    FIND_ELEMENT,
    CHECK_EMPTY,
    GET_LENGTH,
    INDIVIDUAL_TASK,
    DELETE_LIST,
    OPEN_ERROR_LOG,
    OPEN_OUTPUT_LOG,
    INPUT_DATA_FROM_FILE,
    EXIT
};

bool IsDigit(char c);
int Input(std::string message, int min, int max, FileLogging &f1);
void InputDataFromFile(DoubleList *dl, const std::string &input);
void PrintList(DoubleList *dl, FileLogging &fl);
void InsertInList(DoubleList *dl, FileLogging &fl);
void DeleteFromList(DoubleList *dl, FileLogging &fl);
void ClearList(DoubleList *dl, FileLogging &fl);
void FindElement(DoubleList *dl, FileLogging &fl);
void CheckEmpty(DoubleList *dl, FileLogging &fl);
void GetLength(DoubleList *dl, FileLogging &fl);
void IndividualTask(FileLogging &fl);
void WaitForEnter();

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
        std::cout << "\033[2J\033[1;1H";
        run(menu);
    }
}

std::string MyError::m_file = std::string();

int main(int argc, char *argv[])
{
    DoubleList *dl = nullptr;
    std::string error = "error_log.txt";
    std::string output = "output_log.txt";
    std::string input = "input.txt";

    if (argc >= 3)
    {
        input = argv[1];
        output = argv[2];
        error = argv[3];
    }

    FileLogging errorLog(error);
    FileLogging outputLog(output);
    outputLog.Logging("Program is launched.\n");

    CMenuItem menuItems[] = {
        CMenuItem("Создать список", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            if (!dl)
            {
                dl = new DoubleList();
                std::cout << "Список успешно создан!\n";
            }
            else
            {
                std::cout << "Список уже создан!\n";
                errorLog.Logging("List already created: attempt to create a list.\n");
            }
            WaitForEnter();
            return CREATE_LIST; }),
        CMenuItem("Вывести список", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            PrintList(dl, errorLog);
            WaitForEnter();
            return PRINT_LIST; }),
        CMenuItem("Вставить элемент в список", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            InsertInList(dl, errorLog);
            WaitForEnter();
            return INSERT_IN_LIST; }),
        CMenuItem("Удалить элемент из списка", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            DeleteFromList(dl, errorLog);
            WaitForEnter();
            return DELETE_FROM_LIST; }),
        CMenuItem("Очистить список", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            ClearList(dl, errorLog);
            WaitForEnter();
            return CLEAR_LIST; }),
        CMenuItem("Найти элемент в списке", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            FindElement(dl, errorLog);
            WaitForEnter();
            return FIND_ELEMENT; }),
        CMenuItem("Проверить список на пустоту", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            CheckEmpty(dl, errorLog);
            WaitForEnter();
            return CHECK_EMPTY; }),
        CMenuItem("Узнать длину списка", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            GetLength(dl, errorLog);
            WaitForEnter();
            return GET_LENGTH; }),
        CMenuItem("Индивидуальное задание", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            IndividualTask(errorLog);
            WaitForEnter();
            return INDIVIDUAL_TASK; }),
        CMenuItem("Удалить список", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            if (!dl)
            {
                std::cout << "Список еще не создан!\n";
                errorLog.Logging("List does not exist: attempt to delete list.\n");
            }
            else
            {
                delete dl;
                dl = nullptr;
                std::cout << "Список успешно удален!\n";
            }
            WaitForEnter();
            return DELETE_LIST; }),
        CMenuItem("Открыть error_log.txt", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            errorLog.PrintFile();
            WaitForEnter();
            return OPEN_ERROR_LOG; }),
        CMenuItem("Открыть output_log.txt", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            outputLog.PrintFile();
            WaitForEnter();
            return OPEN_OUTPUT_LOG; }),
        CMenuItem("Считать данные из input.txt", [&]()
                  {
            std::cout << "\033[2J\033[1;1H";
            if (!dl)
            {
                dl = new DoubleList();
            }
            InputDataFromFile(dl, input);
            WaitForEnter();
            return INPUT_DATA_FROM_FILE; }),
        CMenuItem("Выход", [&]()
                  { return 0; })};

    CMenu menu("Меню", menuItems, sizeof(menuItems) / sizeof(CMenuItem));
    run(menu);

    if (dl)
    {
        delete dl;
    }
    return 0;
}

bool IsDigit(char c)
{
    return '0' <= c && c <= '9';
}

int Input(std::string message, int min, int max, FileLogging &f1)
{
    int number = 0;
    bool correct = false;
    while (!correct)
    {
        std::cout << message;
        std::string input;
        std::cin >> input;
        correct = (input[0] == '-' || IsDigit(input[0]));

        for (size_t i = 1; i < input.size(); i++)
        {
            if (!IsDigit(input[i]))
            {
                correct = false;
                break;
            }
        }

        if (!correct)
        {
            std::cout << "Некорректная запись числа!\n";
            f1.Logging("Incorrect number entry.\n");
            continue;
        }

        if (input.size() > std::to_string(INT_MAX).size() - 1)
        {
            correct = false;
            std::cout << "Введенное число выходит из допустимого диапазона!\n";
            f1.Logging("The entered number out of range.\n");
            continue;
        }

        number = stoi(input);
        if (min > number || max < number)
        {
            correct = false;
            std::cout << "Введенное число выходит из допустимого диапазона!\n";
            f1.Logging("The entered number out of range.\n");
        }
    }
    return number;
}

void InputDataFromFile(DoubleList *dl, const std::string &input)
{
    dl->Clear();
    std::ifstream fin(input);
    if (fin.is_open())
    {
        int data;
        while (fin >> data)
        {
            dl->PushBack(data);
        }
        std::cout << "Данные успешно считались!\n";
    }
    else
    {
        std::cout << "Не удалось открыть файл: " << input << "\n";
    }
}

void PrintList(DoubleList *dl, FileLogging &fl)
{
    if (dl)
    {
        dl->PrintDoubleList();
    }
    else
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to print list.\n");
    }
}

void WaitForEnter()
{
    std::cout << "Нажмите Enter, чтобы продолжить...";
    std::cin.clear();
    std::cin.ignore(1024, '\n');
    std::cin.get();
}

void InsertInList(DoubleList *dl, FileLogging &fl)
{
    if (!dl)
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to add a new element to the list.\n");
        return;
    }

    std::cout << "--------------------------Вставка---------------------------\n"
              << " 1. Вставить элемент в начало списка\n"
              << " 2. Вставить элемент в конец списка\n"
              << " 3. Вставить элемент в список по индексу\n"
              << " 4. Выйти в главное меню\n"
              << "-------------------------------------------------------------\n";

    int subchoice = Input("Выбрать: ", 1, 4, fl);
    int data = 0;
    int index = 0;

    switch (subchoice)
    {
    case 1:
        data = Input("Введите число для вставки: ", INT_MIN, INT_MAX, fl);
        dl->PushFront(data);
        std::cout << "Число " << data << " успешно добавлено в начало списка!\n";
        break;

    case 2:
        data = Input("Введите число для вставки: ", INT_MIN, INT_MAX, fl);
        dl->PushBack(data);
        std::cout << "Число " << data << " успешно добавлено в конец списка!\n";
        break;

    case 3:
        data = Input("Введите число для вставки: ", INT_MIN, INT_MAX, fl);
        index = Input("Введите индекс элемента для вставки: ", 0, dl->getSize(), fl);
        dl->Insert(index, data);
        std::cout << "Число " << data << " успешно добавлено в позицию с номером " << index << " списка!\n";
        break;

    case 4:
        break;
    }
}

void DeleteFromList(DoubleList *dl, FileLogging &fl)
{
    if (!dl)
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to remove an element from a list.\n");
        return;
    }

    if (dl->IsEmpty())
    {
        std::cout << "Нельзя ничего удалить из пустого списка!\n";
        fl.Logging("List is empty: attempt to remove an element from a list.\n");
        return;
    }

    std::cout << "--------------------------Удаление---------------------------\n"
              << " 1. Удалить первый элемент списка\n"
              << " 2. Удалить последний элемент списка\n"
              << " 3. Удалить элемент из списка по индексу\n"
              << " 4. Выйти в главное меню\n"
              << "-------------------------------------------------------------\n";

    int subchoice = Input("Выбрать: ", 1, 4, fl);

    switch (subchoice)
    {
    case 1:
        dl->PopFront();
        std::cout << "Первый элемент успешно удалён!\n";
        break;

    case 2:
        dl->PopBack();
        std::cout << "Последний элемент успешно удалён!\n";
        break;

    case 3:
        int index = Input("Введите индекс элемента для удаления: ", 0, dl->getSize() - 1, fl);
        dl->Remove(index);
        std::cout << "Элемент с индексом " << index << " успешно удалён из списка!\n";
        break;
    }
}

void ClearList(DoubleList *dl, FileLogging &fl)
{
    if (dl)
    {
        dl->Clear();
        std::cout << "Список успешно очищен!\n";
    }
    else
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: trying to clear the list.\n");
    }
}

void FindElement(DoubleList *dl, FileLogging &fl)
{
    if (!dl)
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to find an element in a list.\n");
        return;
    }

    std::cout << "--------------------------Поиск------------------------------\n"
              << " 1. Первое вхождение элемента слева\n"
              << " 2. Первое вхождение элемента справа\n"
              << " 3. Выйти в главное меню\n"
              << "-------------------------------------------------------------\n";

    int subchoice = Input("Выбрать: ", 1, 3, fl);
    int data = 0;

    switch (subchoice)
    {
    case 1:
        data = Input("Введите число для поиска: ", INT_MIN, INT_MAX, fl);
        std::cout << "Индекс этого элемента: " << dl->FindElement(data) << "\n";
        break;

    case 2:
        data = Input("Введите число для поиска: ", INT_MIN, INT_MAX, fl);
        std::cout << "Индекс этого элемента: " << dl->RFindElement(data) << "\n";
        break;

    case 3:
        break;
    }
}

void CheckEmpty(DoubleList *dl, FileLogging &fl)
{
    if (dl)
    {
        std::cout << "Список пуст: " << (dl->IsEmpty() ? "да" : "нет") << "\n";
    }
    else
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to check if the list is empty.\n");
    }
}

void GetLength(DoubleList *dl, FileLogging &fl)
{
    if (dl)
    {
        std::cout << "Длина списка: " << dl->getSize() << "\n";
    }
    else
    {
        std::cout << "Список еще не создан!\n";
        fl.Logging("List does not exist: attempt to get the length of the list.\n");
    }
}

void IndividualTask(FileLogging &fl)
{
    std::string input;
    DoubleList *list = new DoubleList();

    while (true)
    {
        std::cout << "Введите последовательность латинских букв, оканчивающуюся точкой: ";
        std::cin >> input;

        bool validInput = true;
        for (char c : input)
        {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '#' || c == '.'))
            {
                validInput = false;
                break;
            }
        }

        if (!validInput)
        {
            std::cout << "Ошибка: ввод должен содержать только латинские буквы, '#' и '.'\n";
            fl.Logging("The input must contain only Latin letters, '#' and '.'\n");
            continue;
        }

        for (char c : input)
        {
            if (c == '.')
            {
                break;
            }
            else if (c == '#')
            {
                list->PopBack();
            }
            else
            {
                list->PushBack(c);
            }
        }
        DoubleList::Node *curr = list->getHead();
        while (curr)
        {
            std::cout << char(curr->data);
            curr = curr->next;
        }
        std::cout << std::endl;
        break;
    }
}
