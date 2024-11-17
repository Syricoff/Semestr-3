#include "DoubleList.h"
#include "FileLogging.h"
#include <sstream>
#include <vector>
#include <string>

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
int Input(std::string message, int min, int max, FileLogging& f1);
void InputDataFromFile(DoubleList* dl, std::string input);
void PrintList(DoubleList* dl, FileLogging& f1);
void InsertInList(DoubleList* dl, FileLogging& f1);
void DeleteFromList(DoubleList* dl, FileLogging& f1);
void ClearList(DoubleList* dl, FileLogging& f1);
void FindElement(DoubleList* dl, FileLogging& f1);
void CheckEmpty(DoubleList* dl, FileLogging& f1);
void GetLength(DoubleList* dl, FileLogging& f1);
void IndividualTask();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	DoubleList* dl = nullptr;
	bool exit = false;
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
	while (!exit)
	{
		if (dl)
		{
			std::stringstream ss;
			ss << *dl;
			outputLog.Logging(ss.str());
		}
		else
		{
			outputLog.Logging("List does not exist.\n");
		}
		std::cout <<
			"--------------------------Меню---------------------------\n" <<
			" 1. Создать список\n" <<
			" 2. Вывести список\n" <<
			" 3. Вставить элемент в список\n" <<
			" 4. Удалить элемент из списка\n" <<
			" 5. Очистить список\n" <<
			" 6. Найти элемент в списке\n" <<
			" 7. Проверить список на пустоту\n" <<
			" 8. Узнать длину списка\n" <<
			" 9. Индивидуальное задание\n" <<
			"10. Удалить список\n" <<
			"11. Открыть error_log.txt\n" <<
			"12. Открыть output_log.txt\n" <<
			"13. Считать данные из input.txt\n" <<
			"14. Выход\n" <<
			"----------------------------------------------------------\n";
		int choice = Input("Выбрать: ", 1, 14, errorLog);
		system("cls");
		switch (choice)
		{
		case CREATE_LIST:
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
			break;

		case PRINT_LIST:
			PrintList(dl, errorLog);
			break;

		case INSERT_IN_LIST:
			InsertInList(dl, errorLog);
			break;

		case DELETE_FROM_LIST:
			DeleteFromList(dl, errorLog);
			break;

		case CLEAR_LIST:
			ClearList(dl, errorLog);
			break;
			
		case FIND_ELEMENT:
			FindElement(dl, errorLog);
			break;

		case CHECK_EMPTY:
			CheckEmpty(dl, errorLog);
			break;

		case GET_LENGTH:
			GetLength(dl, errorLog);
			break;

		case INDIVIDUAL_TASK:
			IndividualTask();
			break;

		case DELETE_LIST:
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
			break;

		case OPEN_ERROR_LOG:
			errorLog.PrintFile();
			break;

		case OPEN_OUTPUT_LOG:
			outputLog.PrintFile();
			break;

		case INPUT_DATA_FROM_FILE:
			if (!dl)
			{
				dl = new DoubleList();
			}
			InputDataFromFile(dl, input);
			break;

		case EXIT:
			exit = true;
			break;
		}
		std::cout << "\n";
		system("pause");
		system("cls");
	}
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

int Input(std::string message, int min, int max, FileLogging& f1)
{
	int number = 0;
	bool correct = false;
	while (!correct)
	{
		std::cout << message;
		std::string input = "";
		std::cin >> input;
		correct = (input[0] == '-' || IsDigit(input[0]));
		for (size_t i = 1; i < input.size(); i++)
		{
			correct = IsDigit(input[i]);
			if (!correct)
			{
				break;
			}
		}
		if (!correct)
		{
			std::cout << "Неккоректная запись числа!\n";
			f1.Logging("Incorrect number entry.\n");
		}
		if (correct && input.size() > std::to_string(INT_MAX).size() - 1)
		{
			correct = false;
			std::cout << "Введенное число выходит из допустимого диапазона!\n";
			f1.Logging("The entered number out of range.\n");
		}
		if (correct)
		{
			number = stoi(input);
			if (min > number || max < number)
			{
				correct = false;
				std::cout << "Введенное число выходит из допустимого диапазона!\n";
				f1.Logging("The entered number out of range.\n");
			}
		}
	}
	return number;
}

