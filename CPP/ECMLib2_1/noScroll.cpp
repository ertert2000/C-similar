#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

void SetColor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void gotoxy(int x, int y) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition(hConsole, position);
}

int main() 
{

    std::vector<std::string> color
    {
        "BLACK",
        "BLUE",
        "GREEN",
        "CYAN",
        "RED",
        "MAGENTA",
        "BROWN",
        "LIGHTGRAY",
        "DARKGRAY",
        "LIGHTBLUE",
        "LIGHTGREEN",
        "LIGHTCYAN",
        "LIGHTRED",
        "LIGHTMAG",
        "YELLOW",
        "WHITE"
    };

    int x1 = 10, y1 = 15, x2 = 70, y2 = 20;
    int stepT = 700;
    int stepS = 2;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int bgColor = 0; bgColor < 16; bgColor++)
        for (int textColor = 0; textColor < 16; textColor++) 
        {
            if (bgColor == textColor) continue;

            SetColor(15, bgColor);
            system("cls");

            for (int y = y1; y <= y2; y += stepS)
                for (int x = x1; x <= x2; x += 25) 
                {
                    gotoxy(x, y);
                    SetColor(textColor, bgColor);
                    std::cout << "B:" << color[bgColor] << " T:" << color[textColor];
                }

            Sleep(stepT);
        }


    return 0;
}

