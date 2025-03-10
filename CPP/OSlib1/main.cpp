#include <iostream>
#include "Menu.h"

int main() 
{

    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());

    bool interfaceFlag = true;

    Menu menu;

    while (interfaceFlag)
        interfaceFlag = menu.mainMenu();
    return 0;
}