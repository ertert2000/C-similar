#include <stdio.h>
#define R 10
#define C 10


int main()
{
    int temp, columns=11, i, j, rows=11, counter = 1;


    puts("enter the size of the array (two numbers from 0 to 10)");
    while (C <= columns)
        scanf_s("%d", &columns);
    while (R <= rows)
        scanf_s("%d", &rows);

    int array[C * R];

    puts("enter the array elements");
    for (i = 0; i < (columns * rows); i++)
        scanf_s("%d", &array[i]);


    for (i = 0; i < (columns * rows); i++)
        for (j = 0; j < (columns * rows) - 1 - i; j++)
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }


    for (i = 0; i < (columns * rows) - 1; i++)
        if (array[i] != array[i + 1])
            counter++;
    
    
    printf("%d", counter);


    return 0;
}