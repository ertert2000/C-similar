#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARS 200
#define MAX_LEN 200

struct Car
{
    char Company[MAX_LEN];
    char Model[MAX_LEN];
    char Color[MAX_LEN];
	float Price;
}SHOP[MAX_CARS];


int case_struct_comparison_function(const void* v1, const void* v2) {
    const struct Car* case_1 = v1;
    const struct Car* case_2 = v2;
    return  strcmp(case_1->Company, case_2->Company);
}

int main()
{
    char temp[50000];
    char* token;
    char serchColor[MAX_LEN];
    int TMP = 0;
    int t = 0;
    float serchPrice, serchPrice1;
	
	FILE* f;
	f = fopen("Cars.csv", "r");
    if (f == NULL)
        return 1;


    while (fgets(temp, sizeof(struct Car), f) != NULL)
    {
        token = strtok(temp, ";");
        strcpy(SHOP[TMP].Company, token);

        token = strtok(NULL, ";");
        strcpy(SHOP[TMP].Model, token);

        token = strtok(NULL, ";");
        strcpy(SHOP[TMP].Color, token);

        token = strtok(NULL, ";");
        SHOP[TMP].Price = atof(token);

        TMP++;
    }

    fclose(f);

    qsort(SHOP, TMP, sizeof(struct Car), case_struct_comparison_function);

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

    puts("Company Model Color Price\n");
    for (int i = 0; i < TMP; i++) {
        int res = strcmp(serchColor, SHOP[i].Color);
        if (res == 0)
            if (serchPrice < SHOP[i].Price && SHOP[i].Price < serchPrice1)
                printf("%s    %s    %s    %f$ \n", SHOP[i].Company, SHOP[i].Model, SHOP[i].Color, SHOP[i].Price);
    }

	
	return 0;
}