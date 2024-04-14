#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"

#define MAX_LINE_LENGTH 100

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
/***********************************************************************************/

void InitCar(CarHead* my_carHead) {
    my_carHead->first = NULL;
    my_carHead->last = NULL;
}
/***********************************************************************************/

void InitBrand(BrandHead* my_brandHead) {
    my_brandHead->first = NULL;
    my_brandHead->last = NULL;
}
/***********************************************************************************/

void PushBack_Car(CarHead* my_carHead, char* string, Brand* marque) {
    Car* new = malloc(sizeof(Car));
    char* token = mystrtok(string, ",");
    if (token) new->name = token;
    token = mystrtok(string, ",");/*skip this line because is the brand*/
    if (token) new->manufacturer = marque;
    token = mystrtok(string, ",");
    if (token) new->year = atoi(token);
    token = mystrtok(string, ",");
    if (token) new->weigth = atof(token);
    token = mystrtok(string, ",");
    if (token) new->mileage = atoi(token);
    token = mystrtok(string, ",");
    if (token) new->engineSize = atof(token);
    token = mystrtok(string, ",");
    if (token) new->price[0] = atof(token);
    token = mystrtok(string, ",");
    if (token) new->price[1] = atof(token);
    new->next = NULL;
    new->prev = my_carHead->last;
    if (my_carHead->last) my_carHead->last->next = new; /*if it have a last it should, his next element his point on new and it will become the penultimate*/
    else my_carHead->last = new;
}
/***********************************************************************************/

Brand* PushBack_Brand(BrandHead* my_brandHead, char* brand) {
    Brand* new = malloc(sizeof(Brand));
    new->name = brand;
    new->next = NULL;
    new->prev = my_brandHead->last;
    if (my_brandHead->last) my_brandHead->last->next = new;
    else my_brandHead->last = new;
    return new;
}
/***********************************************************************************/

void ReadFromFile(CarHead* mycarHead, BrandHead* my_brandHead) {
    printf("Enter the path of the file: ");
    char filename[15];
    scanf("%s", filename);
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Opening File error 89");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        Brand* temp = NULL;
        char* token = mystrtok(line, ",");
        if (!token) {
            printf("Cutting Error 98");
            exit(1);
        }
        token = mystrtok(line, ",");
        if (token) temp = PushBack_Brand(my_brandHead, token);
        PushBack_Car(mycarHead, line, temp);
    }

}
/***********************************************************************************/

void ReadFromConsole(CarHead* mycarHead, BrandHead* my_brandHead) {
    printf("How many cars do you want to add ? \n");
    int n;
    scanf("%d", &n);
    char line[MAX_LINE_LENGTH];
    for (int i = 0; i < n; i++) {
        printf("Input the following information about the car separate by a coma. \n");
        printf("Name,Manufacturer,Year,Weight,Mileage,EngineSize,PriceinEuro,PriceinDollars \n");
        scanf("%s", line);
        Brand* temp = NULL;
        char* token = mystrtok(line, ",");
        if (!token) {
            printf("Cutting Error 121");
            exit(1);
        }
        token = mystrtok(line, ",");
        if (token) temp = PushBack_Brand(my_brandHead, token);
        PushBack_Car(mycarHead, line, temp);
    }
}
/***********************************************************************************/

void PrintBrand(BrandHead* my_brandHead) {
    Brand* current = my_brandHead->first;
    while (current) {
        printf("%s\n", current->name);
        current = current->next;
    }
}
/***********************************************************************************/

void PrintCar(CarHead* mycarHead) {
    Car* current = mycarHead->first;
    printf("┌────────────┬────────────────────┬────────────┬──────────────┬─────────────┬─────────────────┬─────────┬─────────────────┐\n");
    printf("│ Name       │ Manufacturer       │ Year       │ Weigth       │ Mileage     │     Engine size │  Prix $ │ Prix P          │\n");
    printf("├────────────┼────────────────────┼────────────┼──────────────┼─────────────┼─────────────────┼─────────┼─────────────────┤\n");
    while (current) {
        printf("│ %-10s │ %-18s │ %-14d │ %-5.2f │ %-11d │ %-14.2f│ %-6.2f │ %-6.2f│\n",
            current->name, current->manufacturer->name, current->year, current->weigth,
            current->mileage, current->engineSize, current->price[0], current->price[1]);
        printf("├────────────┼────────────────────┼────────────┼──────────────┼─────────────┼─────────────────┼─────────┼─────────────────┤\n");
        current = current->next;
    }
    printf("└────────────┴────────────────────┴────────────┴──────────────┴─────────────┴─────────────────┴─────────┴─────────────────┘\n");
}
/***********************************************************************************/

void PopElem(CarHead* mycarHead) {
    printf("Enter the year of the car that you want to delete the next element\n");
    int anos;
    scanf("%d", &anos);
    Car* current = mycarHead->first;
    while (current->year != anos)
    {
        current = current->next;
    }
    if (current->next == NULL) printf("This is the last element, you can't delete it");
    else {
        Car* temp = current->next;
        current->next = temp->next;
        temp->next->prev = current;
    }
}
/***********************************************************************************/

void ClearCar(CarHead* mycarHead) {
    Car* temp;
    Car* pelem = mycarHead->first;
    while (pelem) {
        temp = pelem;
        pelem = pelem->next;
        free(temp);
    }
    mycarHead->first = NULL;
    mycarHead->last = NULL;
}
/***********************************************************************************/

void clearBrand(BrandHead* mybrandhead) {
    Brand* temp;
    Brand* pelem = mybrandhead->first;
    while (pelem) {
        temp = pelem;
        pelem = pelem->next;
        free(temp);
    }
    mybrandhead->first = NULL;
    mybrandhead->last = NULL;
}
/***********************************************************************************/

int menu(void) {
    int n;
    printf("Enter a number to choose the operation that you want to do \n:");
    printf("1-Add data from file (press 1 for add from a file)\n");
    printf("2-Add from console (press 2 for add element from console)\n");
    printf("3-Delete the second element (press 3 for delete the penultimate element)\n");
    printf("4-Print the list(press 4 to print the list)\n");
    printf("5-Finish the program (press 5 to finish the program)\n");
    scanf("%d", &n);
    return n;
}
/***********************************************************************************/

void traitement(int* option, CarHead* mycarHead, BrandHead* mybrandHead) {
    switch (*option)
    {
    case 1:
        ReadFromFile(mycarHead, mybrandHead);
        break;
    case 2:
        ReadFromConsole(mycarHead, mybrandHead);
        break;
    case 3:
        PopElem(mycarHead);
        break;
    case 4:
        PrintCar(mycarHead);
    default:
        ClearCar(mycarHead);
        clearBrand(mybrandHead);
        exit(1);
        break;
    }
}

