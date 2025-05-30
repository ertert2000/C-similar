#include "Header.h"
#include <iostream>
#include <fstream>
#include <random>
#include <thread>

int main()
{
    HANDLE hMutex = CreateMutexW(nullptr, FALSE, MUTEX_NAME);
    if (!hMutex){std::wcerr << L"Error CreateMutex: " << GetLastError() << std::endl; return 1;}

    HANDLE hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, PAGE_COUNT * PAGE_SIZE, FILE_MAPPING_NAME);
    if (!hMapFile){std::wcerr << L"Error CreateFileMapping: " << GetLastError() << std::endl; return 1;}

    LPVOID pBase = MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
    if (!pBase){ std::wcerr << L"Error MapViewOfFile: " << GetLastError() << std::endl; return 1;}

    VirtualLock(pBase, PAGE_COUNT * PAGE_SIZE);

    std::wstring logFile = L"writer_" + std::to_wstring(GetCurrentProcessId()) + L".log";

    while (true){

        DWORD tickStart = timeGetTime();
        LogToFile(logFile, L"[WAITING] " + std::to_wstring(tickStart));
        WaitForSingleObject(hMutex, INFINITE);

        int page = rand() % PAGE_COUNT;
        char* pageAddr = (char*)pBase + (page * PAGE_SIZE);

        DWORD tickWrite = timeGetTime();
        LogToFile(logFile, L"[WRITING] Page " + std::to_wstring(page) + L" at " + std::to_wstring(tickWrite));
        std::string data = "PID " + std::to_string(GetCurrentProcessId());
        memcpy(pageAddr, data.c_str(), min(data.size(), PAGE_SIZE - 1));
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 1000));

        DWORD tickRelease = timeGetTime();
        LogToFile(logFile, L"[RELEASE] " + std::to_wstring(tickRelease));
        ReleaseMutex(hMutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
