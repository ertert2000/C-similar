#pragma once

#include <iostream>
#include <limits>
#include <Windows.h>
#include "DiskManager.h"
#include "FileManager.h"

class Menu
{
protected:
	DiskManager diskManager;
	FileManager fileManager;

	bool firstFlag = false;

	//void info();

	void tableOfContents();
public:
	Menu();

	bool mainMenu();

	//~Menu();
};

