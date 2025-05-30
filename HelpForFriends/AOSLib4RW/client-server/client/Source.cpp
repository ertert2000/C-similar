#include <windows.h>
#include <iostream>

const wchar_t* pipeName = L"\\\\.\\pipe\\Pipe";
HANDLE hPipe = INVALID_HANDLE_VALUE;

struct OverlappedData {
    OVERLAPPED overlapped{};
    char buffer[1024]{};
};

void CALLBACK ReadCompleted(DWORD dwErrCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    OverlappedData* data = reinterpret_cast<OverlappedData*>(lpOverlapped);

    if (dwErrCode == ERROR_SUCCESS && dwNumberOfBytesTransfered > 0) {
        data->buffer[dwNumberOfBytesTransfered] = '\0';
        std::cout << "\nMessage from server: " << data->buffer << std::endl;
    }
    else {
        std::cerr << "\nReadFileEx failed or no data received. Error code: " << dwErrCode << std::endl;
    }

    delete data;
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
        std::cerr << "Failed to connect to server pipe. Error: " << GetLastError() << std::endl;
    }
    else {
        std::cout << "Connected to server pipe.\n";
    }
}

void ReadMessage() {
    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Not connected to pipe.\n";
        return;
    }

    auto* data = new OverlappedData();
    ZeroMemory(&data->overlapped, sizeof(OVERLAPPED));

    BOOL success = ReadFileEx(
        hPipe,
        data->buffer,
        sizeof(data->buffer) - 1,
        &data->overlapped,
        ReadCompleted);

    if (!success) {
        std::cerr << "ReadFileEx failed. Error: " << GetLastError() << std::endl;
        delete data;
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
        case 1:
            ConnectToPipe();
            break;
        case 2:
            ReadMessage();
            break;
        }

    } while (choice != 0);

    if (hPipe != INVALID_HANDLE_VALUE) {
        CloseHandle(hPipe);
    }

    return 0;
}
