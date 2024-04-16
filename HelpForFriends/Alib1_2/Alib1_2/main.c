#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100
#define MAXPERSON 200

struct NOTE2
{
	char Name[MAXLEN];
	char TELE[MAXLEN];
	char DATE[MAXLEN];
}BLOCKNOTE[MAXPERSON];

int comparison(const void* v1, const void* v2);

char* mystrtok(char* str, const char* delim);

int main()
{
	FILE* file;
    char buffer[1024];
    char* token;
    char numbePhone[20];
    int temp = 0;
    int i;
    int flag;

	file = fopen("person.csv", "r");

    while (fgets(buffer, sizeof(struct NOTE2), file) != NULL)
    {
        token = mystrtok(buffer, ";");
        strcpy(BLOCKNOTE[temp].Name, token);

        token = mystrtok(NULL, ";");
        strcpy(BLOCKNOTE[temp].TELE, token);

        token = mystrtok(NULL, ";");
        strcpy(BLOCKNOTE[temp].DATE, token);

        temp++;
    }

    fclose(file);

    qsort(BLOCKNOTE, temp, sizeof(struct NOTE2), comparison);

    puts("\n| Name            |Phone number    |Date of birth");
    puts("+-----------------+----------------+------------");

    for (i = 0; i < temp; i++)
        printf("| %15s |%14s  | %s", BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);
    puts("");

    puts("enter a phone number to find a person");
    fgets(numbePhone, 20, stdin);

    numbePhone[strcspn(numbePhone, "\n")] = '\0';

    flag = 1;
    for (i = 0; i < temp; i++)
        if (strcmp(numbePhone, BLOCKNOTE[i].TELE) == 0){
            printf("%s %s %s", BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);
            flag = 0;
        }

    if (flag)
            printf("Error, this user was not found!");

	return 0;
}

int comparison(const void* v1, const void* v2)
{
    const struct NOTE2* note_1 = v1;
    const struct NOTE2* note_2 = v2;
    return strcmp(note_1->Name, note_2->Name);
}

char* mystrtok(char* str, const char* delim) {
    static char* next;

    if (str) {
        next = str;
        while (*next && strchr(delim, *next))
            *next++ = '\0';
    }

    if (!*next) {
        str = NULL;

    }
    else {
        str = next;

        while (*next && !strchr(delim, *next)) {
            ++next;
        }

        while (*next && strchr(delim, *next))
            *next++ = '\0';

    }

    return str;
}
