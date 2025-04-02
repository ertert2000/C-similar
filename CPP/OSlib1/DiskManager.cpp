#include "DiskManager.h"

DiskManager::DiskManager() {}

void DiskManager::SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void DiskManager::getDrive()
{
    DWORD drives = GetLogicalDrives();
    
    for (char letter = 'A'; letter <= 'Z'; ++letter)
    	if (drives & (1 << (letter - 'A')))
    		std::cout << letter << ":\\" << std::endl;
}

void DiskManager::help()
{
    std::wcout << L"Usage: [command] [arguments]" << std::endl << std::endl;
    std::wcout << L"Available commands:" << std::endl << std::endl;
    std::wcout << L"getdrive          Show all disks." << std::endl;
    std::wcout << L"getinfo <drive>   Show information about disks." << std::endl;
    std::wcout << L"help              Show this help message." << std::endl;
    std::wcout << L"clear             Clear the console screen." << std::endl;
    std::wcout << L"exit              Exit the program." << std::endl << std::endl;
    std::wcout << L"For more details, type: [command] --help" << std::endl;
}

void DiskManager::getInfoDrive(std::wstring drive)
{
    std::wstring wdrive = std::wstring(drive.begin(), drive.end());

    wchar_t volumeName[MAX_PATH] = { 0 };
    wchar_t fileSystem[MAX_PATH] = { 0 };
    DWORD serialNumber = 0, maxComponentLen = 0, fileSystemFlags = 0;
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

    if (GetVolumeInformationW(wdrive.c_str(), volumeName, MAX_PATH, &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystem, MAX_PATH))
        std::wcout << L"Volume:      " << volumeName << L"\nFile system: " << fileSystem << std::endl;
    else
        std::wcerr << "Failed to get volume information for drive " << drive << std::endl;

    std::wcout << L"-----------------------------" << std::endl;
    UINT driveType = GetDriveTypeW(wdrive.c_str());
    if (driveType == DRIVE_NO_ROOT_DIR) 
    {
        std::wcerr << "Error: Invalid drive " << drive << std::endl;
        return;
    }
    else if (driveType == DRIVE_UNKNOWN)
    {
        std::wcerr << "Error: Unknow drive " << drive << std::endl;
        return;
    }
    else
    {
        if (driveType == DRIVE_REMOVABLE)
            std::wcout << L"Disk is REMOVABLE" << std::endl;
        if (driveType == DRIVE_FIXED)
            std::wcout << L"Disk is fixed" << std::endl;
        if (driveType == DRIVE_REMOTE)
            std::wcout << L"Disk is remote" << std::endl;
        if (driveType == DRIVE_CDROM)
            std::wcout << L"Disk is CD-ROM" << std::endl;
        if (driveType == DRIVE_RAMDISK)
            std::wcout << L"Disk is RAM" << std::endl;
    }
    std::wcout << std::endl;

    if (GetDiskFreeSpaceExW(wdrive.c_str(), &freeBytesAvailable, &totalBytes, &totalFreeBytes))
    {
        double usedSpace = (totalBytes.QuadPart - totalFreeBytes.QuadPart) * 100.0 / totalBytes.QuadPart;
        int barWidth = 30;
        int filled = static_cast<int>(barWidth * usedSpace / 100);

        if (usedSpace < 50)
            SetConsoleColor(10);
        else if (usedSpace < 80)
            SetConsoleColor(14);
        else
            SetConsoleColor(12);

        std::wcout << wdrive << L" [";
        for (int i = 0; i < barWidth; i++)
        {
            if (i < filled)
                std::wcout << L"*";
            else
                std::wcout << L".";
        }
        std::wcout << L"] " << usedSpace << L"% (" << L"Free: " << (totalFreeBytes.QuadPart / (1024 * 1024)) << L" MB)" << std::endl;

        SetConsoleColor(7);
    }
    else
        std::wcerr << "Failed to get disk space info for drive " << drive << std::endl;
}

void DiskManager::handleCommand(const std::wstring& command)
{
    std::wstringstream ss(command);
    std::vector<std::wstring> args;
    std::wstring arg;

    while (ss >> arg)
        args.push_back(arg);

    if (args.empty())
        return;

    if (args[0] == L"getdrive")
        getDrive();
    else if (args[0] == L"getinfo" && args.size() == 2)
        getInfoDrive(args[1]);
    else if (args[0] == L"clear")
        system("cls");
    else if (args[0] == L"help")
        help();
    else if (args[0] == L"exit")
        loopFlag = false;
    else
        std::wcout << L"Unknown command!" << L"For info enter \"help\" " << std::endl;
}

void DiskManager::startShell()
{
    std::wstring input;
    while (loopFlag)
    {
        std::wcout << L"> ";
        std::getline(std::wcin, input);
        handleCommand(input);
    }
    loopFlag = true;
}

DiskManager::~DiskManager() {}