void InputDataFromFile(DoubleList* dl, std::string input)
{
	dl->Clear();
	std::cout << input;
	std::fstream fin(input, std::ios::in);
	if (fin.is_open())
	{
		int data;
		while (fin >> data)
		{
			dl->PushBack(data);
		}
	}
	std::cout << "Данные успешно считались!\n";
	fin.close();
}

void PrintList(DoubleList* dl, FileLogging& fl)
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

void InsertInList(DoubleList* dl, FileLogging& fl)
{
	if (dl)
	{
		std::cout << 
			"--------------------------Вставка---------------------------\n" <<
			" 1. Вставить элемент в начало списка\n" <<
			" 2. Вставить элемент в конец списка\n" <<
			" 3. Вставить элемент в список по индексу\n" <<
			" 4. Выйти в главное меню\n" <<
			"-------------------------------------------------------------\n";
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
			std::cout << "Число " << data << " успешно добавлено в позицию с номером " << index << "списка!\n";
			break;

		case 4:
			break;
		}
	}
	else
	{
		std::cout << "Список еще не создан!\n";
		fl.Logging("List does not exist: attempt to add a new element to the list.\n");
	}
}

void DeleteFromList(DoubleList* dl, FileLogging& fl)
{
	if (dl)
	{
		if (dl->IsEmpty())
		{
			std::cout << "Нельзя ничего удалить из пустого списка!\n";
			fl.Logging("List is empty: attempt to remove an element from a list.\n");
		}
		else
		{
			std::cout <<
				"--------------------------Удаление---------------------------\n" <<
				" 1. Удалить первый элемент списка\n" <<
				" 2. Удалить последний элемент списка\n" <<
				" 3. Удалить элемент из списка по индексу\n" <<
				" 4. Выйти в главное меню\n" <<
				"-------------------------------------------------------------\n";
			int subchoice = Input("Выбрать: ", 1, 4, fl);
			int index = 0;
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
				index = Input("Введите индекс элемента для удаления: ", 0, dl->getSize() - 1, fl);
				dl->Remove(index);
				std::cout << "Элемент с индексом " << index << " успешно удалён из списка!\n";
				break;

			case 4:
				break;
			}
		}
	}
	else
	{
		std::cout << "Список еще не создан!\n";
		fl.Logging("List does not exist: attempt to remove an element from a list.\n");
	}
}

void ClearList(DoubleList* dl, FileLogging& fl)
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

void FindElement(DoubleList* dl, FileLogging& fl)
{
	if (dl)
	{
		std::cout <<
			"--------------------------Поиск------------------------------\n" <<
			" 1. Первое вхождение элемента слева\n" <<
			" 2. Первое вхождение элемента справа\n" <<
			" 3. Выйти в главное меню\n" <<
			"-------------------------------------------------------------\n";
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
	else
	{
		std::cout << "Список еще не создан!\n";
		fl.Logging("List does not exist: attempt to find an element in a list.\n");
	}
}

void CheckEmpty(DoubleList* dl, FileLogging& fl)
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

void GetLength(DoubleList* dl, FileLogging& fl)
{
	if (dl)
	{
		std::cout << "Длина списка: " << dl->getSize() << "\n";
	}
	else
	{
		std::cout << "Список еще не создан!\n";
		fl.Logging("List does not exist: attempt to get the lenght of the list.\n");
	}
}

void IndividualTask()
{
	std::string data;
	std::cout << "Введите строку: ";
	std::cin >> data;
	DoubleList* tdl = new DoubleList();
	for (auto i : data)
	{
		tdl->PushBack((int)i);
	}
	DoubleList::Node* curr = tdl->getHead()->next;
	std::vector<DoubleList::Node*> elements;
	for (size_t i = 1; i < tdl->getSize() - 2; i++)
	{
		if (curr->prev->data == curr->next->data)
		{
			curr->data = INT_MAX;
		}
		curr = curr->next;
	}
	if (curr->prev->data == tdl->getHead()->data)
	{
		tdl->getTail()->prev->data = INT_MAX;
	}
	bool exist = true;
	while (exist)
	{
		exist = false;
		curr = tdl->getHead();
		for (size_t i = 0; i < tdl->getSize() - 1; i++)
		{
			if (curr->data == INT_MAX)
			{
				tdl->Remove(i);
				exist = true;
				break;
			}
			curr = curr->next;
		}
	}
	curr = tdl->getHead();
	std::cout << "Результат: ";
	while (curr)
	{
		std::cout << static_cast<char>(curr->data);
		curr = curr->next;
	}
	std::cout << "\n";
	delete tdl;
}