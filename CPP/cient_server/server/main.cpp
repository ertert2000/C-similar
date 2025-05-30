#include <windows.h>
#include <iostream>
#include <string>

HANDLE hPipe, hEvent;
OVERLAPPED overlapped = {};
const wchar_t* pipeName = L"\\\\.\\pipe\\MyPipe";

void CreatePipeAndEvent() {
    hPipe = CreateNamedPipeW(
        pipeName,
        PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, nullptr);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe.\n";
        return;
    }

    hEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!hEvent) {
        std::cerr << "Failed to create event.\n";
        return;
    }

    overlapped.hEvent = hEvent;

    std::cout << "Pipe and event created successfully.\n";
}

void WaitForClient() {
    if (!ConnectNamedPipe(hPipe, &overlapped)) {
        if (GetLastError() == ERROR_IO_PENDING) {
            WaitForSingleObject(hEvent, INFINITE);
            std::cout << "Client connected.\n";
        }
        else if (GetLastError() == ERROR_PIPE_CONNECTED) {
            std::cout << "Client already connected.\n";
            SetEvent(hEvent);
        }
        else {
            std::cerr << "Failed to connect to client.\n";
        }
    }
}

void WriteToClient() {
    std::string input;
    std::cout << "Enter message to send: ";
    std::getline(std::cin, input);

    DWORD bytesWritten;
    ResetEvent(hEvent);

    BOOL success = WriteFile(
        hPipe,
        input.c_str(),
        input.size(),
        nullptr,
        &overlapped);

    if (!success && GetLastError() == ERROR_IO_PENDING) {
        WaitForSingleObject(hEvent, INFINITE);
        GetOverlappedResult(hPipe, &overlapped, &bytesWritten, FALSE);
        std::cout << "Sent " << bytesWritten << " bytes.\n";
    }
    else {
        std::cerr << "WriteFile failed.\n";
    }
}

void Disconnect() {
    DisconnectNamedPipe(hPipe);
    std::cout << "Client disconnected.\n";
}

int main() {
    int choice;
    do {
        std::cout << "\n--- Server Menu ---\n";
        std::cout << "1. Create pipe and event\n";
        std::cout << "2. Wait for client\n";
        std::cout << "3. Write message\n";
        std::cout << "4. Disconnect client\n";
        std::cout << "0. Exit\nChoice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: CreatePipeAndEvent(); break;
        case 2: WaitForClient(); break;
        case 3: WriteToClient(); break;
        case 4: Disconnect(); break;
        }
    } while (choice != 0);

    CloseHandle(hPipe);
    CloseHandle(hEvent);
    return 0;
}
