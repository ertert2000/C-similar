#include "Menu.h"


Menu::Menu()
{
	diskManager = DiskManager();
	fileManager = FileManager();
}

void Menu::tableOfContents()
{
	std::wcout << L"#=======Select Mode========#" << std::endl;
	std::wcout << L"1 - Drive manager" << std::endl;
	std::wcout << L"2 - File manager" << std::endl;
	std::wcout << L"3 - Exit" << std::endl;
	std::wcout << L"#==========================#" << std::endl;
}

bool Menu::mainMenu()
{
	int choice;

	system("cls");

	tableOfContents();

	if (firstFlag)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		firstFlag = true;
	}
	std::cin >> choice;

	system("cls");
	switch (choice)
	{
	case 1:
		diskManager.startShell();
		break;
	case 2:
		fileManager.startShell();
		break;
	case 3:
		return false;
		break;
	default:
		break;
	}

}
