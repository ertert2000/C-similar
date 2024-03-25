#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ControlNode.h"
#include "Struct.h"


PROCESSOR_STRUCT* init(char* name, 
    char* nameGenerations, 
    int socket, 
    int technologicalProcess, 
    float frequency, 
    float frequencyInTurboBoost, 
    int* cache)
{
    PROCESSOR_STRUCT* node = (PROCESSOR_STRUCT*)malloc(sizeof(PROCESSOR_STRUCT));
    if (!node)
        exit(1);

    node->name = malloc((strlen(name) + 1) * sizeof(char));
    if (!node->name) {
        free(node);
        exit(1);
    }
    strcpy(node->name, name);

    node->nameGenerations = malloc((strlen(nameGenerations) + 1) * sizeof(char));
    if (!node->nameGenerations) {
        free(node->name);
        free(node);
        exit(1);
    }
    strcpy(node->nameGenerations, nameGenerations);

    node->socket = socket;
    node->technologicalProcess = technologicalProcess;
    node->frequency = frequency;
    node->frequencyInTurboBoost = frequencyInTurboBoost;

    node->cache = (int*)malloc(3 * sizeof(int));
    if (!node->cache)
    {
        free(node->cache);
        free(node);
        exit(1);
    }
    for (int i = 0; i < MAXCACHE; i++)
        node->cache[i] = cache[i];

    node->next = NULL;
    return node;
}

void addFront(PROCESSOR_STRUCT** processor,
	char* name,
	char* nameGenerations,
	int socket,
	int technologicalProcess,
	float frequency,
	float frequencyInTurboBoost,
	int* cache)
{
	PROCESSOR_STRUCT* newNode = init(name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);

   
    PROCESSOR_STRUCT* temp = *processor;
    while (temp->next != NULL) 
        temp = temp->next;

    temp->next = newNode;
}

void printNode(PROCESSOR_STRUCT* processor)
{
    int flag = 0;

    while (processor != NULL)
    {
        flag += 1;
        if (flag == 1)
        {
            puts("|-----------------------------------------------------------------------------------------------|");
            puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
            puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
        }
        if (flag)
        {
            printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", processor->name, processor->nameGenerations,
                processor->socket, processor->technologicalProcess, processor->frequency,
                processor->frequencyInTurboBoost);
            for (int i = 0; i < 3; i++) {
                if (i == 2) {
                    printf("%-4d|", processor->cache[i]);
                }
                else {
                    printf("%d, ", processor->cache[i]);
                }
            }
            puts("");
        }

        //printf("%d\n", processor->socket);
        processor = processor->next;
    }
}


//PROCESSOR_STRUCT* countNode(PROCESSOR_STRUCT** processor, int serchNumber)
//{
//    int flag = 1;
//    PROCESSOR_STRUCT* temp = *processor;
//    PROCESSOR_STRUCT* TMP = NULL;
//    while (temp != NULL)
//    {
//        if (flag == serchNumber) 
//            TMP = temp;
//
//        temp = temp->next;
//        flag++;
//    }
//
//    return TMP;
//
//}

int countQualityNode(PROCESSOR_STRUCT** processor)
{
    int flag = 0;
    PROCESSOR_STRUCT* temp = *processor;
    PROCESSOR_STRUCT* TMP = NULL;
    while (temp != NULL)
    {
        temp = temp->next;
        flag++;
    }

    return flag;

}

void* copyNodes(PROCESSOR_STRUCT* processor, int copyElements[], int qualityCopyElements)
{
    int i = 1;
    int flag = 0;

    int* cache;
    cache = (int*)malloc(3 * sizeof(int));
    if (!cache)
        exit(1);
    
    COPY_PROCESSOR_STRUCT* copyProcessor = (COPY_PROCESSOR_STRUCT*)malloc(qualityCopyElements * sizeof(COPY_PROCESSOR_STRUCT));
    if (!copyProcessor)
        exit(1);

    for (int i = 0; i < qualityCopyElements; i++)
    {
        if (copyElements[i] > countQualityNode(&processor))
        {
            printf("element number %d not found\n", copyElements[i]);
        }
    }

    while (processor)
    {
        for (int j = 0; j < qualityCopyElements; j++)
        {
            
            if (copyElements[j] == i)
            {
                for (int n = 0; n < MAXCACHE; n++)
                    cache[n] = processor->cache[n];

                if (!flag)
                    copyProcessor = init(processor->name, processor->nameGenerations, processor->socket, processor->technologicalProcess, processor->frequency, processor->frequencyInTurboBoost, cache);
                else
                    addFront(&copyProcessor, processor->name, processor->nameGenerations, processor->socket, processor->technologicalProcess, processor->frequency, processor->frequencyInTurboBoost, cache);

                flag++;
            }
        }
            
        processor = processor->next;
        i++;
    }


    return copyProcessor;
}

/*strcpy(name, processor->name);

                strcpy(nameGenerations,processor->nameGenerations);

                socket = processor->socket;

                technologicalProcess = processor->technologicalProcess;

                frequency = processor->frequency;

                frequencyInTurboBoost = processor->frequencyInTurboBoost;*/