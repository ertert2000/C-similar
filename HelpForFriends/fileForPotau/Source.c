#include <stdio.h>

int number = 0;
int main()
{
    char filename[50] = "file";
    //char buffer[10];
    //int cx;

    char str[] = "hello";
    number++;

    snprintf(filename, 50, "file%d.txt", number);
    FILE* file = fopen(filename, "w+");
    if (file == NULL)
        exit(1);

    fputs(str, file);

	return 0;
}