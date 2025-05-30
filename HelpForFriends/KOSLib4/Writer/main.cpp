#include "header.h"
#include <iostream>
#include <fstream>
#include <random>
#include <thread>

HANDLE InitMutex()
{
    HANDLE mutex = CreateMutexW(nullptr, FALSE, SYNC_OBJECT_NAME);
    if (!mutex)
    {
        std::wcerr << L"[InitMutex] Ошибка: " << GetLastError() << std::endl;
    }
    return mutex;
}

HANDLE InitMapping(HANDLE& outHandle, LPVOID& outMemory)
{
    outHandle = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, TOTAL_PAGES * PAGE_SIZE, SHARED_MEMORY_NAME);
    if (!outHandle)
    {
        std::wcerr << L"[InitMapping] Ошибка CreateFileMapping: " << GetLastError() << std::endl;
        return nullptr;
    }

    outMemory = MapViewOfFile(outHandle, FILE_MAP_WRITE, 0, 0, 0);
    if (!outMemory)
    {
        std::wcerr << L"[InitMapping] Ошибка MapViewOfFile: " << GetLastError() << std::endl;
        return nullptr;
    }

    VirtualLock(outMemory, TOTAL_PAGES * PAGE_SIZE);
    return outHandle;
}

void WriteToRandomPage(LPVOID memoryBase, const std::wstring& logFile, std::mt19937& rng)
{
    DWORD tickStart = timeGetTime();
    LogToFile(logFile, L"[WAITING] " + std::to_wstring(tickStart));

    WaitForSingleObject(InitMutex(), INFINITE);

    int pageIndex = rng() % TOTAL_PAGES;
    char* pagePtr = static_cast<char*>(memoryBase) + (pageIndex * PAGE_SIZE);

    DWORD tickWrite = timeGetTime();
    LogToFile(logFile, L"[WRITING] Page " + std::to_wstring(pageIndex) + L" at " + std::to_wstring(tickWrite));

    std::string text = "PID " + std::to_string(GetCurrentProcessId());
    memcpy(pagePtr, text.c_str(), min(text.size(), PAGE_SIZE - 1));

    std::this_thread::sleep_for(std::chrono::milliseconds(500 + rng() % 1000));

    DWORD tickRelease = timeGetTime();
    LogToFile(logFile, L"[RELEASE] " + std::to_wstring(tickRelease));

    ReleaseMutex(InitMutex());
}

int main()
{
    HANDLE mutex = InitMutex();
    if (!mutex) return 1;

    HANDLE mapping;
    LPVOID memory;
    if (!InitMapping(mapping, memory)) return 1;

    std::wstring logFile = L"writer_" + std::to_wstring(GetCurrentProcessId()) + L".log";
    std::mt19937 rng(static_cast<unsigned>(time(nullptr)));

    while (true)
    {
        WriteToRandomPage(memory, logFile, rng);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
