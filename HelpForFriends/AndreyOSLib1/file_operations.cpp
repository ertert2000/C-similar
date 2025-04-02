#include "file_operations.h"

void PrintFileAttributes(const std::wstring& fileName, bool flag)
{
    DWORD attributes = GetFileAttributes(fileName.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        std::wcout << std::setw(30) << std::left << fileName << L" | Ошибка чтения атрибутов" << std::endl;
        return;
    }

    std::wstring attr;
    if (attributes & FILE_ATTRIBUTE_READONLY) attr += L"Т ";
    if (attributes & FILE_ATTRIBUTE_HIDDEN) attr += L"С ";
    if (attributes & FILE_ATTRIBUTE_SYSTEM) attr += L"С ";
    if (attributes & FILE_ATTRIBUTE_DIRECTORY) attr += L"К ";
    if (attributes & FILE_ATTRIBUTE_ARCHIVE) attr += L"А ";
    if (attributes & FILE_ATTRIBUTE_DEVICE) attr += L"УСТ ";
    if (attributes & FILE_ATTRIBUTE_NORMAL) attr += L"НОРМ ";
    if (attributes & FILE_ATTRIBUTE_TEMPORARY) attr += L"ВРЕМ ";
    if (attributes & FILE_ATTRIBUTE_SPARSE_FILE) attr += L"РАЗР ";
    if (attributes & FILE_ATTRIBUTE_REPARSE_POINT) attr += L"ПЕРЕ ";
    if (attributes & FILE_ATTRIBUTE_COMPRESSED) attr += L"СЖАТ ";
    if (attributes & FILE_ATTRIBUTE_OFFLINE) attr += L"ОФФЛ ";
    if (attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) attr += L"НЕИНД ";
    if (attributes & FILE_ATTRIBUTE_ENCRYPTED) attr += L"ШИФР ";

    if (flag)
    {
        std::wcout << std::setw(30) << std::left << L"Имя файла" << L" | Атрибуты" << std::endl;
        std::wcout << std::wstring(50, L'-') << std::endl;
    }
    std::wcout << std::setw(30) << std::left << fileName << L" | " << attr << std::endl;
}

void GetFileInfo(const std::wstring& fileName)
{
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Ошибка: не удалось открыть файл " << fileName << std::endl;
        return;
    }

    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (GetFileInformationByHandle(hFile, &fileInfo))
    {
        std::wcout << L"Информация о файле: " << fileName << std::endl;
        std::wcout << L"Размер файла: " << ((static_cast<ULONGLONG>(fileInfo.nFileSizeHigh) << 32) | fileInfo.nFileSizeLow) << L" байт" << std::endl;
        std::wcout << L"Количество ссылок: " << fileInfo.nNumberOfLinks << std::endl;
        std::wcout << L"Серийный номер тома: " << fileInfo.dwVolumeSerialNumber << std::endl;
        std::wcout << L"Индекс файла: " << fileInfo.nFileIndexHigh << L"-" << fileInfo.nFileIndexLow << std::endl;
    }
    else
        std::wcerr << L"Ошибка: не удалось получить информацию о файле." << std::endl;

    CloseHandle(hFile);
}

void CopyFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    if (CopyFile(srcFile.c_str(), destFile.c_str(), FALSE))
        std::wcout << L"Файл скопирован: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось скопировать " << srcFile << std::endl;
}

void MoveFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    if (MoveFile(srcFile.c_str(), destFile.c_str()))
        std::wcout << L"Файл перемещен: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось переместить " << srcFile << std::endl;
}

void ShowFileTime(const std::wstring& fileName)
{
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    FILETIME creationTime, accessTime, writeTime;
    if (GetFileTime(hFile, &creationTime, &accessTime, &writeTime))
    {
        std::wcout << L"Время создания: ";
        PrintFileTime(creationTime);
        std::wcout << L"Время доступа: ";
        PrintFileTime(accessTime);
        std::wcout << L"Время записи: ";
        PrintFileTime(writeTime);
    }
    else
        std::wcerr << L"Ошибка\n";

    CloseHandle(hFile);
}

void SetFileTime(const std::wstring& fileName, const std::wstring& time, const std::wstring& select)
{
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Ошибка открытия файла\n";
        return;
    }

    FILETIME ft;
    SYSTEMTIME st = {};

    std::wstringstream ss(time);
    wchar_t delimiter;
    ss >> st.wYear >> delimiter >> st.wMonth >> delimiter >> st.wDay >> st.wHour >> delimiter >> st.wMinute >> delimiter >> st.wSecond;
    st.wMilliseconds = 0;

    if (!SystemTimeToFileTime(&st, &ft))
    {
        std::cerr << "Ошибка преобразования времени\n";
        CloseHandle(hFile);
        return;
    }

    if (select == L"w")
    {
        if (SetFileTime(hFile, NULL, NULL, &ft))
            std::wcout << L"Время последней модификации успешно изменено!\n";
        else
            std::cerr << "Ошибка изменения времени\n";
    }
    else if (select == L"a")
    {
        if (SetFileTime(hFile, NULL, &ft, NULL))
            std::wcout << L"Время последнего доступа успешно изменено!\n";
        else
            std::cerr << "Ошибка изменения времени\n";
    }
    else
    {
        if (SetFileTime(hFile, &ft, NULL, NULL))
            std::wcout << L"Время создания успешно изменено!\n";
        else
            std::cerr << "Ошибка изменения времени\n";
    }

    CloseHandle(hFile);
}

void SetFileAttribute(std::wstring fileName, DWORD attributes)
{
    if (SetFileAttributesW(fileName.c_str(), attributes))
        std::cout << "Атрибуты успешно изменены!" << std::endl;
    else
        std::cerr << "Ошибка: " << GetLastError() << std::endl;
}