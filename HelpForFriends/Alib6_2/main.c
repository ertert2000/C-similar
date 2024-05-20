/*Написать программу учета сдачи зачетов при помощи битовых полей.
Структура содержит поля : фамилия, группа, зачеты(битовое поле, 4 бита).
Предусмотреть вывод списков сдавших все зачеты и должников по группам и в алфавитном порядке.

Исходные данные вводятся из файла с возможностью добавления при вводе с клавиатуры.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXPERSON 200

struct NODEMARKS
{
	char surname[100];
	int group;
	signed int Castens : 4;
}MARKS[MAXPERSON];

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

int comparison(const void* v1, const void* v2)
{
    const struct NODEMARKS* note_1 = v1;
    const struct NODEMARKS* note_2 = v2;
    return strcmp(note_1->surname, note_2->surname);
}

int cmpGroup(const void* v1, const void* v2)
{
    int cmp = 0;
    const struct NODEMARKS* case_1 = v1;
    const struct NODEMARKS* case_2 = v2;
    if (case_1->group < case_2->group)
        cmp = -1;
    else if (case_1->group > case_2->group)
        cmp = 1;
    else
        cmp = 0;
    return cmp;
}

int compare(const void* v1, const void* v2)
{
    int cmp = 0;
    const struct NODEMARKS* case_1 = v1;
    const struct NODEMARKS* case_2 = v2;

    if (case_1->group != case_2->group)
        cmp = case_1->group - case_2->group;
    else
        cmp = strcmp(case_1->surname, case_2->surname);

    return cmp;
}

int readInStruct(char* fileName)
{
	int TMP = 0;
    int tokenTemp;
	char buffer[1000];
    char bufferTemp[100];
	char* token;

    FILE* file;
    file = fopen(fileName, "r");

    while (fgets(buffer, sizeof(struct NODEMARKS), file))
    {
        if (buffer[0] == '\n')
        {
            puts("error");
            exit(1);
        }

        token = mystrtok(buffer, ";");
        strcpy(MARKS[TMP].surname, token);

        token = mystrtok(NULL, ";");
        MARKS[TMP].group = atoi(token);

        token = mystrtok(NULL, ";");
        tokenTemp = atoi(token);
        if (tokenTemp <= 7 && tokenTemp >= 0)
            MARKS[TMP].Castens = tokenTemp;
        else
        {
            if (tokenTemp > 7)
            {
                puts("The number of tests cannot be more than seven");
                exit(7);
            }
            if (tokenTemp < 7)
            {
                puts("The number of credits cannot be less than zero");
                exit(-1);
            }
        }

        TMP++;
    }

    fclose(file);
    return TMP;
}

void writeInStruct(char* fileName)
{
    char yesNo;
    int flag = 1;

    FILE* file;
    file = fopen(fileName, "a");

    fputs("\n", file);
    while (flag)
    {
        char name[50];
        int group;
        int сastens;

        puts("Enter person name:");
        scanf("%s", name);
        fprintf(file, "%s;", name);

        puts("Enter group number:");
        scanf("%d", &group);
        fprintf(file, "%d;", group);

        puts("Enter number of tests passed:");
        scanf("%d", &сastens);
        if (сastens <= 7 && сastens >= 0)
            fprintf(file, "%d", сastens);
        else
        {
            puts("Input error number cannot be greater than seven or less than zero.");
            flag = 0;
        }

        if (flag != 0)
        {
            puts("Do you want to add another pocient? (Y/N)");
            scanf(" %c", &yesNo);
            if (yesNo == 'N' || yesNo == 'n')
                flag = 0;
            system("cls");
        }
    }

    fclose(file);
}

void printStruct(int temp, int choose)
{
    int Numbering = 0;
    puts("|--------------------------------------------------|");
    puts("|id |Surname     |Group     |Number of exams passed|");
    puts("|---+------------+----------+----------------------|");
    switch (choose)
    {
    case 1:
        for (int i = 0; i < temp; i++)
            if (MARKS[i].Castens == 7)
            {
                Numbering = i + 1;
                printf("|%-3d|%-12s|%-10d|%-22d|\n", Numbering, MARKS[i].surname, MARKS[i].group, MARKS[i].Castens);
            }

        system("pause");

        break;
    case 2:
        for (int i = 0; i < temp; i++)
            if (MARKS[i].Castens != 7)
            {
                Numbering = i + 1;
                printf("|%-3d|%-12s|%-10d|%-22d|\n", Numbering, MARKS[i].surname, MARKS[i].group, MARKS[i].Castens);
            }

        system("pause");

        break;
    }
}


int main()
{
    int chooseMenu;
    int chooseMenuPrint;
    int chooseSort;
    char pathfile[100];

    FILE* file;

    printf("Enter the path to the file:");
    fgets(pathfile, 100, stdin);
    pathfile[strcspn(pathfile, "\n")] = '\0';

    file = fopen(pathfile, "r");

    while (!file)
    {
        printf("Invalid file name \nEnter the path to the file again:\n");
        fgets(pathfile, 100, stdin);
        pathfile[strcspn(pathfile, "\n")] = '\0';
        file = fopen(pathfile, "r");
        system("cls");
    }
    system("cls");

    fclose(file);

    int temp = readInStruct(pathfile);



    while (1)
    {
        puts("#===================#");
        puts("1 - table output");
        puts("2 - adding students");
        puts("3 - exit");
        puts("#===================#");
        scanf("%d", &chooseMenu);

        system("cls");

        switch (chooseMenu)
        {
        case 1:

            puts("#========================================#");
            puts("1 - sorting by last name (general table)");
            puts("2 - sort by group (general table)");
            puts("3 - sort by group and last name");
            puts("#========================================#");
            scanf("%d", &chooseSort);

            switch (chooseSort)
            {
            case 1:
                qsort(MARKS, temp, sizeof(struct NODEMARKS), comparison);
                break;
            case 2:
                qsort(MARKS, temp, sizeof(struct NODEMARKS), cmpGroup);
                break;
            case 3:
                qsort(MARKS, temp, sizeof(struct NODEMARKS), compare);
                break;
            }

            system("cls");

            puts("#===============================================#");
            puts("1 - students who successfully passed the tests");
            puts("2 - students with debts");
            puts("#===============================================#");
            scanf("%d", &chooseMenuPrint);

            switch (chooseMenuPrint)
            {
            case 1:
                printStruct(temp, chooseMenuPrint);
                break;
            case 2:
                printStruct(temp, chooseMenuPrint);
                break;
            }
            system("cls");
            break;
        case 2:
            writeInStruct(pathfile);
            temp = readInStruct(pathfile);
            break;
        case 3:
	        return 0;
        }
    }
}