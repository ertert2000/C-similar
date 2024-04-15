#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
	char* name;
	char* nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency; //�������
	float frequencyInTurboBoost;
	int* cache;
	int TMP;
} PROCESSOR_STRUCT;

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
PROCESSOR_STRUCT* addMemory(int size, int TMP, PROCESSOR_STRUCT* processor)
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
	return (-1) * flag;
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
		puts("enter the name ofthe processor");
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