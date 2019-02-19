#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "header.h"

void userMenuInput(bool menuState);
void rulesMenu();

void menu()
{
	bool menuState = false;

	std::cout << "===========================\n"
		<< "|| Welcome to MasterComp ||\n"
		<< "===========================" << std::endl;

	std::cout << std::setw(18) << std::left << "||" << std::setw(10) << std::right << "||\n"
		<< std::setw(8) << std::left << "||" << std::setw(10) << std::left << "1 - Play" << std::setw(10) << std::right << "||\n"
		<< std::setw(8) << std::left << "||" << std::setw(10) << std::left << "2 - Rules" << std::setw(10) << std::right << "||\n"
		<< std::setw(8) << std::left << "||" << std::setw(10) << std::left << "3 - Quit" << std::setw(10) << std::right << "||\n"
		<< std::setw(18) << std::left << "||" << std::setw(10) << std::right << "||\n"
		<< "===========================" << std::endl;

	userMenuInput(menuState);
}

void rulesMenu()
{
	bool menuState = true;
	std::string rulesContent;

	std::cout << "==============================================\n"
		<< "||             MasterComp Rules             ||\n"
		<< "==============================================" << std::endl;
	std::cout << std::setw(23) << std::left << "||" << std::setw(23) << std::right << "||" << std::endl;

	std::ifstream rulesFile;
	rulesFile.open("rules.txt");

	if (rulesFile.is_open())
	{
		while (!rulesFile.eof())
		{
			getline(rulesFile, rulesContent);

			std::cout << std::setw(3) << std::left << "||"
				<< std::setw(40) << std::left << rulesContent
				<< std::setw(3) << std::right << " ||" << std::endl;
		}
	}

	rulesFile.close();

	std::cout << std::setw(23) << std::left << "||" << std::setw(24) << std::right << "||\n"
		<< "==============================================" << std::endl;

	std::cout << "Press anything to return...\n";

	userMenuInput(menuState);
}

void userMenuInput(bool menuState)
{
	int userSelection = 0, resetCount = 0;

	if (!menuState)
	{
		std::cin >> userSelection;
		std::cin.ignore();

		if (userSelection == 1)
			startGame();
		else if (userSelection == 2)
			rulesMenu();
		else if (userSelection == 3)
			throw quitting();
		else
			menu();
	}
	else
	{
		std::cin.ignore();
		menu();
	}
}
