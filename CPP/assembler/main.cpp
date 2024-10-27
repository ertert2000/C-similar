//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;

int summ(int a, int b)
{
    return a + b;
}


int main()
{
    int b;
    int a;
    int sum;

    scanf_s("%d%d", &a, &b);

    __asm {
        push a
        push b

        call summ

        add esp, 8

        mov sum, eax
    }

    printf("%d\n", sum);
    return 0;
}
