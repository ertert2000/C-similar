#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <unordered_map>

class FileManager
{
protected:
	std::wstring currentPath;

    bool loopFlag = true;

    void setPath(const std::wstring& path);

    void createDirectory(const std::wstring& dirName);

    void removeFile(const std::wstring& file);

    void removeDirectory(const std::wstring& dirName);

    void createFile(const std::wstring& fileName);

    void copyFile(const std::wstring& srcFile, const std::wstring& destFile);

    void moveFile(const std::wstring& srcFile, const std::wstring& destFile);

    void printFileAttributes(const std::wstring& fileName, bool flag = true);

    void listFilesWithAttributes(const std::wstring& directoryPath);

    void getFileInfo(const std::wstring& fileName);

    void help();

    void listFiles();

    void printFileTime(const FILETIME& fileTime);

    void showFileTime(const std::wstring& fileName);

    void setTimeFile(const std::wstring& fileName, const std::wstring& time, const std::wstring& select);

    void setFileAttributes(const std::wstring& fileName, const std::wstring& attr);

    std::vector<std::wstring> parseCommand(const std::wstring& command);

    void handleCommand(const std::wstring& command);
public:
    FileManager();

    void startShell();

	~FileManager();
};

