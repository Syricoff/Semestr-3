#ifndef MENU
#define MENU
#include <iostream>
#include <string>
#include <any>
#include <vector>
#include <functional>
#include <conio.h>
#include "ConsoleEditor.h"

class Menu
{
public:
	using Func = std::function<void(std::vector<std::any>)>;

	Menu(std::string label, Func function);
	Menu(std::string label, std::vector<Menu> menus);
	Menu(std::string label, Func function, std::vector<std::any> params);
	Menu(std::string label, std::vector<Menu> menus, std::vector<std::any> params);
	Menu(const Menu& menu);


	void Run(std::vector<std::any> params);
	void PrintMenu(size_t selected = 1);
	void changeMenu(size_t old_selected, size_t new_selected);
	void setSelectedItemColor(int selectedItemColor);

private:
	enum Buttons
	{
		ARROW = 224,
		UP = 80,
		DOWN = 72,
		ESC = 27,
		ENTER = 13
	};
	int selectedItemColor = BACKGROUND_GREEN;
	std::string label{};
	std::vector<Menu> menus{};
	Func func{};
	std::vector<std::any> params{};
};
#endif