#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARS 200
#define MAX_LEN 200

struct CAR
{
    char Company[MAX_LEN];
    char Model[MAX_LEN];
    char Color[MAX_LEN];
	float Price;
}SHOP[MAX_CARS];


int comparison_function(const void* v1, const void* v2) 
{
    const struct CAR* case_1 = v1;
    const struct CAR* case_2 = v2;
    return strcmp(case_1->Company, case_2->Company);
}

int comparison_function_prise(const void* v1, const void* v2) 
{
    const struct CAR* case_1 = v1;
    const struct CAR* case_2 = v2;
    return case_1->Price - case_2->Price;
}

char* mystrtok(char* str, const char* delim) 
{
    static char* next;

    if (str) 
    {
        next = str;
        while (*next && strchr(delim, *next))
            *next++ = '\0';
    }

    if (!*next)
        str = NULL;

    else 
    {
        str = next;

        while (*next && !strchr(delim, *next)) 
            ++next;

        while (*next && strchr(delim, *next))
            *next++ = '\0';

    }

    return str;
}

int main()
{
    char temp[50000];
    char* token;
    char serchColor[MAX_LEN];
    char choiceQuest[MAX_LEN];
    int TMP = 0;
    int t = 0;
    float serchPrice, serchPrice1;
	
	FILE* f;
    f = fopen("Cars.csv", "r");
        
    while (fgets(temp, sizeof(struct CAR), f) != NULL)
    {
        token = mystrtok(temp, ";");
        strcpy(SHOP[TMP].Company, token);

        token = mystrtok(NULL, ";");
        strcpy(SHOP[TMP].Model, token);

        token = mystrtok(NULL, ";");
        strcpy(SHOP[TMP].Color, token);

        token = mystrtok(NULL, ";");
        SHOP[TMP].Price = atof(token);

        TMP++;
    }

    fclose(f);

    puts("enter the sorting method for the \"Company\" or \"Price\" table");
    fgets(choiceQuest, MAX_LEN, stdin);

    choiceQuest[strcspn(choiceQuest, "\n")] = '\0';

    if(strcmp(choiceQuest, "Company") == 0)
        qsort(SHOP, TMP, sizeof(struct CAR), comparison_function);
    if (strcmp(choiceQuest, "Price") == 0)
        qsort(SHOP, TMP, sizeof(struct CAR), comparison_function_prise);

    puts("|________________Source table_______________|");
    puts("|   Company|    Model|    Color|       Price|");
    puts("|----------+---------+---------+------------|");

    for (int i = 0; i < TMP; i++)
        printf("|%9s | %7s | %7s | %10.2f$| \n", SHOP[i].Company, SHOP[i].Model, SHOP[i].Color, SHOP[i].Price);

    puts("enter car color");
    fgets(serchColor, MAX_LEN, stdin);
    
    while (serchColor[t] != '\0')
    {
        if (serchColor[t] == '\n')
            serchColor[t] = '\0';
        t++;
    }

    puts("enter price range");
    printf("from ");
    scanf_s("%f", &serchPrice);
    printf("to ");
    scanf_s("%f", &serchPrice1);

    puts("|___________________________________________|");
    puts("|   Company|    Model|    Color|       Price|");
    puts("|----------+---------+---------+------------|");

    for (int i = 0; i < TMP; i++)
        if (strcmp(serchColor, SHOP[i].Color) == 0)
            if (serchPrice < SHOP[i].Price && SHOP[i].Price < serchPrice1)
                printf("|%9s | %7s | %7s | %10.2f$| \n", SHOP[i].Company, SHOP[i].Model, SHOP[i].Color, SHOP[i].Price);
	

	return 0;
}