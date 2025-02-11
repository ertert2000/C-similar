#pragma once

#include <iostream>
#include <Windows.h>
#include <execution>
#include <vector>
#include <sstream>

class DiskManager
{
protected:
	bool loopFlag = true;

	void SetConsoleColor(int color);

	void getDrive();

	void help();

	void getInfoDrive(std::wstring drive);

	void handleCommand(const std::wstring& command);

public:
	DiskManager();

	void startShell();

	~DiskManager();
};

