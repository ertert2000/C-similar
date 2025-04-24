#include <iostream>
#include <windows.h>

void GetSystemInfoFunc() 
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    std::cout << "Processor Architecture: " << si.wProcessorArchitecture << "\n";
    std::cout << "Number of Processors: " << si.dwNumberOfProcessors << "\n";
    std::cout << "Page Size: " << si.dwPageSize << " bytes\n";
    std::cout << "Minimum Application Address: " << si.lpMinimumApplicationAddress << "\n";
    std::cout << "Maximum Application Address: " << si.lpMaximumApplicationAddress << "\n";
}

void GetMemoryStatusFunc() 
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    std::cout << "Total Physical Memory: " << ms.dwTotalPhys / (1024 * 1024) << " MB" << std::endl;
    std::cout << "Available Physical Memory: " << ms.dwAvailPhys / (1024 * 1024) << " MB" << std::endl;
}

void QueryMemoryStatus() 
{
    void* address;
    MEMORY_BASIC_INFORMATION mbi;
    std::cout << "Enter memory address (hex): ";
    std::cin >> address;
    if (VirtualQuery(address, &mbi, sizeof(mbi))) 
    {
        std::cout << "Base Address: " << mbi.BaseAddress << std::endl;
        std::cout << "Allocation Protect: " << mbi.AllocationProtect << std::endl;
    }
    else
        std::cerr << "VirtualQuery failed!" << std::endl;
}

void ReserveAndCommitMemory() 
{
    SIZE_T size = 1024 * 1024;
    LPVOID mem = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (mem) 
    {
        std::cout << "Memory allocated at: " << mem << std::endl;
        VirtualFree(mem, 0, MEM_RELEASE);
    }
    else
        std::cerr << "Memory allocation failed!" << std::endl;
}

void ProtectMemory() 
{
    void* address;
    DWORD oldProtect;
    std::cout << "Enter memory address to protect (hex): ";
    std::cin >> address;
    if (VirtualProtect(address, 4096, PAGE_READONLY, &oldProtect))
        std::cout << "Memory protection changed successfully!" << std::endl;
    else
        std::cerr << "VirtualProtect failed!" << std::endl;
}

int main() 
{
    int choice;
    do 
    {
        std::cout << "#================================#" << std::endl;
        std::cout << "1 - Get System Info" << std::endl;
        std::cout << "2 - Get Memory Status" << std::endl;
        std::cout << "3 - Query Memory Status" << std::endl;
        std::cout << "4 - Reserve and Commit Memory" << std::endl;
        std::cout << "5 - Protect Memory" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "#================================#" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
            system("cls"); 
            GetSystemInfoFunc(); 
            system("pause"); 
            system("cls"); 
            break;
        case 2: 
            system("cls"); 
            GetMemoryStatusFunc(); 
            system("pause"); 
            system("cls"); 
            break;
        case 3: 
            system("cls");
            QueryMemoryStatus(); 
            system("pause"); 
            system("cls"); 
            break;
        case 4: 
            system("cls"); 
            ReserveAndCommitMemory(); 
            system("pause"); 
            system("cls"); 
            break;
        case 5:
            system("cls"); 
            ProtectMemory(); 
            system("pause"); 
            system("cls"); 
            break;
        case 0: 
            std::cout << "Exiting..." << std::endl;
            break;
        default: 
            std::cout << "Invalid choice!" << std::endl;
        }
    } 
    while (choice != 0);

    return 0;
}
