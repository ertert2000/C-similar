#include "FileManager.h"

FileManager::FileManager()
{
    wchar_t buffer[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, buffer);
    currentPath = buffer;
}

FileManager::~FileManager() {}

void FileManager::setPath(const std::wstring& path)
{
    if (path.length() == 2 && path[1] == L':' && iswalpha(path[0])) 
    {
        std::wstring newDrive = path + L"\\";

        if (SetCurrentDirectoryW(newDrive.c_str()))
            currentPath = newDrive;
        else
            std::wcerr << L"Error: Unable to change to drive " << path << std::endl;

        return;
    }

    if (path == L"..") 
    {
        size_t pos = currentPath.find_last_of(L"\\/");

        if (pos != std::wstring::npos)
            currentPath = currentPath.substr(0, pos);
        if (!SetCurrentDirectoryW(currentPath.c_str()))
            std::wcerr << L"Error: Unable to change directory to " << currentPath << std::endl;

        return;
    }

    std::wstring newPath = currentPath + L"\\" + path;

    if (SetCurrentDirectoryW(newPath.c_str()))
        currentPath = newPath;
    else
        std::wcerr << L"Error: Unable to change directory to " << newPath << std::endl;
}

void FileManager::createDirectory(const std::wstring& dirName)
{
    std::wstring fullPath = currentPath + L"\\" + dirName;
    if (CreateDirectoryW(fullPath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
        std::wcout << L"The catalog was created: " << fullPath << std::endl;
    else
        std::wcerr << L"Error: failed to create a catalog " << fullPath << std::endl;
}

void FileManager::removeDirectory(const std::wstring& dirName)
{
    std::wstring fullPath = currentPath + L"\\" + dirName;
    if (RemoveDirectoryW(fullPath.c_str()))
        std::wcout << L"The catalog is deleted: " << fullPath << std::endl;
    else
        std::wcerr << L"Error: failed to remove the catalog " << fullPath << std::endl;
}

void FileManager::createFile(const std::wstring& fileName)
{
    std::wstring fullPath = currentPath + L"\\" + fileName;
    HANDLE hFile = CreateFileW(fullPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        std::wcout << L"The file is created: " << fullPath << std::endl;
    }
    else
        std::wcerr << L"Error: failed to create a file " << fullPath << std::endl;
}

void FileManager::copyFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    std::wstring srcPath = currentPath + L"\\" + srcFile;
    std::wstring destPath = currentPath + L"\\" + destFile; //тут по пути надо разобраться
    if (CopyFileW(srcPath.c_str(), destPath.c_str(), FALSE))
        std::wcout << L"The file is copied: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Error: failed to copy " << srcFile << std::endl;
}

void FileManager::moveFile(const std::wstring& srcFile, const std::wstring& destFile)
{
    std::wstring srcPath = currentPath + L"\\" + srcFile;
    std::wstring destPath = currentPath + L"\\" + destFile; //тут по пути надо разобраться
    if (MoveFileW(srcPath.c_str(), destPath.c_str()))
        std::wcout << L"The file moved: " << srcFile << L" -> " << destFile << std::endl;
    else
        std::wcerr << L"Error: failed to move " << srcFile << std::endl;
}

void FileManager::printFileAttributes(const std::wstring& fileName, bool flag)
{
    DWORD attributes = GetFileAttributes(fileName.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) 
    {
        std::wcout << std::setw(30) << std::left << fileName << L" | Error reading attributes" << std::endl;
        return;
    }

    std::wstring attr;
    if (attributes & FILE_ATTRIBUTE_READONLY) attr += L"R ";
    if (attributes & FILE_ATTRIBUTE_HIDDEN) attr += L"H ";
    if (attributes & FILE_ATTRIBUTE_SYSTEM) attr += L"S ";
    if (attributes & FILE_ATTRIBUTE_DIRECTORY) attr += L"D ";
    if (attributes & FILE_ATTRIBUTE_ARCHIVE) attr += L"A ";
    if (attributes & FILE_ATTRIBUTE_DEVICE) attr += L"DEV ";
    if (attributes & FILE_ATTRIBUTE_NORMAL) attr += L"NORM ";
    if (attributes & FILE_ATTRIBUTE_TEMPORARY) attr += L"TEMP ";
    if (attributes & FILE_ATTRIBUTE_SPARSE_FILE) attr += L"SPARSE ";
    if (attributes & FILE_ATTRIBUTE_REPARSE_POINT) attr += L"REPARSE ";
    if (attributes & FILE_ATTRIBUTE_COMPRESSED) attr += L"COMP ";
    if (attributes & FILE_ATTRIBUTE_OFFLINE) attr += L"OFFLINE ";
    if (attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) attr += L"NOINDEX ";
    if (attributes & FILE_ATTRIBUTE_ENCRYPTED) attr += L"ENC ";

    if (flag)
    {
        std::wcout << std::setw(30) << std::left << L"File Name" << L" | Attributes" << std::endl;
        std::wcout << std::wstring(50, L'-') << std::endl;
    }
    std::wcout << std::setw(30) << std::left << fileName << L" | " << attr << std::endl;
}

void FileManager::listFilesWithAttributes(const std::wstring& directoryPath)
{
    bool flag = true;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directoryPath + L"\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) 
    {
        std::wcerr << L"Error opening directory: " << directoryPath << std::endl;
        return;
    }

    do
    {
        printFileAttributes(directoryPath + L"\\" + findFileData.cFileName, flag);
        flag = false;
    }
    while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void FileManager::getFileInfo(const std::wstring& fileName)
{
    std::wstring fullPath = currentPath + L"\\" + fileName;
    HANDLE hFile = CreateFileW(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Error: Unable to open file " << fullPath << std::endl;
        return;
    }

    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (GetFileInformationByHandle(hFile, &fileInfo)) // table
    {
        std::wcout << L"File Information for: " << fileName << std::endl;
        std::wcout << L"File size: " << ((static_cast<ULONGLONG>(fileInfo.nFileSizeHigh) << 32) | fileInfo.nFileSizeLow) << L" bytes" << std::endl;
        std::wcout << L"Number of links: " << fileInfo.nNumberOfLinks << std::endl;
        std::wcout << L"Volume serial number: " << fileInfo.dwVolumeSerialNumber << std::endl;
        std::wcout << L"File index: " << fileInfo.nFileIndexHigh << L"-" << fileInfo.nFileIndexLow << std::endl;
    }
    else
        std::wcerr << L"Error: Unable to retrieve file information." << std::endl;

    CloseHandle(hFile);
}

void FileManager::help()
{
    std::wcout << L"Usage: [command] [arguments]" << std::endl << std::endl;
    std::wcout << L"Available commands:" << std::endl << std::endl;
    std::wcout << L"mkdir <dir>       Create a new directory." << std::endl;
    std::wcout << L"rm <dir>          Remove a directory." << std::endl;
    std::wcout << L"touch <file>      Create an empty file." << std::endl;
    std::wcout << L"cp <src> <dest>   Copy a file from source to destination." << std::endl;
    std::wcout << L"mv <src> <dest>   Move or rename a file." << std::endl;
    std::wcout << L"cd <dir>          Change the current directory." << std::endl;
    std::wcout << L"info <file>       Display file attributes." << std::endl;
    std::wcout << L"ls                List files in the current directory." << std::endl;
    std::wcout << L"help              Show this help message." << std::endl;
    std::wcout << L"clear             Clear the console screen." << std::endl;
    std::wcout << L"exit              Exit the program." << std::endl << std::endl;
    std::wcout << L"For more details, type: [command] --help" << std::endl;
}

void FileManager::listFiles()
{
    std::wstring searchPath = currentPath + L"\\*";
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Error: failed to open the catalog " << currentPath << std::endl;
        return;
    }

    std::wcout << L"Content " << currentPath << L":\n";

    do
        std::wcout << findFileData.cFileName << std::endl;
    while (FindNextFileW(hFind, &findFileData));

    FindClose(hFind);
}

void FileManager::printFileTime(const FILETIME& fileTime)
{
    SYSTEMTIME systemTime;
    FileTimeToSystemTime(&fileTime, &systemTime);

    std::wcout << systemTime.wYear << L"." << systemTime.wMonth << L"." << systemTime.wDay << L" " << systemTime.wHour << L":" << systemTime.wMinute << L":" << systemTime.wSecond << std::endl;
}

void FileManager::showFileTime(const std::wstring& fileName)
{
    std::wstring searchPath = currentPath + L"\\" + fileName;

    HANDLE hFile = CreateFile(searchPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    FILETIME cretionFile, accessTime, writeTime;
    if (GetFileTime(hFile, &cretionFile, &accessTime, &writeTime))
    {
        std::wcout << L"Creation time: ";
        printFileTime(cretionFile);
        std::wcout << L"Access time: ";
        printFileTime(accessTime);
        std::wcout << L"Write time: ";
        printFileTime(writeTime);
    }
    else
        std::wcerr << L"Error\n";

    CloseHandle(hFile);
}

void FileManager::setTimeFile(const std::wstring& fileName, const std::wstring& time, const std::wstring& select)
{
    std::wstring filename = currentPath + L"\\" + fileName;


    HANDLE hFile = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cerr << "File opening error\n";
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
        std::cerr << "Time enveloping error\n";
        CloseHandle(hFile);
        return;
    }

    if (select == L"-w")
    {

        if (SetFileTime(hFile, NULL, NULL, &ft))
            std::cout << "The time of the last modification has been successfully changed!\n";
        else
            std::cerr << "Time changes error\n";
    }
    else if (select == L"-a")
    {
        if (SetFileTime(hFile, NULL, &ft, NULL))
            std::cout << "The time of the last modification has been successfully changed!\n";
        else
            std::cerr << "Time changes error\n";
    }
    else
    {
        if (SetFileTime(hFile, &ft, NULL, NULL))
            std::cout << "The time of the last modification has been successfully changed!\n";
        else
            std::cerr << "Time changes error\n";
    }

    CloseHandle(hFile);
}

void FileManager::handleCommand(const std::wstring& command)
{
    std::wstringstream ss(command);
    std::vector<std::wstring> args;
    std::wstring arg;

    while (ss >> arg)
        args.push_back(arg);

    if (args.empty())
        return;

    if (args[0] == L"mkdir" && args.size() == 2)
        createDirectory(args[1]);
    else if (args[0] == L"rm" && args.size() == 2)
        removeDirectory(args[1]);
    else if (args[0] == L"touch" && args.size() == 2)
        createFile(args[1]);
    else if (args[0] == L"cp" && args.size() == 3)
        copyFile(args[1], args[2]);
    else if (args[0] == L"mv" && args.size() == 3)
        moveFile(args[1], args[2]);
    else if (args[0] == L"cd" && args.size() == 2)
        setPath(args[1]);
    else if (args[0] == L"info" && args.size() == 2)
        printFileAttributes(args[1]);
    else if (args[0] == L"info" && args[1] == L"-a" && args.size() == 3)
        listFilesWithAttributes(args[2]);
    else if (args[0] == L"info" && args[1] == L"-f" && args.size() == 3)
        getFileInfo(args[2]);
    else if (args[0] == L"time" && args.size() == 2)
        showFileTime(args[1]);
    else if (args[0] == L"time" && args[1] == L"-s" && (args[2] == L"-c" || args[2] == L"-a" || args[2] == L"-w") && args.size() == 6)
    {
        std::wstring timeString = args[4] + L" " + args[5];
        setTimeFile(args[3], timeString, args[2]);
    }
    else if (args[0] == L"ls")
        listFiles();
    else if (args[0] == L"help")
        help();
    else if (args[0] == L"clear")
        system("cls");
    else if (args[0] == L"exit")
        loopFlag = false;
    else
        std::wcout << L"Unknown command! " << L"For info enter \"help\" " << std::endl;
}

void FileManager::startShell()
{
    std::wstring input;
    while (loopFlag)
    {
        std::wcout << L"\n" << currentPath << L"> ";
        std::getline(std::wcin, input);
        handleCommand(input);
    }
    loopFlag = true;
}