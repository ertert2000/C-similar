#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Struct.h"
#include "BasisProgram.h"


int main()
{
	int flagStart = 0;
	int flagEnd = 0;
	int flagTwoEnd = 0;
	char Serch[100];
	char* name;
	PROCESSOR_STRUCT* processor = NULL;

	puts("#-----------------#");
	puts("1 - read file");
	puts("2 - add to file");
	puts("#-----------------#");
	scanf("%d", &flagStart);
	switch (flagStart)
	{
	case 1:
		processor = addInSruct(processor);
		break;
	case 2:
		addInFile();
		processor = addInSruct(processor);
		break;
	}
	system("cls");


	puts("|---------------------------------------Source table--------------------------------------------|");
	puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
	puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
	for (int i = 0; i < processor->TMP; i++)
	{
		printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", processor[i].name, processor[i].nameGenerations,
			processor[i].socket, processor[i].technologicalProcess, processor[i].frequency,
			processor[i].frequencyInTurboBoost);
		for (int j = 0; j < 3; j++) {
			if (j == 2) {
				printf("%-4d|", processor[i].cache[j]);
			}
			else {
				printf("%d, ", processor[i].cache[j]);
			}
		}
		puts("");
	}
	puts("");

	puts("#----------------------------------#");
	puts("1 - search by processor name");
	puts("2 - search by processor generation");
	puts("#----------------------------------#");
	scanf("%d", &flagEnd);

	switch (flagEnd)
	{
	case 1:
		puts("enter the name of the processor");
		scanf("%s", Serch);
		for (int i = 0; Serch[i]; i++)
			Serch[i] = tolower(Serch[i]);

		

		for (int i = 0; i < processor->TMP; i++) 
		{
			name = processor[i].name;
			for (int j = 0; name[j]; j++)
				name[j] = tolower(name[j]);

			if (strstr(name, Serch) != NULL)
			{
				flagTwoEnd += 1;
				if (flagTwoEnd == 1)
				{
					puts("|-----------------------------------------------------------------------------------------------|");
					puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flagTwoEnd)
				{
					printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", processor[i].name, processor[i].nameGenerations,
						processor[i].socket, processor[i].technologicalProcess, processor[i].frequency,
						processor[i].frequencyInTurboBoost);
					for (int j = 0; j < 3; j++) {
						if (j == 2) {
							printf("%-4d|", processor[i].cache[j]);
						}
						else {
							printf("%d, ", processor[i].cache[j]);
						}
					}
					puts("");
				}
			}
			
		}
		if (flagTwoEnd == 0)
			puts("Nothing found");
		break;
	case 2:
		puts("enter generation name");
		scanf("%s", Serch);
		for (int i = 0; Serch[i]; i++)
			Serch[i] = tolower(Serch[i]);

		for (int i = 0; i < processor->TMP; i++)
		{
			name = processor[i].nameGenerations;
			for (int j = 0; name[j]; j++)
				name[j] = tolower(name[j]);

			if (strstr(name, Serch) != NULL)
			{
				flagTwoEnd += 1;
				if (flagTwoEnd == 1)
				{
					puts("|-----------------------------------------------------------------------------------------------|");
					puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flagTwoEnd)
				{
					printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", processor[i].name, processor[i].nameGenerations,
						processor[i].socket, processor[i].technologicalProcess, processor[i].frequency,
						processor[i].frequencyInTurboBoost);
					for (int j = 0; j < 3; j++) {
						if (j == 2) {
							printf("%-4d|", processor[i].cache[j]);
						}
						else {
							printf("%d, ", processor[i].cache[j]);
						}
					}
					puts("");
				}
			}

		}
		if (flagTwoEnd == 0)
			puts("Nothing found");
		break;
	}

	
	free(processor);
	
	return 0;
}