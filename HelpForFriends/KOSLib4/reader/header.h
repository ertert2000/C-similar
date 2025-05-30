#pragma once
#include <windows.h>
#include <string>

const wchar_t* SHARED_MEMORY_NAME = L"Global\\CustomSharedMem";
const wchar_t* SYNC_OBJECT_NAME = L"Global\\AccessMutex";

const size_t PAGE_SIZE = 4096;
const int TOTAL_PAGES = 12;

inline void LogToFile(const std::wstring& filepath, const std::wstring& entry)
{
    FILE* file;
    _wfopen_s(&file, filepath.c_str(), L"a+");
    if (file)
    {
        fwprintf(file, L"%s\n", entry.c_str());
        fclose(file);
    }
}

