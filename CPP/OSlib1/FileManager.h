#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


class FileManager
{
protected:
	std::wstring currentPath;

    bool loopFlag = true;

    void setPath(const std::wstring& path);

    void createDirectory(const std::wstring& dirName);

    void removeDirectory(const std::wstring& dirName);

    void createFile(const std::wstring& fileName);

    void copyFile(const std::wstring& srcFile, const std::wstring& destFile);

    void moveFile(const std::wstring& srcFile, const std::wstring& destFile);

    void printFileAttributes(const std::wstring& fileName);

    void listFilesWithAttributes(const std::wstring& directoryPath);

    void getFileInfo(const std::wstring& fileName);

    void help();

    void listFiles();

    void handleCommand(const std::wstring& command);
public:
    FileManager();

    void startShell();

	~FileManager();
};

