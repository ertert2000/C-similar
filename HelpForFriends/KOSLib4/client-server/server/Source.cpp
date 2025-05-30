#include <windows.h>
#include <iostream>
#include <string>

HANDLE gPipeHandle = nullptr;
HANDLE gEventHandle = nullptr;
OVERLAPPED gAsyncOp = {};
const wchar_t* kPipePath = L"\\\\.\\pipe\\MyPipe";

void InitializeResources();

void WaitForIncomingConnection();

void SendMessageToClient();

void CloseConnection();

int main() {
    int menuChoice = -1;

    while (menuChoice != 0) {
        std::cout << "#--- Server Menu ---#" << std::endl;
        std::cout << "1. Create pipe and event" << std::endl;
        std::cout << "2. Wait for client" << std::endl;
        std::cout << "3. Write message" << std::endl;
        std::cout << "4. Disconnect client" << std::endl;
        std::cout << "0. Exit " << std::endl;
        std::cout << "Choice: ";
        std::cin >> menuChoice;
        std::cin.ignore();

        switch (menuChoice) {
        case 1: InitializeResources(); break;
        case 2: WaitForIncomingConnection(); break;
        case 3: SendMessageToClient(); break;
        case 4: CloseConnection(); break;
        }
    }

    if (gPipeHandle) CloseHandle(gPipeHandle);
    if (gEventHandle) CloseHandle(gEventHandle);

    return 0;
}

void InitializeResources() {
    gPipeHandle = CreateNamedPipeW(
        kPipePath,
        PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, nullptr
    );

    if (gPipeHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe.\n";
        return;
    }

    gEventHandle = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!gEventHandle) {
        std::cerr << "Failed to create event.\n";
        return;
    }

    gAsyncOp.hEvent = gEventHandle;

    std::cout << "Pipe and event created successfully.\n";
}

void WaitForIncomingConnection() {
    BOOL isPending = ConnectNamedPipe(gPipeHandle, &gAsyncOp);

    if (!isPending) {
        DWORD error = GetLastError();

        if (error == ERROR_IO_PENDING) {
            WaitForSingleObject(gEventHandle, INFINITE);
            std::cout << "Client connected.\n";
        }
        else if (error == ERROR_PIPE_CONNECTED) {
            SetEvent(gEventHandle);
            std::cout << "Client already connected.\n";
        }
        else {
            std::cerr << "Failed to connect to client.\n";
        }
    }
}

void SendMessageToClient() {
    std::string message;
    std::cout << "Enter message to send: ";
    std::getline(std::cin, message);

    ResetEvent(gEventHandle);
    DWORD bytesSent = 0;

    WriteFile(
        gPipeHandle,
        message.c_str(),
        static_cast<DWORD>(message.size()),
        nullptr,
        &gAsyncOp
    );

    WaitForSingleObject(gEventHandle, INFINITE);
    GetOverlappedResult(gPipeHandle, &gAsyncOp, &bytesSent, FALSE);
    std::cout << "Sent " << bytesSent << " bytes.\n";
    
}

void CloseConnection() {
    DisconnectNamedPipe(gPipeHandle);
    std::cout << "Client disconnected.\n";
}