#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

void createDirectory(const std::wstring& dirName);

void removeDirectory(const std::wstring& dirName);

void createFile(const std::wstring& fileName);

void copyFile(const std::wstring& srcFile, const std::wstring& destFile);

void moveFile(const std::wstring& srcFile, const std::wstring& destFile);

void setFileTime(const std::wstring& fileName, const std::wstring& time, int select);

void printFileAttributes(const std::wstring& fileName);

void displayDrives();

void displayDriveDetails(const std::wstring& driveLetter);

void showFileTime(const std::wstring& fileName);

void SetFileAttribute(std::wstring fileName);

void displayMenu();


int main() {
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale());

    int choice, input3;
    std::wstring input, input2;

    do {
        system("cls");
        displayMenu();
        std::wcin >> choice;
        std::wcin.ignore();

        switch (choice) {
        case 1: system("cls"); displayDrives(); system("pause"); break;
        case 2: system("cls"); std::wcout << L"Enter drive letter (e.g., C:\\): "; std::getline(std::wcin, input); displayDriveDetails(input); system("pause"); break;
        case 3: system("cls"); std::wcout << L"Enter directory name: "; std::getline(std::wcin, input); createDirectory(input); system("pause"); break;
        case 4: system("cls"); std::wcout << L"Enter directory name: "; std::getline(std::wcin, input); removeDirectory(input); system("pause"); break;
        case 5: system("cls"); std::wcout << L"Enter file name: "; std::getline(std::wcin, input); createFile(input); system("pause"); break;
        case 6: system("cls"); std::wcout << L"Enter source file name: "; std::getline(std::wcin, input); std::wcout << L"Enter destination file name: "; std::getline(std::wcin, input2); copyFile(input, input2); system("pause"); break;
        case 7: system("cls"); std::wcout << L"Enter source file name: "; std::getline(std::wcin, input); std::wcout << L"Enter destination file name: "; std::getline(std::wcin, input2); moveFile(input, input2); system("pause"); break;
        case 8: system("cls"); std::wcout << L"Enter file name: "; std::getline(std::wcin, input); printFileAttributes(input); system("pause"); break;
        case 9: system("cls"); std::wcout << L"Enter file name: "; std::getline(std::wcin, input); showFileTime(input); system("pause"); break;
        case 10: system("cls"); std::wcout << L"Enter file name: "; std::getline(std::wcin, input); std::wcout << L"Enter time: "; std::getline(std::wcin, input2); std::wcout << L"1 - write, 2 - acces, 3 - create: "; std::wcin >> input3; setFileTime(input, input2, input3); system("pause"); break;
        case 11: system("cls"); std::wcout << L"Enter file name: "; std::getline(std::wcin, input); SetFileAttribute(input); system("pause"); break;
        case 0: break;
        default: std::wcerr << L"Invalid option!" << std::endl; system("pause"); break;
        }
    } while (choice != 0);

    return 0;
}

void createDirectory(const std::wstring& dirName) {
    if (CreateDirectory(dirName.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        std::wcout << L"Directory created: " << dirName << std::endl;
    }
    else {
        std::wcerr << L"Failed to create directory: " << dirName << std::endl;
    }
}

void removeDirectory(const std::wstring& dirName) {
    if (RemoveDirectory(dirName.c_str())) {
        std::wcout << L"Directory removed: " << dirName << std::endl;
    }
    else {
        std::wcerr << L"Failed to remove directory: " << dirName << std::endl;
    }
}

void createFile(const std::wstring& fileName) {
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        std::wcout << L"File created: " << fileName << std::endl;
    }
    else {
        std::wcerr << L"Failed to create file: " << fileName << std::endl;
    }
}

void copyFile(const std::wstring& srcFile, const std::wstring& destFile) {
    if (CopyFile(srcFile.c_str(), destFile.c_str(), FALSE)) {
        std::wcout << L"File copied: " << srcFile << L" to " << destFile << std::endl;
    }
    else {
        std::wcerr << L"Failed to copy file: " << srcFile << std::endl;
    }
}

