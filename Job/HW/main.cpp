#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD GetProcessID(const std::wstring& processName) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

    DWORD processID = 0;
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (processName == pe32.szExeFile) {
                processID = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    return processID;
}

void ReadMemory(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, processID);
    if (!hProcess) return;

    char buffer[256];
    SIZE_T bytesRead;
    ReadProcessMemory(hProcess, (LPCVOID)0x7FFE0000, buffer, sizeof(buffer), &bytesRead);
    std::cout << "Прочитано: " << buffer << std::endl;

    CloseHandle(hProcess);
}

int main() {
    DWORD pid = GetProcessID(L"your_app.exe");
    if (pid) ReadMemory(pid);
    return 0;
}