#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char* name;
    char* nameGenerations;
    int socket;
    int technologicalProcess;
    float frequency;
    float frequencyInTurboBoost;
    int* cache;
} PROCESSOR;

typedef struct {
    PROCESSOR* processors;
    int TMP;
} ProcessorArray;

void addInFile(ProcessorArray* array);

char* mystrtok(char* str, const char* delim);

ProcessorArray* addMemory(int size, int tmp, ProcessorArray* array);

ProcessorArray* inputInStruct();

int main() {
    ProcessorArray array;
    int size = 3;
    array.processors = (PROCESSOR*)malloc(size * sizeof(PROCESSOR));

    if (array.processors) {
        for (int i = 0; i < size; i++) {
            array.processors[i].name = (char*)malloc(50 * sizeof(char));
            array.processors[i].cache = (int*)malloc(3 * sizeof(int));
            array.processors[i].nameGenerations = (char*)malloc(100 * sizeof(char));
        }

        FILE* file;
        file = fopen("pros.csv", "r");
        if (file == NULL)
            exit(1);

        int tmp = 0;
        char buffer[1000];
        char* token;

        while (fgets(buffer, 1000, file) != NULL) {
            token = mystrtok(buffer, ";");
            strcpy(array.processors[tmp].name, token);

            token = mystrtok(NULL, ";");
            strcpy(array.processors[tmp].nameGenerations, token);

            token = mystrtok(NULL, ";");
            array.processors[tmp].socket = atoi(token);

            token = mystrtok(NULL, ";");
            array.processors[tmp].technologicalProcess = atoi(token);

            token = mystrtok(NULL, ";");
            array.processors[tmp].frequency = atof(token);

            token = mystrtok(NULL, ";");
            array.processors[tmp].frequencyInTurboBoost = atof(token);

            for (int i = 0; i < 3; i++) {
                token = mystrtok(NULL, ",");
                array.processors[tmp].cache[i] = atoi(token);
            }

            tmp++;
            if (tmp == size) {
                size *= 2;
                array = *addMemory(size, tmp, &array);
            }
        }

        fclose(file);

        for (int i = 0; i < tmp; i++) {
            printf("%s %s %d %d %f %f ", array.processors[i].name, array.processors[i].nameGenerations,
                array.processors[i].socket, array.processors[i].technologicalProcess, array.processors[i].frequency,
                array.processors[i].frequencyInTurboBoost);
            for (int j = 0; j < 3; j++)
                printf("%d ", array.processors[i].cache[j]);
            puts("");
        }

        free(array.processors);
    }

    return 0;
}

void addInFile(ProcessorArray* array) {
    char yesNo;
    int flag = 1;

    FILE* file;
    file = fopen("pros.csv", "a");
    if (file == NULL)
        exit(1);

    while (flag) {
        char name[50];
        char nameGenerations[50];
        int socket;
        int technologicalProcess;
        float frequency;
        float frequencyInTurboBoost;
        float cache[3];

        puts("Enter processor name:");
        scanf("%s", name);
        fprintf(file, "%s;", name);

        puts("Enter processor generations:");
        scanf("%s", nameGenerations);
        fprintf(file, "%s;", nameGenerations);

        puts("Enter processor socket:");
        scanf("%d", &socket);
        fprintf(file, "%d;", socket);

        puts("Enter technological process:");
        scanf("%d", &technologicalProcess);
        fprintf(file, "%d;", technologicalProcess);

        puts("Enter frequency:");
        scanf("%f", &frequency);
        fprintf(file, "%f;", frequency);

        puts("Enter frequency in Turbo Boost:");
        scanf("%f", &frequencyInTurboBoost);
        fprintf(file, "%f;", frequencyInTurboBoost);

        puts("Enter cache sizes (3 values):");
        for (int i = 0; i < 3; i++) {
            scanf("%f", &cache[i]);
            fprintf(file, "%f", cache[i]);
            if (i != 2)
                fprintf(file, ",");
        }
        fprintf(file, "\n");

        puts("Do you want to add another processor? (Y/N)");
        scanf(" %c", &yesNo);
        if (yesNo == 'N' || yesNo == 'n')
            flag = 0;
    }

    fclose(file);
}

char* mystrtok(char* str, const char* delim) {
    static char* next;

    if (str) {
        next = str;
        while (*next && strchr(delim, *next))
            *next++ = '\0';
    }

    if (!*next)
        str = NULL;
    else {
        str = next;
        while (*next && !strchr(delim, *next))
            ++next;
        while (*next && strchr(delim, *next))
            *next++ = '\0';
    }

    return str;
}

ProcessorArray* addMemory(int size, int tmp, ProcessorArray* array) {
    char* temp;
    ProcessorArray* newArray = array;
    temp = realloc(array->processors, size * sizeof(PROCESSOR));
    if (temp) {
        newArray->processors = temp;
        for (int i = tmp; i < size; i++) {
            newArray->processors[i].name = malloc(50 * sizeof(char));
            newArray->processors[i].cache = malloc(3 * sizeof(int));
            newArray->processors[i].nameGenerations = malloc(100 * sizeof(char));
        }
    }

    return newArray;
}

ProcessorArray* inputInStruct(ProcessorArray* )
{
    
}