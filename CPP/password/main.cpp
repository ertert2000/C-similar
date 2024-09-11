#include <iostream>
#include <windows.h>

int main() {
    // Команда для запуска WSL и выполнения команды внутри WSL
    const char* cmd = "wsl bash -c \"echo '#include <iostream>\\nint main() { std::cout << \\\"Hello, World!\\\" << std::endl; return 0; }' > hello.cpp && g++ hello.cpp -o hello && ./hello\"";

    // Настройка структуры для запуска процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Создание процесса
    if (CreateProcess(NULL, (LPWSTR)cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Ожидание завершения процесса
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Закрытие дескрипторов процесса и потока
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Failed to create process." << std::endl;
    }

    return 0;
}

