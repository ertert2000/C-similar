#include <windows.h>
#include <stdio.h>

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
    int x1 = 10, y1 = 5, x2 = 40, y2 = 20;
    int stepT = 1000;
    int stepS = 1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int bgColor = 0; bgColor < 16; bgColor++)
        for (int textColor = 0; textColor < 16; textColor++) 
        {
            if (bgColor == textColor) continue;

            SetColor(15, bgColor);
            system("cls");

            for (int y = y1; y <= y2; y += stepS)
                for (int x = x1; x <= x2; x += 10) 
                {
                    gotoxy(x, y);
                    SetColor(textColor, bgColor);
                    printf("F:%d T:%d", bgColor, textColor);
                }

            Sleep(stepT);
        }


    return 0;
}
