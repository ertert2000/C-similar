// Дан двумерный массив.Определить количество элементов массива с различными значениями.
#include <stdio.h>
#define rows 2
#define columns 2


int main()
{
    int temp, counter = 1;
    /*scanf_s("%d", &columns);
    scanf_s("%d", &rows);*/

    int array[columns * rows];
    for (int i = 0; i < (columns * rows); i++)
        scanf_s("%d", &array[i]);

    for (int i = 0; i < (columns * rows); i++)
        for (int j = 0; j < (columns * rows) - 1 - i; j++)
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }

    for (int i = 0; i < (columns * rows) - 1; i++)
        if (array[i] != array[i + 1])
            counter++;
    
    
    printf("%d", counter);

    return 0;
}