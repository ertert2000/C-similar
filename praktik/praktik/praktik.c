#include <stdio.h>
#include "func.h"

int check_triangle(int a, int b, int c)
{
    if (((a + b) < c) || ((c + b) < a) || ((c + a) < b))
        return 0;
    return 1;
}

int main()
{
    int a, b, c;

    return 0;
}