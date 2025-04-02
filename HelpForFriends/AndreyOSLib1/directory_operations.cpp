#include "directory_operations.h"
#include <iostream>
#include <windows.h>

void CreateDirectory(const std::wstring& dirName)
{
    if (CreateDirectory(dirName.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
        std::wcout << L"Каталог создан: " << dirName << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось создать каталог " << dirName << std::endl;
}

void RemoveDirectory(const std::wstring& dirName)
{
    if (RemoveDirectory(dirName.c_str()))
        std::wcout << L"Каталог удален: " << dirName << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось удалить каталог " << dirName << std::endl;
}
