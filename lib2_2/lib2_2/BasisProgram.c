#define _CRT_SECURE_NO_WARNINGS
#include "Struct.h"
#include "Strtok.h"
#include "BasisProgram.h"
#include "MemoryAndFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void* v1, const void* v2)
{
	int flag;
	const PROCESSOR_STRUCT* case_v1 = v1;
	const PROCESSOR_STRUCT* case_v2 = v2;

	if (case_v1->frequencyInTurboBoost < case_v2->frequencyInTurboBoost)
		flag = -1;
	else if (case_v1->frequencyInTurboBoost > case_v2->frequencyInTurboBoost)
		flag = 1;
	else
		flag = 0;
	return (-1)*flag;
}

PROCESSOR_STRUCT* addInSruct(PROCESSOR_STRUCT* processor)
{
	int size = 3;
	int TMP;
	char buffer[1000];
	char* token;

		
	//PROCESSOR* processor;
	processor = (PROCESSOR_STRUCT*)malloc(3 * sizeof(PROCESSOR_STRUCT));
	if (processor)
	{
		processor->TMP = 0;
		for (int i = 0; i < 3; i++)
			processor[i].name = (char*)malloc(50 * sizeof(char));
		for (int i = 0; i < 3; i++)
			processor[i].cache = (int*)malloc(3 * sizeof(int));
		for (int i = 0; i < 3; i++)
			processor[i].nameGenerations = (char*)malloc(100 * sizeof(char));



		FILE* file;
		file = fopen("pros.csv", "r");
		if (file == NULL)
			exit(1);

		while (fgets(buffer, 1000, file) != NULL)
		{

			if (processor->TMP == size)
			{
				size *= 2;
				TMP = processor->TMP;
				processor = addMemory(size, TMP, processor);
				if (processor == NULL)
					exit(1);
				processor->TMP = TMP;
			}

			token = mystrtok(buffer, ";");
			strcpy(processor[processor->TMP].name, token);

			token = mystrtok(NULL, ";");
			strcpy(processor[processor->TMP].nameGenerations, token);

			token = mystrtok(NULL, ";");
			processor[processor->TMP].socket = atoi(token);

			token = mystrtok(NULL, ";");
			processor[processor->TMP].technologicalProcess = atoi(token);

			token = mystrtok(NULL, ";");
			processor[processor->TMP].frequency = atof(token);

			token = mystrtok(NULL, ";");
			processor[processor->TMP].frequencyInTurboBoost = atof(token);

			for (int i = 0; i < 3; i++)
			{
				token = mystrtok(NULL, ",");
				processor[processor->TMP].cache[i] = atoi(token);
			}

			processor->TMP++;
		}

		fclose(file);

		TMP = processor->TMP;
		qsort(processor, TMP, sizeof(PROCESSOR_STRUCT), cmp);
		processor->TMP = TMP;
	}
	return processor;

}
