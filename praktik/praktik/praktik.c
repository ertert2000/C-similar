#include <stdio.h>
#include "func.h"
#include <math.h>

int matrix(int matrix[][64], int arr[], int n)
{
    int k = cell(sqrt);
    int i, j;
    int index = 0;

    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
        {
            if (index < n)
            {
                matrix[i][j] = arr[index];
                index++;
            }
            else
                matrix[i][j] = 0;
        }
    return 0;
}


int main()
{
    int a;
    a = 2500 - (690 * 3);
    printf("%d",a);
    return 0;
}

