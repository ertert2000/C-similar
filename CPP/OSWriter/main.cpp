#include "shared.h"
#include <iostream>
#include <fstream>
#include <random>
#include <thread>

int main()
{
    HANDLE hMutex = CreateMutexW(nullptr, FALSE, MUTEX_NAME);
    if (!hMutex)
    {
        std::wcerr << L"Ошибка CreateMutex: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, TOTAL_SIZE, FILE_MAPPING_NAME);
    if (!hMapFile)
    {
        std::wcerr << L"Ошибка CreateFileMapping: " << GetLastError() << std::endl;
        return 1;
    }

    LPVOID pBase = MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
    if (!pBase)
    {
        std::wcerr << L"Ошибка MapViewOfFile: " << GetLastError() << std::endl;
        return 1;
    }

    VirtualLock(pBase, TOTAL_SIZE);

    BYTE* meta = (BYTE*)pBase;
    char* dataBase = (char*)pBase + META_SIZE;

    std::wstring logFile = L"writer_" + std::to_wstring(GetCurrentProcessId()) + L".log";

    int lastPage = 0;

    while (true)
    {
        DWORD tickStart = timeGetTime();
        LogToFile(logFile, L"[WAITING] " + std::to_wstring(tickStart));

        WaitForSingleObject(hMutex, INFINITE);

        int page = -1;
        for (int i = 0; i < PAGE_COUNT; ++i)
        {
            int candidate = (lastPage + i) % PAGE_COUNT;
            if (meta[candidate] == 0)
            {
                page = candidate;
                meta[page] = 1;
                lastPage = (page + 1) % PAGE_COUNT;
                break;
            }
        }

        if (page == -1)
        {
            ReleaseMutex(hMutex);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        char* pageAddr = dataBase + (page * PAGE_SIZE);

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
