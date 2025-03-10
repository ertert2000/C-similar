//#define _CRT_SECURE_NO_WARNINGS
//
//#define UNICODE
//#define _UNICODE
//#include <iostream>
//#include <string>
//#include <chrono>
//#include <thread>
//#include <queue>
//#include <map>
//#include <set>
//#include <filesystem>
//#include <fstream>
//#include <windows.h>
//#include <psapi.h>
//#include <tlhelp32.h>
//#include <mutex>
//#include <locale>
//
//// Константы
//const std::string TARGET_FOLDER = "WB_PVZ";
//const std::string LOG_PATH = R"(D:\file_access.log)";
//std::string WATCHED_DIR;
//bool stop_threads = false;
//
//// Очередь для сообщений
//std::queue<std::string> message_queue;
//std::mutex queue_mutex;
//
//// Класс для логирования
//class Logger {
//public:
//    Logger(const std::string& path) {
//        log_file.open(path, std::ios::app);
//    }
//
//
//    void info(const std::string& message) {
//        auto now = std::chrono::system_clock::now();
//        auto time = std::chrono::system_clock::to_time_t(now);
//        std::string timestamp = std::ctime(&time);
//        timestamp = timestamp.substr(0, timestamp.length() - 1);
//
//        std::lock_guard<std::mutex> lock(log_mutex);
//        log_file << timestamp << " - INFO - " << message << std::endl;
//    }
//
//private:
//    std::ofstream log_file;
//    std::mutex log_mutex;
//};
//
//// Глобальный логгер
//std::unique_ptr<Logger> logger;
//
//// Прототип функции для создания консоли
//void create_console();
//
//// Поиск директории
//std::string find_directory() {
//    for (char drive = 'C'; drive <= 'Z'; ++drive) {
//        std::string drive_path = std::string(1, drive) + ":\\";
//        try {
//            for (const auto& entry : std::filesystem::recursive_directory_iterator(drive_path)) {
//                if (entry.is_directory() && entry.path().filename() == TARGET_FOLDER) {
//                    std::cout << "Найдена папка: " << entry.path().string() << std::endl;
//                    return entry.path().string();
//                }
//            }
//        }
//        catch (...) {
//            continue;
//        }
//    }
//    return "";
//}
//
//// Мониторинг файлов
//void monitor_file_access() {
//    std::map<std::tuple<std::string, std::string, DWORD>, std::chrono::system_clock::time_point> last_seen;
//
//    while (!stop_threads) {
//        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//        if (snapshot == INVALID_HANDLE_VALUE) continue;
//
//        PROCESSENTRY32W pe32;
//        pe32.dwSize = sizeof(pe32);
//
//        if (Process32FirstW(snapshot, &pe32)) {
//            do {
//                HANDLE process = OpenProcess(
//                    PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
//                    FALSE,
//                    pe32.th32ProcessID
//                );
//
//                if (process) {
//                    HANDLE snapshot_handle = CreateToolhelp32Snapshot(
//                        TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
//                        pe32.th32ProcessID
//                    );
//
//                    if (snapshot_handle != INVALID_HANDLE_VALUE) {
//                        MODULEENTRY32W me32;
//                        me32.dwSize = sizeof(me32);
//
//                        if (Module32FirstW(snapshot_handle, &me32)) {
//                            do {
//                                std::wstring path = me32.szExePath;
//                                if (path.find(L".mp3") != std::wstring::npos &&
//                                    path.find(std::wstring(WATCHED_DIR.begin(), WATCHED_DIR.end())) != std::wstring::npos) {
//
//                                    auto now = std::chrono::system_clock::now();
//                                    auto key = std::make_tuple(
//                                        std::string(path.begin(), path.end()),
//                                        std::string(pe32.szExeFile, pe32.szExeFile + wcslen(pe32.szExeFile)),
//                                        pe32.th32ProcessID
//                                    );
//
//                                    if (last_seen.find(key) == last_seen.end() ||
//                                        std::chrono::duration_cast<std::chrono::milliseconds>(now - last_seen[key]).count() > 100) {
//
//                                        auto time = std::chrono::system_clock::to_time_t(now);
//                                        std::string message =
//                                            std::string(std::ctime(&time)).substr(0, 24) +
//                                            " - INFO - [ACCESS] " + std::get<0>(key) +
//                                            " от процесса " + std::get<1>(key) +
//                                            " (PID: " + std::to_string(std::get<2>(key)) + ")";
//
//                                        std::cout << message << std::endl;
//
//                                        std::lock_guard<std::mutex> lock(queue_mutex);
//                                        message_queue.push(message);
//
//                                        last_seen[key] = now;
//                                    }
//                                }
//                            } while (Module32NextW(snapshot_handle, &me32));
//                        }
//                        CloseHandle(snapshot_handle);
//                    }
//                    CloseHandle(process);
//                }
//            } while (Process32NextW(snapshot, &pe32));
//        }
//        CloseHandle(snapshot);
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    }
//}
//
//// Обработка сообщений
//void display_messages() {
//    while (!stop_threads) {
//        std::lock_guard<std::mutex> lock(queue_mutex);
//        while (!message_queue.empty()) {
//            logger->info(message_queue.front());
//            message_queue.pop();
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    }
//}
//
//
//// Функция для создания консоли
//void create_console() {
//    AllocConsole(); // Выделяем память для консоли
//    FILE* file;
//    freopen_s(&file, "CONOUT$", "w", stdout); // Перенаправляем стандартный вывод
//    freopen_s(&file, "CONOUT$", "w", stderr); // Перенаправляем стандартный вывод ошибок
//    std::cout.clear(); // Обновляем поток вывода
//    std::cerr.clear(); // Обновляем поток ошибок
//}
//
//int main() 
//{
//
//    create_console();  // Создаем консоль вручную
//
//    std::cout << "Launch of the program ..." << std::endl;
//
//    //WATCHED_DIR = find_directory();
//
//    WATCHED_DIR = "D:\\WB_PVZ";
//    if (WATCHED_DIR.empty()) {
//        std::cout << "The WB Point folder was not found." << std::endl;
//        return 1;
//    }
//
//    logger = std::make_unique<Logger>(LOG_PATH);
//    logger->info("--- Программа запущена ---");
//    std::cout << "--- The program is running ---" << std::endl;
//
//    std::thread monitor_thread(monitor_file_access);
//    std::thread display_thread(display_messages);
//
//
//    stop_threads = true; // Останавливаем потоки после выхода из GUI
//    monitor_thread.join();
//    display_thread.join();
//
//    logger->info("--- The program is completed ---");
//    std::cout << "--- Программа завершена ---" << std::endl;
//
//    // Ожидание нажатия клавиши перед закрытием
//    std::cout << "Press any key to close the program ..." << std::endl;
//    Sleep(10000);
//    return 0;
//}



#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

DWORD GetProcessIdByWindowTitle(const std::wstring& windowTitle) {
    HWND hWnd = FindWindowW(NULL, windowTitle.c_str());
    if (!hWnd) {
        std::wcerr << L"The window is not found!" << std::endl;
        return 0;
    }
    DWORD processId = 0;
    GetWindowThreadProcessId(hWnd, &processId);
    return processId;
}

void ListOpenedFiles(DWORD processId) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "It was not possible to get a picture of the process." << std::endl;
        return;
    }
    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &me32)) {
        do {
            std::wstring modulePath = me32.szExePath;
            if (modulePath.find(L".mp3") != std::wstring::npos) {
                std::wcout << L"Open mp3: " << modulePath << std::endl;
            }
        } while (Module32Next(hSnapshot, &me32));
    }
    CloseHandle(hSnapshot);
}

int main() {
    std::wstring windowTitle = L"Медиаплеер";
    while (true)
    {
        DWORD processId = GetProcessIdByWindowTitle(windowTitle);
        if (processId) {
            ListOpenedFiles(processId);
        }
    }
    return 0;
}