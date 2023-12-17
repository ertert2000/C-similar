/*Ввести строку символов-разделителей, а затем массив символов, 
который образует последовательность слов и символов-разделителей, находящихся в произвольном количестве до и после слов. 
Количество символов в массиве задается. Подсчитать и вывести количество слов с заданным количеством символов.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


int main() {
    char delimiters[100];
    char string[1000];

    printf("Dividers ??? ");
    fgets(delimiters, sizeof(delimiters), stdin);
    delimiters[strcspn(delimiters, "\n")] = '\0';

    printf("line ? ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    int length;
    printf("I want the length ");
    scanf("%d", &length);


    char* token = strtok(string, delimiters);
    int count = 0;

    while (token != NULL) 
    {
        if (strlen(token) == length)
            count++;
        token = strtok(NULL, delimiters);
    }

    int result = count;

    printf("such long words %d: %d\n", length, result);

    return 0;
}