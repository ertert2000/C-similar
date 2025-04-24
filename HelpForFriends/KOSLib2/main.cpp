#include <iostream>
#include <windows.h>

void show_system_info()
{
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    std::cout << "Архитектура процессора: " << sys_info.wProcessorArchitecture << "\n";
    std::cout << "Количество ядер процессора: " << sys_info.dwNumberOfProcessors << "\n";
    std::cout << "Размер страницы памяти: " << sys_info.dwPageSize << " байт\n";
    std::cout << "Минимальный адрес приложения: " << sys_info.lpMinimumApplicationAddress << "\n";
    std::cout << "Максимальный адрес приложения: " << sys_info.lpMaximumApplicationAddress << "\n";
}

void set_memory_protection()
{
    void* addr;
    DWORD old_protection;
    std::cout << "Введите адрес памяти для изменения защиты (в шестнадцатеричном формате): ";
    std::cin >> addr;
    if (VirtualProtect(addr, 4096, PAGE_READONLY, &old_protection))
        std::cout << "Защита памяти успешно обновлена!\n";
    else
        std::cerr << "Ошибка: Не удалось обновить защиту памяти!\n";
}

void get_memory_info()
{
    void* addr;
    MEMORY_BASIC_INFORMATION mem_info;
    std::cout << "Введите адрес памяти (в шестнадцатеричном формате): ";
    std::cin >> addr;
    if (VirtualQuery(addr, &mem_info, sizeof(mem_info)))
    {
        std::cout << "Базовый адрес: " << mem_info.BaseAddress << "\n";
        std::cout << "Флаги защиты выделения: " << mem_info.AllocationProtect << "\n";
    }
    else
        std::cerr << "Ошибка: Запрос памяти не удался!\n";
}

void display_memory_status()
{
    MEMORYSTATUS memory_status;
    GlobalMemoryStatus(&memory_status);
    std::cout << "Общий объём физической памяти: " << memory_status.dwTotalPhys / (1024 * 1024) << " МБ\n";
    std::cout << "Доступная физическая память: " << memory_status.dwAvailPhys / (1024 * 1024) << " МБ\n";
}

void allocate_and_commit_memory()
{
    SIZE_T memory_size = 1024 * 1024;
    LPVOID allocated_memory = VirtualAlloc(NULL, memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (allocated_memory)
    {
        std::cout << "Память выделена по адресу: " << allocated_memory << "\n";
        VirtualFree(allocated_memory, 0, MEM_RELEASE);
    }
    else
        std::cerr << "Ошибка: Не удалось выделить память!\n";
}

int main()
{
	bool menu_flag = true;
    int menu_choice;
    while (menu_flag)
    {
        std::cout << "Меню\n";
        std::cout << "1 Показать информацию о системе\n";
        std::cout << "2 Показать состояние памяти\n";
        std::cout << "3 Запросить информацию о памяти\n";
        std::cout << "4 Выделить и зарезервировать память\n";
        std::cout << "5 Изменить защиту памяти\n";
        std::cout << "0 Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> menu_choice;

        switch (menu_choice)
        {
        case 1:
            system("cls"); 
            show_system_info(); 
            system("pause"); 
            system("cls"); 
            break;
        case 2:
            system("cls"); 
            display_memory_status(); 
            system("pause"); 
            system("cls"); 
            break;
        case 3:
            system("cls"); 
            get_memory_info(); 
            system("pause"); 
            system("cls"); 
            break;
        case 4:
            system("cls");
            allocate_and_commit_memory(); 
            system("pause"); 
            system("cls"); 
            break;
        case 5:
            system("cls"); 
            set_memory_protection(); 
            system("pause"); 
            system("cls"); 
            break;
        case 0:
            system("cls");
			menu_flag = false;
            std::cout << "Выход из программы\n"; 
            break;
        default:
            std::cout << "Неверный вариант! Пожалуйста, попробуйте снова.\n";
        }
    } 

    return 0;
}
