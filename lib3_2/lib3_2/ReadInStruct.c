#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ReadInStruct.h"
#include "ControlNode.h"
#include "Mystrtok.h"

PROCESSOR_STRUCT* addInSruct(PROCESSOR_STRUCT* processor)
{
	int TMP = 0;
	char buffer[1000];
	char* token;

	char* name;
	char* nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency;
	float frequencyInTurboBoost;
	int* cache;

	name = (char*)malloc(50 * sizeof(char));
	nameGenerations = (char*)malloc(100 * sizeof(char));
	cache = (int*)malloc(3 * sizeof(int));


	FILE* file;
	file = fopen("pros.csv", "r");
	if (file == NULL)
		exit(1);

	while (fgets(buffer, 1000, file) != NULL)
	{

		token = mystrtok(buffer, ";");
		strcpy(name, token);

		token = mystrtok(NULL, ";");
		strcpy(nameGenerations, token);

		token = mystrtok(NULL, ";");
		socket = atoi(token);

		token = mystrtok(NULL, ";");
		technologicalProcess = atoi(token);

		token = mystrtok(NULL, ";");
		frequency = atof(token);

		token = mystrtok(NULL, ";");
		frequencyInTurboBoost = atof(token);

		for (int i = 0; i < 3; i++)
		{
			token = mystrtok(NULL, ",");
			cache[i] = atoi(token);
		}

		if (TMP == 0)
			processor = init(name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);
		else
			addFront(&processor, name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);

		TMP++;
	}

	fclose(file);
	free(name);
	free(nameGenerations);
	free(cache);
	return processor;

}