//Реализуйте функцию substring_count, которая подсчитывает количество вхождений фрагмента в тексте

//Аргументы функции : string типа char*, substring типа char*

//Возвращаемый тип : int
#include <stdio.h>
#include "func.h"
#include <string.h>

int substring_count(char* string, char* substring) 
{
    int count = 0;
    for(int i=0;i<strlen(string);i++)
        for (int j = 0; j < strlen(substring); j++)
        {
            if (string[i] == substring[j])
            {
                count++;
            }
            else
                break;
        }
    count = count / strlen(substring);
    return count;
}


int main()
{
    char string[] = { "This is an example. Return the number of occurrences of example in this example string example" };
    char substring[] = { "example" };
    substring_count(string,substring);
    return 0;
}

