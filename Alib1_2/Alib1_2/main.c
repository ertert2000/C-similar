#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100
#define MAXPERSON 200

struct NOTE2 // вообще нисколько не похоже)
{
	char Name[MAXLEN];
	char TELE[MAXLEN];
	char DATE[MAXLEN];
}BLOCKNOTE[MAXPERSON];

int comparison(const void* v1, const void* v2); //это прототип функция внизу

int main()
{
	FILE* file;
    char buffer[1024];
    char* token;
    char numbePhone[20];
    int temp = 0;
    int i;
    

	file = fopen("person.csv", "r");

    while (fgets(buffer, sizeof(struct NOTE2), file) != NULL)
    {
        token = strtok(buffer, ";");
        strcpy(BLOCKNOTE[temp].Name, token);

        token = strtok(NULL, ";");
        strcpy(BLOCKNOTE[temp].TELE, token);

        token = strtok(NULL, ";");
        strcpy(BLOCKNOTE[temp].DATE, token);

        temp++;
    }

    fclose(file);


    qsort(BLOCKNOTE, temp, sizeof(struct NOTE2), comparison);

    puts("enter a phone number to find a person");
    fgets(numbePhone, 20, stdin);

    numbePhone[strcspn(numbePhone, "\n")] = '\0';
    

    puts("\nName  Phone number  Date of birth");
    for (i = 0; i < temp; i++)
        if (strcmp(numbePhone, BLOCKNOTE[i].TELE) == 0)
            printf("%s %s %s", BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);

    puts(""); //тоже служебное........... КАК ПРОТЕСТИШЬ ВСЕ УБРАТЬ
    for (i = 0; i < temp; i++) //для проверки сортировки
        printf("%s %s %s", BLOCKNOTE[i].Name, BLOCKNOTE[i].TELE, BLOCKNOTE[i].DATE);


	return 0;
}

int comparison(const void* v1, const void* v2)
{
    const struct NOTE2* note_1 = v1;
    const struct NOTE2* note_2 = v2;
    return strcmp(note_1->Name, note_2->Name);
}