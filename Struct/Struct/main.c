#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


#define MAX_AUTHORS   4
#define MAX_NAME_LENGTH   100
#define MAX_PUBLISHER_LENGTH   100
#define MAX_AUTHOR_LENGTH   100
#define MAX_BOOKS   1000

struct BOOK{
    char name[MAX_NAME_LENGTH];
    char publisher[MAX_PUBLISHER_LENGTH];
    int year;
    float price;
    char authors[MAX_AUTHORS][MAX_AUTHOR_LENGTH];
} Book[MAX_BOOKS];

// Функция сравнения для qsort
int compareBooks(const void* a, const void* b) {
    const struct BOOK* bookA = a;
    const struct BOOK* bookB = b;
    return strcmp(bookA->publisher, bookB->publisher);
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

int main() {
    int TMP = 0;
    int TM = 0;
    int t = 0;
    char* token;
    char* tok = 0;
    char* temp;
    char line[1024];
    char serves[MAX_AUTHOR_LENGTH];
    char fileName[100];
    char authorName[MAX_AUTHOR_LENGTH];

    setlocale(LC_ALL, "Rus");

    printf("Введите название файла: ");
    scanf("%s", fileName);

    printf("Введите полное имя автора: ");
    scanf("%s", authorName);


    FILE* file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл\n");
        return   1;
    }

    
    while (fgets(line, sizeof(struct BOOK), file) != NULL)
    {
        token = mystrtok(line, ";");
        strcpy(Book[TMP].name, token);

        token = mystrtok(NULL, ";");
        strcpy(Book[TMP].publisher, token);

        token = mystrtok(NULL, ";");
        Book[TMP].year = atof(token);

        token = mystrtok(NULL, ";");
        Book[TMP].price = atof(token);

        token = mystrtok(NULL, ";");
        strcpy(serves, token);

        
        for (int i = 0; serves[i] != '\0'; ++i)
            if (serves[i] == ',') {
                TM = TMP;
                t++;
            }
        
        if (t == 1)
        {
            tok = mystrtok(serves, ",");
            strcpy(Book[TMP].authors[0], tok);

            temp = Book[TMP].authors[0];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[0], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[1], tok);

            temp = Book[TMP].authors[1];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[1], temp);

            t = 0;
        }
        if (t == 2)
        {
            tok = mystrtok(serves, ",");
            strcpy(Book[TMP].authors[0], tok);

            temp = Book[TMP].authors[0];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[0], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[1], tok);

            temp = Book[TMP].authors[1];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[1], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[2], tok);

            temp = Book[TMP].authors[2];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[2], temp);

            t = 0;
        }
        if (t == 3)
        {
            tok = mystrtok(serves, ",");
            strcpy(Book[TMP].authors[0], tok);

            temp = Book[TMP].authors[0];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[0], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[1], tok);

            temp = Book[TMP].authors[1];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[1], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[2], tok);

            temp = Book[TMP].authors[2];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[2], temp);

            tok = mystrtok(NULL, ",");
            strcpy(Book[TMP].authors[3], tok);

            temp = Book[TMP].authors[3];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[3], temp);

            t = 0;
        }
        else
        {
            
            strcpy(Book[TMP].authors[0], serves);

            temp = Book[TMP].authors[0];
            temp[strcspn(temp, "\n")] = '\0';
            strcpy(Book[TMP].authors[0], temp);
        }

        TMP++;
    }

    fclose(file);

    // Сортировка по названию издательства
    qsort(Book, TMP, sizeof(struct BOOK), compareBooks);

    // Вывод сведений о книгах, написанных заданным автором
    int found = 0;
    for (int i = 0; i < TMP; i++)
        for (int t = 0; t < MAX_AUTHORS; t++)
            if (strcmp(Book[i].authors[t], authorName) == 0) {
                found = printf("Название: %s, Издательство: %s, Год издания: %d, Цена: %.2f\n", Book[i].name, Book[i].publisher, Book[i].year, Book[i].price);
            }
  
    if (found == 0) {
        printf("Книги, написанные %s, не найдены.\n", authorName);
    }

    return   0;
}
