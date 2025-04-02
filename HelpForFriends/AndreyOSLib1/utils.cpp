#include "utils.h"

void PrintFileTime(const FILETIME& fileTime)
{
    SYSTEMTIME systemTime;
    FileTimeToSystemTime(&fileTime, &systemTime);

    std::wcout << systemTime.wYear << L"." << systemTime.wMonth << L"." << systemTime.wDay << L" " << systemTime.wHour << L":" << systemTime.wMinute << L":" << systemTime.wSecond << std::endl;
}