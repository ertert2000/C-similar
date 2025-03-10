#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

bool loopFlag = true;

void SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ListDrives()
{
    DWORD drives = GetLogicalDrives();

    for (char letter = 'A'; letter <= 'Z'; ++letter)
        if (drives & (1 << (letter - 'A')))
            std::wcout << letter << L":\\" << std::endl;
}

void ShowDriveInfo(const std::wstring& drive)
{
    std::wstring wdrive = std::wstring(drive.begin(), drive.end());

    wchar_t volumeName[MAX_PATH] = { 0 };
    wchar_t fileSystem[MAX_PATH] = { 0 };
    DWORD serialNumber = 0, maxComponentLen = 0, fileSystemFlags = 0;
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

    if (GetVolumeInformationW(wdrive.c_str(), volumeName, MAX_PATH, &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystem, MAX_PATH))
        std::wcout << L"Том: " << volumeName << L"\nФайловая система: " << fileSystem << std::endl;
    else
        std::wcerr << L"Не удалось получить информацию о томе для диска " << drive << std::endl;

    std::wcout << L"-----------------------------" << std::endl;
    UINT driveType = GetDriveTypeW(wdrive.c_str());
    if (driveType == DRIVE_NO_ROOT_DIR)
    {
        std::wcerr << L"Ошибка: Неверный диск " << drive << std::endl;
        return;
    }
    else if (driveType == DRIVE_UNKNOWN)
    {
        std::wcerr << L"Ошибка: Неизвестный диск " << drive << std::endl;
        return;
    }
    else
    {
        if (driveType == DRIVE_REMOVABLE)
            std::wcout << L"Диск СЪЕМНЫЙ" << std::endl;
        if (driveType == DRIVE_FIXED)
            std::wcout << L"Диск ФИКСИРОВАННЫЙ" << std::endl;
        if (driveType == DRIVE_REMOTE)
            std::wcout << L"Диск УДАЛЕННЫЙ" << std::endl;
        if (driveType == DRIVE_CDROM)
            std::wcout << L"Диск CD-ROM" << std::endl;
        if (driveType == DRIVE_RAMDISK)
            std::wcout << L"Диск RAMDISK" << std::endl;
    }
    std::wcout << std::endl;

    if (GetDiskFreeSpaceExW(wdrive.c_str(), &freeBytesAvailable, &totalBytes, &totalFreeBytes))
    {
        double usedSpace = (totalBytes.QuadPart - totalFreeBytes.QuadPart) * 100.0 / totalBytes.QuadPart;
        int barWidth = 30;
        int filled = static_cast<int>(barWidth * usedSpace / 100);

        if (usedSpace < 50)
            SetConsoleColor(10);  // Зеленый
        else if (usedSpace < 80)
            SetConsoleColor(14);  // Желтый
        else
            SetConsoleColor(12);  // Красный

        std::wcout << wdrive << L" [";
        for (int i = 0; i < barWidth; i++)
        {
            if (i < filled)
                std::wcout << L"*";
            else
                std::wcout << L".";
        }
        std::wcout << L"] " << usedSpace << L"% (" << L"Свободно: " << (totalFreeBytes.QuadPart / (1024 * 1024)) << L" МБ)" << std::endl;

        SetConsoleColor(7);  // По умолчанию
    }
    else
        std::wcerr << L"Не удалось получить информацию о свободном месте на диске " << drive << std::endl;
}

void CreateDirectory(const std::wstring& dirName)
{
    std::wstring fullPath = dirName;
    if (CreateDirectoryW(fullPath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
        std::wcout << L"Каталог создан: " << fullPath << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось создать каталог " << fullPath << std::endl;
}

void RemoveDirectory(const std::wstring& dirName)
{
    std::wstring fullPath = dirName;
    if (RemoveDirectoryW(fullPath.c_str()))
        std::wcout << L"Каталог удален: " << fullPath << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось удалить каталог " << fullPath << std::endl;
}

void CreateFile(const std::wstring& fileName)
{
    std::wstring fullPath = fileName;
    HANDLE hFile = CreateFileW(fullPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        std::wcout << L"Файл создан: " << fullPath << std::endl;
    }
    else
        std::wcerr << L"Ошибка: не удалось создать файл " << fullPath << std::endl;
}

void CopyFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    std::wstring srcPath = srcFile;
    std::wstring destPath = destFile;
    if (CopyFileW(srcPath.c_str(), destPath.c_str(), FALSE))
        std::wcout << L"Файл скопирован: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось скопировать " << srcFile << std::endl;
}

void MoveFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    std::wstring srcPath = srcFile;
    std::wstring destPath = destFile;
    if (MoveFileW(srcPath.c_str(), destPath.c_str()))
        std::wcout << L"Файл перемещен: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Ошибка: не удалось переместить " << srcFile << std::endl;
}

