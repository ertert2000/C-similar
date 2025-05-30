#include <windows.h>
#include <iostream>

const wchar_t* pipeName = L"\\\\.\\pipe\\MyPipe";
HANDLE hPipe;

void CALLBACK ReadCompleted(DWORD dwErrCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    if (dwErrCode == ERROR_SUCCESS) {
        std::cout << "\nMessage from server: " << (char*)lpOverlapped->hEvent << std::endl;
    }
    else {
        std::cerr << "\nReadFileEx failed with code: " << dwErrCode << std::endl;
    }
}

void ConnectToPipe() {
    hPipe = CreateFileW(
        pipeName,
        GENERIC_READ,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        nullptr);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to server pipe.\n";
        return;
    }
    std::cout << "Connected to server pipe.\n";
}

void ReadMessage() {
    char buffer[1024] = {};
    OVERLAPPED overlapped = {};
    overlapped.hEvent = buffer;

    BOOL success = ReadFileEx(
        hPipe,
        buffer,
        sizeof(buffer),
        &overlapped,
        ReadCompleted);

    if (!success) {
        std::cerr << "ReadFileEx failed.\n";
        return;
    }

    SleepEx(INFINITE, TRUE);
}

int main() {
    int choice;
    do {
        std::cout << "\n--- Client Menu ---\n";
        std::cout << "1. Connect to server\n";
        std::cout << "2. Read message\n";
        std::cout << "0. Exit\nChoice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: ConnectToPipe(); break;
        case 2: ReadMessage(); break;
        }
    } while (choice != 0);

    CloseHandle(hPipe);
    return 0;
}
