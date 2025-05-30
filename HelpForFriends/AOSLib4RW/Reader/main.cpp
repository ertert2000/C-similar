#include "Header.h"
#include <iostream>
#include <fstream>
#include <random>
#include <thread>

int main()
{
    HANDLE hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    if (!hMutex){std::wcerr << L"Error OpenMutex: " << GetLastError() << std::endl;return 1;}

    HANDLE hMapFile = OpenFileMappingW(FILE_MAP_READ, FALSE, FILE_MAPPING_NAME);
    if (!hMapFile){std::wcerr << L"Error OpenFileMapping: " << GetLastError() << std::endl;return 1;}

    LPVOID pBase = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
    if (!pBase){std::wcerr << L"Error MapViewOfFile: " << GetLastError() << std::endl;return 1;}

    VirtualLock(pBase, PAGE_COUNT * PAGE_SIZE);

    std::wstring logFile = L"reader_" + std::to_wstring(GetCurrentProcessId()) + L".log";

    while (true){
        DWORD tickStart = timeGetTime();
        LogToFile(logFile, L"[WAITING] " + std::to_wstring(tickStart));
        WaitForSingleObject(hMutex, INFINITE);

        int page = rand() % PAGE_COUNT;
        char* pageAddr = (char*)pBase + (page * PAGE_SIZE);

        DWORD tickRead = timeGetTime();
        LogToFile(logFile, L"[READING] Page " + std::to_wstring(page) + L" at " + std::to_wstring(tickRead));
        std::string readData(pageAddr, pageAddr + strnlen_s(pageAddr, PAGE_SIZE));
        std::wcout << L"[" << GetCurrentProcessId() << L"] Прочитал с страницы " << page << L": " << std::wstring(readData.begin(), readData.end()) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 1000));

        DWORD tickRelease = timeGetTime();
        LogToFile(logFile, L"[RELEASE] " + std::to_wstring(tickRelease));
        ReleaseMutex(hMutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
