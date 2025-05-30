#include "header.h"
#include <iostream>
#include <fstream>
#include <random>
#include <thread>

HANDLE GetExistingMutex()
{
    HANDLE mutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, SYNC_OBJECT_NAME);
    if (!mutex)
    {
        std::wcerr << L"[GetExistingMutex] Ошибка: " << GetLastError() << std::endl;
    }
    return mutex;
}

HANDLE GetSharedMemory(LPVOID& outPtr)
{
    HANDLE mappingHandle = OpenFileMappingW(FILE_MAP_READ, FALSE, SHARED_MEMORY_NAME);
    if (!mappingHandle)
    {
        std::wcerr << L"[GetSharedMemory] Ошибка OpenFileMapping: " << GetLastError() << std::endl;
        return nullptr;
    }

    outPtr = MapViewOfFile(mappingHandle, FILE_MAP_READ, 0, 0, 0);
    if (!outPtr)
    {
        std::wcerr << L"[GetSharedMemory] Ошибка MapViewOfFile: " << GetLastError() << std::endl;
        return nullptr;
    }

    VirtualLock(outPtr, TOTAL_PAGES * PAGE_SIZE);
    return mappingHandle;
}

void ReadRandomPage(LPVOID memoryBase, const std::wstring& logFile, std::mt19937& rng)
{
    DWORD tickBeforeWait = timeGetTime();
    LogToFile(logFile, L"[WAITING] " + std::to_wstring(tickBeforeWait));

    HANDLE mutex = GetExistingMutex();
    WaitForSingleObject(mutex, INFINITE);

    int pageIndex = rng() % TOTAL_PAGES;
    const char* page = static_cast<char*>(memoryBase) + (pageIndex * PAGE_SIZE);

    DWORD tickRead = timeGetTime();
    LogToFile(logFile, L"[READING] Page " + std::to_wstring(pageIndex) + L" at " + std::to_wstring(tickRead));

    std::string content(page, page + strnlen_s(page, PAGE_SIZE));
    std::wcout << L"[" << GetCurrentProcessId() << L"] Чтение страницы " << pageIndex << L": "
        << std::wstring(content.begin(), content.end()) << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500 + rng() % 1000));

    DWORD tickUnlock = timeGetTime();
    LogToFile(logFile, L"[RELEASE] " + std::to_wstring(tickUnlock));

    ReleaseMutex(mutex);
}

int main()
{
    HANDLE mutex = GetExistingMutex();
    if (!mutex) return 1;

    HANDLE mapping;
    LPVOID sharedMemory;
    if (!GetSharedMemory(sharedMemory)) return 1;

    std::wstring logPath = L"reader_" + std::to_wstring(GetCurrentProcessId()) + L".log";
    std::mt19937 generator(static_cast<unsigned>(time(nullptr)));

    while (true)
    {
        ReadRandomPage(sharedMemory, logPath, generator);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
