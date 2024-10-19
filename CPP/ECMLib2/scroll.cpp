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

void ScrollSquare(short left, short top, short right, short bottom)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT scrollRect;
    CHAR_INFO fillChar;

    scrollRect.Left = left;
    scrollRect.Top = top;
    scrollRect.Right = right;
    scrollRect.Bottom = bottom;

    fillChar.Char.UnicodeChar = ' ';
    fillChar.Attributes = 0;

    ScrollConsoleScreenBuffer(
        hConsole,
        &scrollRect,
        NULL,
        { left, top - 1 },
        &fillChar
    );
}

void FillConsoleExceptSquare(short left, short top, short right, short bottom, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD homeCoords = { 0, 0 };
    DWORD cellCount;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;


    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    for (short y = 0; y < csbi.dwSize.Y; y++)
        for (short x = 0; x < csbi.dwSize.X; x++)
        {
            if (x >= left && x <= right && y >= top && y <= bottom)
                continue;

            gotoxy(x, y);
            SetColor(0, bgColor);
            printf(" ");
        }
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


    short x1 = 10, y1 = 15;
    short x2 = 70, y2 = 20;
    int stepT = 700;
    int textPosY = y1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int bgColor = 1; bgColor < 16; bgColor++)
        for (int textColor = 0; textColor < 16; textColor++)
        {
            if (bgColor == textColor) continue;

            FillConsoleExceptSquare(x1, y1, x2+3, y2, bgColor);

            SetColor(textColor, bgColor);

            if (textPosY > y2)
            {
                ScrollSquare(x1, y1, x2+3, y2);
                textPosY = y2;
            }

            
            gotoxy(x1, textPosY);
            SetColor(textColor, bgColor);
            std::cout << "B:" << color[bgColor] << " T:" << color[textColor] << "  " << "B:" << color[bgColor] << " T:" << color[textColor] << "  " << "B:" << color[bgColor] << " T:" << color[textColor] << "                        ";

            textPosY++;

            Sleep(stepT);
        }

    return 0;
}

