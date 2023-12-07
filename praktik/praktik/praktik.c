#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>

int main() {
    char put[100];
    
    fgets(put, 100, stdin);

    int len = strlen(put);
    if (put[len - 1] = '\n')
        put[len - 1] = '\0';


    /*int c;
    int index=0;
    while ((c = getchar()) != '\n' && index < 99)
    {
        put[index] = c;
        index++;
    }
    put[index] = '\0';*/
    
    FILE* f = fopen(put, "r");
    char string[100];

    if (f == NULL)
        return 1;
    
    fgets(string, 100, f);

    printf("%s", string);

    fclose(f);
    return 0;
}
