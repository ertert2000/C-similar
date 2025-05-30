#include <windows.h>
#include <iostream>
#include <string>

HANDLE hPipe = INVALID_HANDLE_VALUE;
HANDLE hEvent = nullptr;
OVERLAPPED overlapped = {};
const wchar_t* pipeName = L"\\\\.\\pipe\\Pipe";

void CreatePipeAndEvent() {
    hPipe = CreateNamedPipeW(
        pipeName,
        PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, nullptr);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe. Error: " << GetLastError() << "\n";
        return;
    }

    hEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!hEvent) {
        std::cerr << "Failed to create event. Error: " << GetLastError() << "\n";
        CloseHandle(hPipe);
        hPipe = INVALID_HANDLE_VALUE;
        return;
    }

    overlapped = {};
    overlapped.hEvent = hEvent;

    std::cout << "Pipe and event created successfully.\n";
}

void WaitForClient() {
    if (hPipe == INVALID_HANDLE_VALUE || !hEvent) {
        std::cerr << "Pipe or event not initialized.\n";
        return;
    }

    BOOL result = ConnectNamedPipe(hPipe, &overlapped);

    if (!result) {
        DWORD err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            std::cout << "Waiting for client to connect...\n";
            WaitForSingleObject(hEvent, INFINITE);
            std::cout << "Client connected.\n";
        }
        else if (err == ERROR_PIPE_CONNECTED) {
            std::cout << "Client already connected.\n";
            SetEvent(hEvent);
        }
        else {
            std::cerr << "Failed to connect to client. Error: " << err << "\n";
        }
    }
    else {
        std::cout << "Client connected immediately.\n";
    }
}

void WriteToClient() {
    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Pipe is not connected.\n";
        return;
    }

    std::string input;
    std::cout << "Enter message to send: ";
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cerr << "Empty message. Nothing sent.\n";
        return;
    }

    DWORD bytesWritten = 0;
    ResetEvent(hEvent);

    BOOL success = WriteFile(
        hPipe,
        input.c_str(),
        static_cast<DWORD>(input.size()),
        nullptr,
        &overlapped);

    if (!success) {
        DWORD err = GetLastError();
        if (err == ERROR_IO_PENDING) {
            WaitForSingleObject(hEvent, INFINITE);
            if (GetOverlappedResult(hPipe, &overlapped, &bytesWritten, FALSE)) {
                std::cout << "Sent " << bytesWritten << " bytes.\n";
            }
            else {
                std::cerr << "GetOverlappedResult failed. Error: " << GetLastError() << "\n";
            }
        }
        else {
            std::cerr << "WriteFile failed immediately. Error: " << err << "\n";
        }
    }
    else {
        if (GetOverlappedResult(hPipe, &overlapped, &bytesWritten, FALSE)) {
            std::cout << "Sent " << bytesWritten << " bytes immediately.\n";
        }
    }
}

void Disconnect() {
    if (hPipe != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(hPipe);
        std::cout << "Client disconnected.\n";
    }
    else {
        std::cerr << "No pipe to disconnect.\n";
    }
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

    if (hPipe != INVALID_HANDLE_VALUE) CloseHandle(hPipe);
    if (hEvent) CloseHandle(hEvent);

    return 0;
}