void moveFile(const std::wstring& srcFile, const std::wstring& destFile) {
    if (MoveFile(srcFile.c_str(), destFile.c_str())) {
        std::wcout << L"File moved: " << srcFile << L" to " << destFile << std::endl;
    }
    else {
        std::wcerr << L"Failed to move file: " << srcFile << std::endl;
    }
}

void setFileTime(const std::wstring& fileName, const std::wstring& time, int select)
{
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    FILETIME ft;
    SYSTEMTIME st = {};

    std::wstringstream ss(time);
    wchar_t delimiter;
    ss >> st.wYear >> delimiter >> st.wMonth >> delimiter >> st.wDay >> st.wHour >> delimiter >> st.wMinute >> delimiter >> st.wSecond;
    st.wMilliseconds = 0;

    if (!SystemTimeToFileTime(&st, &ft))
    {
        std::cerr << "Time transformation error\n";
        CloseHandle(hFile);
        return;
    }

    if (select == 1)
    {
        if (SetFileTime(hFile, NULL, NULL, &ft)) {
            std::wcout << L"The time of the last modification has been successfully changed!\n";
        }
        else {
            std::cerr << "Time changes error\n";
        }
    }
    else if (select == 2)
    {
        if (SetFileTime(hFile, NULL, &ft, NULL)) {
            std::wcout << L"The last access time has been successfully changed!\n";
        }
        else {
            std::cerr << "Time changes error\n";
        }
    }
    else
    {
        if (SetFileTime(hFile, &ft, NULL, NULL)) {
            std::wcout << L"The time of creation has been successfully changed!\n";
        }
        else {
            std::cerr << "Time changes error\n";
        }
    }

    CloseHandle(hFile);
}

void printFileAttributes(const std::wstring& fileName) {
    DWORD attributes = GetFileAttributes(fileName.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        std::wcerr << L"Failed to read attributes for file " << fileName << std::endl;
        return;
    }

    std::wstring attr;
    if (attributes & FILE_ATTRIBUTE_READONLY)  attr += L"Read-Only ";
    if (attributes & FILE_ATTRIBUTE_HIDDEN)    attr += L"Hidden ";
    if (attributes & FILE_ATTRIBUTE_SYSTEM)    attr += L"System ";
    if (attributes & FILE_ATTRIBUTE_DIRECTORY) attr += L"Directory ";
    if (attributes & FILE_ATTRIBUTE_ARCHIVE)   attr += L"Archive ";
    if (attributes & FILE_ATTRIBUTE_DEVICE)    attr += L"Device ";
    if (attributes & FILE_ATTRIBUTE_NORMAL)    attr += L"Normal ";
    if (attributes & FILE_ATTRIBUTE_TEMPORARY) attr += L"Temporary ";

    std::wcout << std::setw(30) << std::left << fileName << L" | " << attr << std::endl;
}

void displayDrives() {
    DWORD availableDrives = GetLogicalDrives();
    for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter) {
        if (availableDrives & (1 << (driveLetter - 'A'))) {
            std::wcout << driveLetter << L":\\\n";
        }
    }
}

void displayDriveDetails(const std::wstring& driveLetter) {
    std::wstring drivePath = driveLetter + L"\\";
    wchar_t volumeLabel[MAX_PATH] = { 0 };
    wchar_t fsType[MAX_PATH] = { 0 };
    DWORD serialNum = 0, maxComponentLen = 0, fsFlags = 0;
    ULARGE_INTEGER freeSpace, totalSpace, freeTotal;

    if (GetVolumeInformation(drivePath.c_str(), volumeLabel, MAX_PATH, &serialNum, &maxComponentLen, &fsFlags, fsType, MAX_PATH)) {
        std::wcout << L"Volume: " << volumeLabel << L"\nFile System: " << fsType << std::endl;
    }
    else {
        std::wcerr << L"Failed to retrieve information for " << driveLetter << std::endl;
    }

    UINT driveType = GetDriveType(drivePath.c_str());
    switch (driveType) {
    case DRIVE_NO_ROOT_DIR: std::wcerr << L"Error: Invalid drive\n"; return;
    case DRIVE_UNKNOWN:     std::wcerr << L"Error: Unknown drive\n"; return;
    case DRIVE_REMOVABLE:   std::wcout << L"Removable Drive\n";      break;
    case DRIVE_FIXED:       std::wcout << L"Fixed Drive\n";          break;
    case DRIVE_REMOTE:      std::wcout << L"Remote Drive\n";         break;
    case DRIVE_CDROM:       std::wcout << L"CD-ROM Drive\n";         break;
    case DRIVE_RAMDISK:     std::wcout << L"RAM Disk\n";             break;
    default:                std::wcerr << L"Unknown Drive Type\n";   break;
    }

    if (GetDiskFreeSpaceEx(drivePath.c_str(), &freeSpace, &totalSpace, &freeTotal)) {
        std::wcout << L"Free space: " << (freeTotal.QuadPart / (1024 * 1024)) << L" MB" << std::endl;
    }
    else {
        std::wcerr << L"Failed to retrieve free space for " << driveLetter << std::endl;
    }
}

