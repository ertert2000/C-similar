#pragma once
#include <windows.h>
#include <string>

const wchar_t* FILE_MAPPING_NAME = L"Global\MySharedMemory";
const wchar_t* MUTEX_NAME = L"Global\PageMutex";
const size_t PAGE_SIZE = 4096;
const int PAGE_COUNT = 14;
const size_t META_SIZE = PAGE_COUNT;
const size_t TOTAL_SIZE = META_SIZE + PAGE_COUNT * PAGE_SIZE;

inline void LogToFile(const std::wstring& filename, const std::wstring& message)
{
    FILE* f;
    _wfopen_s(&f, filename.c_str(), L"a+");
    if (f)
    {
        fwprintf(f, L"%s\n", message.c_str());
        fclose(f);
    }
}