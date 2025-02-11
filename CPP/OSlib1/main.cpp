#include <iostream>
#include "Menu.h"

int main() 
{
    bool interfaceFlag = true;

    Menu menu;

    while (interfaceFlag)
        interfaceFlag = menu.mainMenu();
    return 0;
}