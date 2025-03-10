#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

void scanMemory(DWORD pid, int targetValue) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!hProcess) {
        printf("������ �������� ��������: %lu\n", GetLastError());
        return;
    }

    MEMORY_BASIC_INFORMATION mbi;
    unsigned char* addr = 0;
    SIZE_T bytesRead;

    while (VirtualQueryEx(hProcess, addr, &mbi, sizeof(mbi))) {
        if (mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {
            unsigned char* buffer = (unsigned char*)malloc(mbi.RegionSize);
            if (ReadProcessMemory(hProcess, addr, buffer, mbi.RegionSize, &bytesRead)) {
                for (SIZE_T i = 0; i < bytesRead - sizeof(int); i++) {
                    if (*(int*)(buffer + i) == targetValue) {
                        printf("������� �������� %d �� ������: 0x%p\n", targetValue, addr + i);
                    }
                }
            }
            free(buffer);
        }
        addr += mbi.RegionSize;
    }

    CloseHandle(hProcess);
}


void findValue(LPCVOID address, DWORD pid)
{

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!hProcess) {
        printf("�� ������� ������� �������! ��� ������: %lu\n", GetLastError());
        return 1;
    }

    SIZE_T bytesRead;
    int buffer;                  

    if (ReadProcessMemory(hProcess, address, &buffer, sizeof(buffer), &bytesRead)) {
        printf("�������� �� ������ %p: %d\n", address, buffer);
    }
    else {
        printf("������ ������ ������! ��� ������: %lu\n", GetLastError());
    }

    CloseHandle(hProcess);
}


int main() 
{
    setlocale(LC_ALL, "RUS");
    int targetValue;
    LPCVOID address = 0x0000; DWORD pid = 26004;
    int choose;
    char adress[12];
    //scanMemory(pid, targetValue);

    FILE* file = fopen("new_text.txt", "r");
    if (file == NULL) {
        printf("�� ������� ������� ����.\n");
        return 1;
    }

    char buffer[30];
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = 0;

        LPCVOID address = (LPCVOID)strtoull(buffer, NULL, 16);

        if (address == NULL) 
        {
            printf("������ �������������� ������ � �����.\n");
            continue;
        }

        findValue(address, pid);
    }

    fclose(file);
    return 0;

    
    //findValue((LPCVOID)0x2437FA6B4D8, 12236);

}
