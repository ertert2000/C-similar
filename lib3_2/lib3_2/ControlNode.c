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
    while (processor != NULL)
    {
        printf("%d\n", processor->socket);
        processor = processor->next;
    }
}

PROCESSOR_STRUCT* copyNodes(PROCESSOR_STRUCT* processor, int copyElements[])
{
    int qualytyCopyElements = 0;
    int i = 0;

    while (copyElements != NULL)
        qualytyCopyElements += 1;
    
    COPY_PROCESSOR_STRUCT* copyProcessor = (COPY_PROCESSOR_STRUCT*)malloc(qualytyCopyElements * sizeof(COPY_PROCESSOR_STRUCT));
    if (!copyProcessor)
        exit(1);

    /*copyProcessor->name = (char*)malloc(100 * sizeof(char));
    if (!copyProcessor->name)
    {
        free(copyProcessor);
        exit(1);
    }

    copyProcessor->nameGenerations = (char*)malloc(50 * sizeof(char));
    if (!copyProcessor->nameGenerations)
    {
        free(copyProcessor->name);
        free(copyProcessor);
        exit(1);
    }

    copyProcessor->cache = (int*)malloc(MAXCACHE * sizeof(int));
    if (!copyProcessor->cache)
    {
        free(copyProcessor->cache);
        free(copyProcessor);
        exit(1);
    }*/

    while (processor != NULL)
    {
        if (copyElements[i])//эту хуетень тоже переделать
        {
            //использовать инит и добавить во фронт

        }
        i++;
        processor = processor->next;
    }

}