#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

PROCESSOR_STRUCT* addMemory(int size,int TMP, PROCESSOR_STRUCT* processor)
{
	PROCESSOR_STRUCT* temp;

	temp = (PROCESSOR_STRUCT*)realloc(processor, size * sizeof(PROCESSOR_STRUCT));
	if (temp)
	{
		processor = temp;
		for (int i = TMP; i < size; i++)
		{
			processor[i].name = malloc(50 * sizeof(char));
			processor[i].cache = malloc(3 * sizeof(int));
			processor[i].nameGenerations = malloc(100 * sizeof(char));
		}
	}

	return processor;
}

void addInFile()
{
	char yesNo;
	int flag = 1;

	FILE* file;
	file = fopen("pros.csv", "a");
	if (file == NULL)
		exit(1);

	while (flag)
	{
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
		for (int i = 0; i < 3; i++)
		{
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
		system("cls");
	}

	fclose(file);
}