void showFileTime(const std::wstring& fileName) {
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    FILETIME creationTime, accessTime, writeTime;
    if (GetFileTime(hFile, &creationTime, &accessTime, &writeTime)) {
        SYSTEMTIME sysTime;
        FileTimeToSystemTime(&creationTime, &sysTime);
        std::wcout << L"Creation Time: " << sysTime.wYear << L"-" << sysTime.wMonth << L"-" << sysTime.wDay << L" " << sysTime.wHour << L":" << sysTime.wMinute << L":" << sysTime.wSecond << std::endl;
        FileTimeToSystemTime(&accessTime, &sysTime);
        std::wcout << L"Access Time: " << sysTime.wYear << L"-" << sysTime.wMonth << L"-" << sysTime.wDay << L" " << sysTime.wHour << L":" << sysTime.wMinute << L":" << sysTime.wSecond << std::endl;
        FileTimeToSystemTime(&writeTime, &sysTime);
        std::wcout << L"Write Time: " << sysTime.wYear << L"-" << sysTime.wMonth << L"-" << sysTime.wDay << L" " << sysTime.wHour << L":" << sysTime.wMinute << L":" << sysTime.wSecond << std::endl;
    }
    else {
        std::wcerr << L"Failed to retrieve file times for " << fileName << std::endl;
    }
    CloseHandle(hFile);
}

void SetFileAttribute(std::wstring fileName)
{
    bool flag = true;
    DWORD attributes = 0;
    char attributesChoise;
    std::wcout << L"Select attributes:\n"
        L"1 - Only for reading\n"
        L"2 - Hidden\n"
        L"3 - Systemic\n"
        L"4 - Archival\n"
        L"5 - A regular file (reset of other attributes)\n"
        L"Enter numbers (0 - complete): ";

    std::cin >> attributesChoise;
    do{
        switch (attributesChoise) {
        case '1': attributes |= FILE_ATTRIBUTE_READONLY; break;
        case '2': attributes |= FILE_ATTRIBUTE_HIDDEN; break;
        case '3': attributes |= FILE_ATTRIBUTE_SYSTEM; break;
        case '4': attributes |= FILE_ATTRIBUTE_ARCHIVE; break;
        case '5': attributes = FILE_ATTRIBUTE_NORMAL; break;
        case '0': if (SetFileAttributesW(fileName.c_str(), attributes)) std::wcout << L"Attributes are successfully changed!\n"; else std::wcerr << L"Error: " << GetLastError() << std::endl; return;
        default: std::wcout << L"Incredible input!\n"; break;
        }
    } while (std::cin >> attributesChoise );

    
}

void displayMenu() {
    std::wcout << L"#==========================#\n";
    std::wcout << L"1 - List all drives\n";
    std::wcout << L"2 - Show drive info\n";
    std::wcout << L"3 - Create directory\n";
    std::wcout << L"4 - Remove directory\n";
    std::wcout << L"5 - Create file\n";
    std::wcout << L"6 - Copy file\n";
    std::wcout << L"7 - Move file\n";
    std::wcout << L"8 - Show file attributes\n";
    std::wcout << L"9 - Show file info\n";
    std::wcout << L"10 - Set file time\n";
    std::wcout << L"11 - Set file attributes\n";
    std::wcout << L"0 - Exit\n";
    std::wcout << L"#==========================#\n";
    std::wcout << L"Choice: ";
}