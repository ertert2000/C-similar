#include <windows.h>
#include <iostream>

const wchar_t* gPipeName = L"\\\\.\\pipe\\MyPipe";
HANDLE gPipeHandle = nullptr;

void CALLBACK OnReadComplete(DWORD errorCode, DWORD bytesRead, LPOVERLAPPED overlappedData);

void ReceiveData();

void StartConnection();

int main() {
    int userInput = -1;

    while (userInput != 0) {
        std::cout << "#--- Client Menu ---#" << std::endl;
        std::cout << "1. Connect to server" << std::endl;
        std::cout << "2. Read message" << std::endl;
        std::cout << "0. Exit: " << std::endl;
        std::cout << "Choice: ";
        std::cin >> userInput;

        switch (userInput) {
        case 1:
            StartConnection();
            break;
        case 2:
            ReceiveData();
            break;
        }
    }

    if (gPipeHandle != nullptr && gPipeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(gPipeHandle);
    }

    return 0;
}

void CALLBACK OnReadComplete(DWORD errorCode, DWORD bytesRead, LPOVERLAPPED overlappedData) {
    if (errorCode == ERROR_SUCCESS) {
        std::cout << "\nMessage from server: " << static_cast<char*>(overlappedData->hEvent) << std::endl;
    }
    else {
        std::cerr << "\nReadFileEx failed with code: " << errorCode << std::endl;
    }
}

void ReceiveData() {
    char recvBuffer[1024] = {};
    OVERLAPPED asyncStruct = {};
    asyncStruct.hEvent = recvBuffer;

    BOOL readResult = ReadFileEx(
        gPipeHandle,
        recvBuffer,
        sizeof(recvBuffer),
        &asyncStruct,
        OnReadComplete
    );

    if (!readResult) {
        std::cerr << "ReadFileEx failed.\n";
        return;
    }

    SleepEx(INFINITE, TRUE);
}

void StartConnection() {
    gPipeHandle = CreateFileW(
        gPipeName,
        GENERIC_READ,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        nullptr
    );

    if (gPipeHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to server pipe.\n";
    }
    else {
        std::cout << "Connected to server pipe.\n";
    }
}