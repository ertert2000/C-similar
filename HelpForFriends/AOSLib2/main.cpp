#include <iostream>
#include <windows.h>

void system_info()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    std::cout << "CPU Architecture: " << si.wProcessorArchitecture << "\n";
    std::cout << "Number of CPU Cores: " << si.dwNumberOfProcessors << "\n";
    std::cout << "Memory Page Size: " << si.dwPageSize << " bytes\n";
    std::cout << "Min Application Address: " << si.lpMinimumApplicationAddress << "\n";
    std::cout << "Max Application Address: " << si.lpMaximumApplicationAddress << "\n";
}

void protect_memory()
{
    void* address;
    DWORD oldProtect;
    std::cout << "Enter the memory address to modify protection (hex): ";
    std::cin >> address;
    if (VirtualProtect(address, 4096, PAGE_READONLY, &oldProtect))
        std::cout << "Memory protection updated successfully!\n";
    else
        std::cerr << "Error: Failed to update memory protection!\n";
}

void query_memory_status()
{
    void* address;
    MEMORY_BASIC_INFORMATION mbi;
    std::cout << "Enter a memory address (hex): ";
    std::cin >> address;
    if (VirtualQuery(address, &mbi, sizeof(mbi)))
    {
        std::cout << "Base Address: " << mbi.BaseAddress << "\n";
        std::cout << "Allocation Protection Flags: " << mbi.AllocationProtect << "\n";
    }
    else
        std::cerr << "Error: Memory query failed!\n";
}

void memory_status()
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    std::cout << "Total Physical Memory: " << ms.dwTotalPhys / (1024 * 1024) << " MB\n";
    std::cout << "Available Physical Memory: " << ms.dwAvailPhys / (1024 * 1024) << " MB\n";
}

void reserve_and_commit()
{
    SIZE_T size = 1024 * 1024;
    LPVOID mem = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (mem)
    {
        std::cout << "Memory allocated at address: " << mem << "\n";
        VirtualFree(mem, 0, MEM_RELEASE);
    }
    else
        std::cerr << "Error: Memory allocation failed!\n";
}

int main()
{
    int choice;
    do
    {
        std::cout << "\tMenu:\n";
        std::cout << "1. Show System Information\n";
        std::cout << "2. Show Memory Status\n";
        std::cout << "3. Query Memory Information\n";
        std::cout << "4. Allocate and Commit Memory\n";
        std::cout << "5. Modify Memory Protection\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: system("cls"); system_info(); system("pause"); system("cls"); break;
        case 2: system("cls"); memory_status(); system("pause"); system("cls"); break;
        case 3: system("cls"); query_memory_status(); system("pause"); system("cls"); break;
        case 4: system("cls"); reserve_and_commit(); system("pause"); system("cls"); break;
        case 5: system("cls"); protect_memory(); system("pause"); system("cls"); break;
        case 0: std::cout << "Exiting the program...\n"; break;
        default: std::cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
