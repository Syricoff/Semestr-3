#include "Menu.h"

Menu::Menu(std::string label, Func func) :
	label(label), func(func)
{}

Menu::Menu(std::string label, std::vector<Menu> menus) :
	label(label), menus(menus)
{}

Menu::Menu(std::string label, Func func, std::vector<std::any> params) :
	label(label), func(func), params(params)
{}

Menu::Menu(std::string label, std::vector<Menu> menus, std::vector<std::any> params) :
	label(label), menus(menus), params(params)
{}

Menu::Menu(const Menu& menu)
{
	label = menu.label;
	menus = menu.menus;
	func = menu.func;
	params = menu.params;
}

void Menu::setSelectedItemColor(int selectedItemColor)
{
	this->selectedItemColor = selectedItemColor;
}

void Menu::PrintMenu(size_t selected)
{
	HideCursor();
	if (!func)
	{
		std::cout << "Меню '" << label << "'\n";
	}
	for (size_t i = 0; i < menus.size(); i++)
	{
		if (i + 1 == selected)
		{
			setConsoleColor(selectedItemColor);
		}
		std::cout << i + 1 << ". " << menus[i].label;
		setConsoleColor();
		std::cout << std::endl;
	}
	if (!func)
	{
		std::cout << "Нажмите ESC для выхода из '" << label << "'\n";
	}
}

// для оптимизации отрисовки меню
void Menu::changeMenu(size_t old_selected, size_t new_selected)
{
	HideCursor();
	setConsoleCoordinates(0, old_selected);
	std::cout << old_selected << ". " << menus[old_selected - 1].label;
	setConsoleCoordinates(0, new_selected);
	setConsoleColor(selectedItemColor);
	std::cout << new_selected << ". " << menus[new_selected - 1].label;
	setConsoleColor();
}

void Menu::Run(std::vector<std::any> params)
{
	bool exit = false;
	while (!exit)
	{
		system("cls");
		PrintMenu();
		int select = 1;
		if (!func)
		{
			int key = 0;
			int old_select = 0;
			while (key != ENTER && key != ESC)
			{
				int oldWidth = getConsoleWidth();
				int oldHeight = getConsoleHeight();
				// Нажатие на стрелку вверх(вниз) генерирует два события
				// с кодом ARROW=224 и с кодом UP=80(DOWN=72)
				key = ARROW;
				while (key == ARROW)
				{
					while (!_kbhit())
					{
						int newWidth = getConsoleWidth();
						int newHeight = getConsoleHeight();
						// Если размеры консоли изменяются,
						// то перерисовываем,
						// иначе будет цветная полоса во всю строку
						if (oldWidth != newWidth || oldHeight != newHeight)
						{
							system("cls");
							PrintMenu(select);
							oldWidth = newWidth;
							oldHeight = newHeight;
						}
					}
					key = _getch();
				}
				old_select = select;
				switch (key)
				{
				case UP:
					select = (select >= menus.size() ? 1 : select + 1);
					changeMenu(old_select, select);
					break;
				case DOWN:
					select = (select <= 1 ? menus.size() : select - 1);
					changeMenu(old_select, select);
					break;
				case ESC:
					select = 0;
					exit = true;
					setConsoleCoordinates(0, menus.size() + 2);
					break;
				default:
					break;
				}
			}
			if (select == 0)
			{
				exit = true;
			}
			else
			{
				menus[select - 1].Run(params);
			}
		}
		else
		{
			func(params);
			system("pause");
			exit = true;
		}
	}
}