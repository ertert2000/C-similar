#include "drive_operations.h"
#include <iostream>
#include <windows.h>

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

    if (GetVolumeInformation(wdrive.c_str(), volumeName, MAX_PATH, &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystem, MAX_PATH))
        std::wcout << L"Том: " << volumeName << L"\nФайловая система: " << fileSystem << std::endl;
    else
        std::wcerr << L"Не удалось получить информацию о томе для диска " << drive << std::endl;

    std::wcout << L"-----------------------------" << std::endl;
    UINT driveType = GetDriveType(wdrive.c_str());
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

    if (GetDiskFreeSpaceEx(wdrive.c_str(), &freeBytesAvailable, &totalBytes, &totalFreeBytes))
        std::wcout << L"Свободно: " << (totalFreeBytes.QuadPart / (1024 * 1024)) << L" МБ" << std::endl;
    else
        std::wcerr << L"Не удалось получить информацию о свободном месте на диске " << drive << std::endl;
}