void PrintFileAttributes(const std::wstring& fileName, bool flag = false)
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

void ListFilesWithAttributes(const std::wstring& directoryPath)
{
    bool flag = true;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directoryPath + L"\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Ошибка открытия каталога: " << directoryPath << std::endl;
        return;
    }

    do
    {
        PrintFileAttributes(directoryPath + L"\\" + findFileData.cFileName, flag);
        flag = false;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void GetFileInfo(const std::wstring& fileName)
{
    std::wstring fullPath = fileName;
    HANDLE hFile = CreateFileW(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Ошибка: не удалось открыть файл " << fullPath << std::endl;
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

void PrintFileTime(const FILETIME& fileTime)
{
    SYSTEMTIME systemTime;
    FileTimeToSystemTime(&fileTime, &systemTime);

    std::wcout << systemTime.wYear << L"." << systemTime.wMonth << L"." << systemTime.wDay << L" " << systemTime.wHour << L":" << systemTime.wMinute << L":" << systemTime.wSecond << std::endl;
}

void ShowFileTime(const std::wstring& fileName)
{
    std::wstring searchPath = fileName;

    HANDLE hFile = CreateFile(searchPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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
    std::wstring filename = fileName;

    HANDLE hFile = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

    if (select == L"-w")
    {
        if (SetFileTime(hFile, NULL, NULL, &ft))
            std::wcout << L"Время последней модификации успешно изменено!\n";
        else
            std::cerr << "Ошибка изменения времени\n";
    }
    else if (select == L"-a")
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

void ShowMenu()
{
    std::wcout << L"\nМеню:\n";
    std::wcout << L"1. Показать все диски\n";
    std::wcout << L"2. Показать информацию о диске\n";
    std::wcout << L"3. Создать каталог\n";
    std::wcout << L"4. Удалить каталог\n";
    std::wcout << L"5. Создать файл\n";
    std::wcout << L"6. Скопировать файл\n";
    std::wcout << L"7. Переместить файл\n";
    std::wcout << L"8. Показать атрибуты файла\n";
    std::wcout << L"9. Показать файлы с атрибутами\n";
    std::wcout << L"10. Показать информацию о файле\n";
    std::wcout << L"11. Показать время файла\n";
    std::wcout << L"12. Установить время файла\n";
    std::wcout << L"0. Выход\n";
    std::wcout << L"Выберите опцию: ";
}

int main()
{
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());

    std::wcout << L"Добро пожаловать в менеджер дисков и файлов!" << std::endl;

    int choice;
    std::wstring input, input2, input3;

    do
    {
        ShowMenu();
        std::wcin >> choice;
        std::wcin.ignore();

        switch (choice)
        {
        case 1:
            ListDrives();
            break;
        case 2:
            std::wcout << L"Введите букву диска (например, C:\\): ";
            std::getline(std::wcin, input);
            ShowDriveInfo(input);
            break;
        case 3:
            std::wcout << L"Введите имя каталога: ";
            std::getline(std::wcin, input);
            CreateDirectory(input);
            break;
        case 4:
            std::wcout << L"Введите имя каталога: ";
            std::getline(std::wcin, input);
            RemoveDirectory(input);
            break;
        case 5:
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            CreateFile(input);
            break;
        case 6:
            std::wcout << L"Введите исходное имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите имя файла назначения: ";
            std::getline(std::wcin, input2);
            CopyFile(input, input2);
            break;
        case 7:
            std::wcout << L"Введите исходное имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите имя файла назначения: ";
            std::getline(std::wcin, input2);
            MoveFile(input, input2);
            break;
        case 8:
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            PrintFileAttributes(input, true);
            break;
        case 9:
            std::wcout << L"Введите путь к каталогу: ";
            std::getline(std::wcin, input);
            ListFilesWithAttributes(input);
            break;
        case 10:
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            GetFileInfo(input);
            break;
        case 11:
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            ShowFileTime(input);
            break;
        case 12:
            std::wcout << L"Введите имя файла: ";
            std::getline(std::wcin, input);
            std::wcout << L"Введите время (гггг-мм-дд чч:мм:сс): ";
            std::getline(std::wcin, input2);
            std::wcout << L"Выберите тип времени (-c для создания, -a для доступа, -w для записи): ";
            std::getline(std::wcin, input3);
            SetFileTime(input, input2, input3);
            break;
        case 0:
            std::wcout << L"Выход из программы." << std::endl;
            break;
        default:
            std::wcout << L"Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
