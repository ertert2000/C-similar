#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>


#define MAXCACHE 3

#ifdef _WIN32
#define clear() system("cls");
#else
#define clear() system("clear");
#endif // linux

typedef struct PROCESSOR_STRUCT/*basic structure*/
{
	char* name;
	char* nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency;
	float frequencyInTurboBoost;
	int* cache;
	int TMP;
	struct PROCESSOR_STRUCT* next;
	struct PROCESSOR_STRUCT* prev;
} PROCESSOR_STRUCT;

struct PROCESSOR_STRUCT_TEMPP/*structure for sorting*/
{
	char* name;
	char* nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency;
	float frequencyInTurboBoost;
	int* cache;
	int TMP;
	struct PROCESSOR_STRUCT* next;
	struct PROCESSOR_STRUCT* prev;
} PROCESSOR_STRUCT_TEMP[200];

typedef struct /*structure for signal processing*/
{
	PROCESSOR_STRUCT* processor;
	char pathFile[50];
	int signal;
} SIGNAL_DATA;

char* mystrtok(char* str, const char* delim);/*prototype functions*/

PROCESSOR_STRUCT* init(char* name, char* nameGenerations, int socket, int technologicalProcess, float frequency, float frequencyInTurboBoost, int* cache);/*prototype functions*/

void addFront(PROCESSOR_STRUCT** processor, char* name, char* nameGenerations, int socket, int technologicalProcess, float frequency, float frequencyInTurboBoost, int* cache);/*prototype functions*/

void writeInFile(PROCESSOR_STRUCT** b, int choose, char* pathFile);/*prototype functions*/

void printNode(PROCESSOR_STRUCT* processor);/*prototype functions*/

void serchByName(PROCESSOR_STRUCT** b, char* serch, int choose);/*prototype functions*/

void serchByCharacterFerqu(PROCESSOR_STRUCT** b, float serch, int choose);/*prototype functions*/

void serchByCharacter(PROCESSOR_STRUCT** b, int serch, int choose);/*prototype functions*/

void printHelp();/*prototype functions*/

void reactStruct(PROCESSOR_STRUCT** processor, int serch);/*prototype functions*/

void removeChoseCard(PROCESSOR_STRUCT** record, int remove);/*prototype functions*/

PROCESSOR_STRUCT* addInSruct(PROCESSOR_STRUCT* processor, char* pathFile);/*prototype functions*/

int cmpNameLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpNameGenerationsLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpSoketLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpFrequencyLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpFrequencyInTurboBoostLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpTechnologicalProcessLineal(const void* v1, const void* v2);/*prototype functions*/

int cmpCacheLineal(const void* v1, const void* v2);/*prototype functions*/

int destroyList(PROCESSOR_STRUCT** processor);/*prototype functions*/

PROCESSOR_STRUCT* createSortList(PROCESSOR_STRUCT* processor);/*prototype functions*/

void SigBreak_Handler(int n_signal);/*prototype functions*/

int main()/*main function*/
{
	PROCESSOR_STRUCT* processor = NULL;/*variable declarations*/


	int serch;
	int removeNode;
	int i;
	int serchTechAndSoket;

	char serchNameOrGeneration[100];
	char pathfile[100];
	float serchferqu;
	FILE* file;

	printf("Enter the name of the file you want to start working with:\n"); 
	fgets(pathfile, 100, stdin); /*entering the file path*/
	pathfile[strcspn(pathfile, "\n")] = '\0';

	file = fopen(pathfile, "r");    /*Opening a file*/

	while (!file)   /*Checking to open a file*/
	{
		printf("Invalid file name \nPlease, enter the path to the file again:\n");
		fgets(pathfile, 100, stdin);
		pathfile[strcspn(pathfile, "\n")] = '\0';
		file = fopen(pathfile, "r");
		system("cls");
	}

	fclose(file);
	system("cls");

	processor = addInSruct(processor, pathfile);

	int choice, choiceFound, choiceSort;

	SIGNAL_DATA signal_data = { .processor = &processor, .signal = SIGBREAK };
	strcpy(signal_data.pathFile, pathfile);

	FILE* tempFile = fopen("temp_signal_data.bin", "wb");
	if (tempFile == NULL) 
	{
		perror("fopen");
		return EXIT_FAILURE;
	}
	fwrite(&signal_data, sizeof(SIGNAL_DATA), 1, tempFile);
	fclose(tempFile);

	signal(SIGBREAK, SigBreak_Handler);

	while (1)
	{
		puts("/----------------------------------------\\");
		puts("0 - Help");
		puts("1 - Adding cards about domain objects");
		puts("2 - Editing cards");
		puts("3 - Removing cards");
		puts("4 - Card index output");
		puts("5 - Search for cards by parameter");
		puts("6 - Sorting a file cabinet by parameter");
		puts("7 - Exit");
		puts("/ ----------------------------------------\\");

		scanf("%d", &choice);

		//clear();
		switch (choice)
		{
		case 0: /*help*/
			printHelp();
			//clear();
			break;
		case 1:/*Adding cards about domain objects*/
			writeInFile(&processor, 1, pathfile);
			//clear();
			break;
		case 2:/*Editing cards*/
			puts("Enter the id of the element you want to change");
			scanf("%d", &serch);
			
			reactStruct(&processor, serch);
			//clear();
			break;
		case 3:/*Removing cards*/
			puts("Enter the id of the element you want to delete");
			scanf("%d", &removeNode);
			

			removeChoseCard(&processor, removeNode);
			puts("The element was successfully deleted\n");
			//clear();
			break;
		case 4:/*Card index output*/
			printNode(processor);
			system("pause");
			//clear();
			break;
		case 5:/*Search for cards by parameter*/

			puts("/----------------------------------------\\");
			puts("1 - Search by name");
			puts("2 - Search by generation");
			puts("3 - Search by base frequency");
			puts("4 - Search by frequency in turbo boost");
			puts("5 - Search by socket");
			puts("6 - Search by tech process");
			puts("7 - Search by cache");
			puts("/----------------------------------------\\");

			scanf("%d", &choiceFound); /*parameter selection*/
			while (!(choiceFound >= 1 && choiceFound <= 7)) 
			{
				puts("Please, rewrite your choice\n");
				scanf("%d", &choiceFound);
			}
			switch (choiceFound)
			{ /*number of parameters*/
			case 1: /*search by parameter*/
				puts("Enter name");
				while ((getchar()) != '\n');
				fgets(serchNameOrGeneration, 100, stdin);

				serchByName(&processor, serchNameOrGeneration, choiceFound);
				break;
			case 2:/*search by parameter*/
				puts("Enter generation");
				while ((getchar()) != '\n');
				fgets(serchNameOrGeneration, 100, stdin);

				serchByName(&processor, serchNameOrGeneration, choiceFound);
				break;
			case 3:/*search by parameter*/
				puts("Enter base frequency");
				scanf("%f", &serchferqu);
				serchByCharacterFerqu(&processor, serchferqu, choiceFound);
				break;
			case 4:/*search by parameter*/
				puts("Enter frequency in turbo boost");
				scanf("%f", &serchferqu);
				serchByCharacterFerqu(&processor, serchferqu, choiceFound);
				break;
			case 5:/*search by parameter*/
				puts("Enter socket");
				scanf("%d", &serchTechAndSoket);
				serchByCharacter(&processor, serchTechAndSoket, choiceFound);
				break;
			case 6:/*search by parameter*/
				puts("Enter tech process");
				scanf("%d", &serchTechAndSoket);
				serchByCharacter(&processor, serchTechAndSoket, choiceFound);
				break;
			case 7:/*search by parameter*/
				puts("Enter cache");
				scanf("%d", &serchTechAndSoket);
				serchByCharacter(&processor, serchTechAndSoket, choiceFound);
				break;
			}
			system("pause");
			//clear();
			break;
		case 6:/*Sorting a file cabinet by parameter*/

			puts("/----------------------------------------\\");
			puts("1 - Sort by name");
			puts("2 - Sort by generation");
			puts("3 - Sort by socket");
			puts("4 - Sort by frequency in turbo boost");
			puts("5 - Sort by base frequency");
			puts("6 - Sort by process");
			puts("7 - Sort by cache");
			puts("/----------------------------------------\\");

			scanf("%d", &choiceSort);/*parameter selection*/
			while (!(choiceSort >= 1 && choiceSort <= 7)) 
			{
				puts("Please, rewrite your choice\n");
				scanf("%d", &choiceSort);
			}
			switch (choiceSort)
			{ /*number of parameters*/
			case 1: /*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP,i,sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpNameLineal);
				processor = createSortList(processor);
				break;
			case 2:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpNameGenerationsLineal);
				processor = createSortList(processor);
				break;
			case 3:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpSoketLineal);
				processor = createSortList(processor);
				break;
			case 4:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpFrequencyLineal);
				processor = createSortList(processor);
				break;
			case 5:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpFrequencyInTurboBoostLineal);
				processor = createSortList(processor);
				break;
			case 6:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpTechnologicalProcessLineal);
				processor = createSortList(processor);
				break;
			case 7:/*sort by parameter*/
				i = destroyList(&processor);
				qsort(PROCESSOR_STRUCT_TEMP, i, sizeof(struct PROCESSOR_STRUCT_TEMPP), cmpCacheLineal);
				processor = createSortList(processor);
				break;
			}
			//clear();
			break;
		case 7:/*Exit*/
			remove("temp_signal_data.bin");
			writeInFile(&processor, 2, pathfile);
			return 0;
			break;
		default:
			puts("Enter the number he zero to seven");
			system("pause");
			clear();
			break;
		}
	}
}

char* mystrtok(char* str, const char* delim) /*function to split a string*/
{
	static char* next;

	if (str) /*string check*/
	{
		next = str;
		while (*next && strchr(delim, *next))
			*next++ = '\0';
	}

	if (!*next)
		str = NULL;

	else /*string splitting*/
	{
		str = next;

		while (*next && !strchr(delim, *next))
			++next;

		while (*next && strchr(delim, *next))
			*next++ = '\0';

	}

	return str;
}

PROCESSOR_STRUCT* init(char* name, char* nameGenerations, int socket, int technologicalProcess, float frequency, float frequencyInTurboBoost, int* cache)
{
	/*memory allocation*/
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

	/*copying variables to structure fields*/
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
	node->prev = NULL;
	return node;
}

void addFront(PROCESSOR_STRUCT** processor, char* name, char* nameGenerations, int socket, int technologicalProcess, float frequency, float frequencyInTurboBoost, int* cache)
{
	PROCESSOR_STRUCT* newNode = init(name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache); /*creating a new node*/

	/*linking structures*/
	PROCESSOR_STRUCT* temp = *processor;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newNode;
}

void writeInFile(PROCESSOR_STRUCT** b, int choose, char* pathFile)
{
	FILE* file;/*opening a file*/
	file = fopen(pathFile, "a");
	if (file == NULL)
		exit(1);

	/*declaration of variables*/
	char name[50];
	char nameGenerations[100];
	char tempSocket[50];
	char tempTechnologicalProcess[50];
	char tempFrequency[50];
	char tempFrequencyInTurboBoost[50];
	char tempCache[3];

	int socket;
	int technologicalProcess;
	float frequency;
	float frequencyInTurboBoost;
	int cache[3];

	char buffer[50];

	PROCESSOR_STRUCT* temp = *b;

	FILE* newFile;

	switch (choose)
	{
	case 1:/*selection for manual entry*/
		while ((getchar()) != '\n');
		puts("name");
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = '\0'; /*Removing a newline character*/
		fprintf(file, "%s;", name);/*copying variables to a structure field*/

		puts("nameGenerations");
		fgets(nameGenerations, sizeof(nameGenerations), stdin);
		nameGenerations[strcspn(nameGenerations, "\n")] = '\0';  /*Removing a newline character*/
		fprintf(file, "%s;", nameGenerations);/*copying variables to a structure field*/

		puts("socket");
		fgets(tempSocket, sizeof(tempSocket), stdin);
		tempSocket[strcspn(tempSocket, "\n")] = '\0';  /*Removing a newline character*/
		fprintf(file, "%s;", tempSocket);
		socket = atoi(tempSocket);/*copying variables to a structure field*/

		puts("technologicalProcess");
		fgets(tempTechnologicalProcess, sizeof(tempTechnologicalProcess), stdin);
		tempTechnologicalProcess[strcspn(tempTechnologicalProcess, "\n")] = '\0';  /*Removing a newline character*/
		fprintf(file, "%s;", tempTechnologicalProcess);
		technologicalProcess = atoi(tempTechnologicalProcess);/*copying variables to a structure field*/

		puts("frequency");
		fgets(tempFrequency, sizeof(tempFrequency), stdin);
		tempFrequency[strcspn(tempFrequency, "\n")] = '\0';  /*Removing a newline character*/
		fprintf(file, "%s;", tempFrequency);
		frequency = atof(tempFrequency);/*copying variables to a structure field*/

		puts("frequencyInTurboBoost");
		fgets(tempFrequencyInTurboBoost, sizeof(tempFrequencyInTurboBoost), stdin);
		tempFrequencyInTurboBoost[strcspn(tempFrequencyInTurboBoost, "\n")] = '\0';  /*Removing a newline character*/
		fprintf(file, "%s;", tempFrequencyInTurboBoost);
		frequencyInTurboBoost = atof(tempFrequencyInTurboBoost);/*copying variables to a structure field*/

		puts("cache");
		for (int i = 0; i < 3; i++)
		{
			memset(&tempCache[0], 0, sizeof(tempCache));
			fgets(tempCache, sizeof(tempCache), stdin);
			tempCache[strcspn(tempCache, "\n")] = '\0';  /*Removing a newline character*/
			fprintf(file, "%s", tempCache);
			if (i != 2)
				fprintf(file, ",");

			cache[i] = atoi(tempCache); /*copying variables to a structure field*/
		}
		fprintf(file, "\n");

		addFront(&temp, name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache); /*adding a new node*/
		break;
	case 2: /*data serialization*/
		remove(file); /*deleting old file*/
		newFile = fopen(pathFile, "w+");
		while (temp != NULL)
		{
			fprintf(newFile, "%s;", temp->name); /*data recording*/

			fprintf(newFile, "%s;", temp->nameGenerations); /*data recording*/

			fprintf(newFile, "%d;", temp->socket); /*data recording*/

			fprintf(newFile, "%d;", temp->technologicalProcess); /*data recording*/

			fprintf(newFile, "%.3f;", temp->frequency); /*data recording*/

			fprintf(newFile, "%.3f;", temp->frequencyInTurboBoost); /*data recording*/

			for (int i = 0; i < 3; i++)
			{
				fprintf(newFile, "%d", temp->cache[i]); /*data recording*/
				if (i != 2)
					fprintf(newFile, ",");
			}

			fprintf(newFile, "\n");

			temp = temp->next;
		}
		fclose(newFile); /*closing a file*/
		break;
	}

	fclose(file);
}

void printNode(PROCESSOR_STRUCT* processor)
{
	/*declaration of variables*/
	int flag = 0;
	int id = 1;

	while (processor != NULL)
	{
		flag += 1;
		if (flag == 1)
		{ /*header output*/
			puts("|---------------------------------------------------------------------------------------------------|");
			puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
			puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
		}
		if (flag)/*table body output*/
		{
			printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |",id, processor->name, processor->nameGenerations,
				processor->socket, processor->technologicalProcess, processor->frequency,
				processor->frequencyInTurboBoost);
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
					printf("%-4d|", processor->cache[i]);
				else
					printf("%d, ", processor->cache[i]);

			}
			puts("");
		}
		id++;
		processor = processor->next;
	}
}

void serchByName(PROCESSOR_STRUCT** b, char* serch, int choose)
{
	/*declaration of variables*/
	int flag = 0;
	int id = 1;
	PROCESSOR_STRUCT* temp = *b;
	PROCESSOR_STRUCT* processor = *b;

	char tempName[50];
	char serchName[50];
	serch[strcspn(serch, "\n")] = '\0'; /*casting to lowercase*/
	for (int i = 0; serch[i]; i++)
		serch[i] = tolower(serch[i]);
	switch (choose)
	{
	case 1:
		while (temp != NULL)
		{
			memset(&tempName[0], 0, 50);
			strcpy(tempName, temp->name);/*casting to lowercase*/
			for (int i = 0; tempName[i]; i++)
				tempName[i] = tolower(tempName[i]);
			if (!strcmp(serch, tempName))
			{ /*header output*/
				flag += 1;
				if (flag == 1)
				{
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)/*table body output*/
				{
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	case 2:
		while (temp != NULL)
		{
			memset(&tempName[0], 0, 50);
			strcpy(tempName, temp->nameGenerations); /*casting to lowercase*/
			for (int i = 0; tempName[i]; i++)
				tempName[i] = tolower(tempName[i]);
			if (!strcmp(serch, tempName))
			{
				flag += 1;
				if (flag == 1)
				{/*header output*/
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)/*table body output*/
				{
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	}
}
void serchByCharacterFerqu(PROCESSOR_STRUCT** b, float serch, int choose)
{
	/*declaration of variables*/
	int flag = 0;
	int id = 1;

	PROCESSOR_STRUCT* temp = *b;
	PROCESSOR_STRUCT* processor = *b;

	switch (choose)
	{
	case 3:
		while (temp != NULL)
		{
			if (serch == temp->frequency)
			{
				flag += 1;
				if (flag == 1)
				{/*header output*/
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)
				{/*table body output*/
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	case 4:
		while (temp != NULL)
		{
			if (serch == temp->frequencyInTurboBoost)
			{
				flag += 1;
				if (flag == 1)
				{/*header output*/
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)/*table body output*/
				{
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	}
}

void serchByCharacter(PROCESSOR_STRUCT** b, int serch, int choose)
{
	/*declaration of variables*/
	int flag = 0;
	int id = 1;

	PROCESSOR_STRUCT* temp = *b;
	PROCESSOR_STRUCT* processor = *b;

	switch (choose)
	{
	case 5:
		while (temp != NULL)
		{
			if (serch == temp->socket)
			{
				flag += 1;
				if (flag == 1)/*header output*/
				{
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)/*table body output*/
				{
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	case 6:
		while (temp != NULL)
		{
			if (serch == temp->technologicalProcess)
			{
				flag += 1;
				if (flag == 1)
				{/*header output*/
					puts("|---------------------------------------------------------------------------------------------------|");
					puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
					puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
				}
				if (flag)/*table body output*/
				{
					printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
						processor->socket, processor->technologicalProcess, processor->frequency,
						processor->frequencyInTurboBoost);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-4d|", processor->cache[i]);
						else
							printf("%d, ", processor->cache[i]);

					}
					puts("");
				}
				id++;

			}
			temp = temp->next;
		}
		break;
	case 7:
		while (temp != NULL)
		{
			for (int i = 0; i < 3; i++)
				if (serch == temp->cache[i])
				{
					flag += 1;
					if (flag == 1)
					{/*header output*/
						puts("|---------------------------------------------------------------------------------------------------|");
						puts("|id |Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");
						puts("|---+-----------------------+------------+----------+----------+------------+------------+----------|");
					}
					if (flag)/*table body output*/
					{
						printf("|%-3d|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", id, processor->name, processor->nameGenerations,
							processor->socket, processor->technologicalProcess, processor->frequency,
							processor->frequencyInTurboBoost);
						for (int i = 0; i < 3; i++)
						{
							if (i == 2)
								printf("%-4d|", processor->cache[i]);
							else
								printf("%d, ", processor->cache[i]);

						}
						puts("");
					}
					id++;

				}

			temp = temp->next;
		}
		break;
	}
}

void printHelp()
{
	char textAboutProgram[1000];
	FILE* fileAbout;

	fileAbout = fopen("AdoutProgram.txt", "r"); /*opening a file*/
	if (!fileAbout)
		exit(1);

	while (fgets(textAboutProgram, 1000, fileAbout) != NULL) /*reading and outputting strings*/
		printf("%s", textAboutProgram);

	puts("");
	system("pause");

}

void reactStruct(PROCESSOR_STRUCT** processor, int serch)
{
	/*declaration of variables*/
	PROCESSOR_STRUCT* temp = *processor;
	int i = 1;

	char name[50];
	char nameGenerations[100];
	int socket;
	int technologicalProcess;
	float frequency; //       
	float frequencyInTurboBoost;
	int cache[3];

	char socketT[50];
	char technologicalProcessT[50];
	char frequencyT[50]; //       
	char frequencyInTurboBoostT[50];
	char cacheT[3];

	while (temp != NULL)
	{
		if (i == serch)
		{
			while ((getchar()) != '\n');
			puts("name");
			fgets(name, 50, stdin); /*reading and writing to a structure*/
			name[strcspn(name, "\n")] = '\0';
			if ((name[0] != '-'))/*checking whether the user is willing to enter*/
				strcpy(temp->name, name);

			puts("nameGenerations");
			fgets(nameGenerations, 100, stdin);/*reading and writing to a structure*/
			nameGenerations[strcspn(nameGenerations, "\n")] = '\0';
			if ((nameGenerations[0] != '-'))/*checking whether the user is willing to enter*/
				strcpy(temp->nameGenerations, nameGenerations);

			puts("socket");
			fgets(socketT, 100, stdin);/*reading and writing to a structure*/
			socketT[strcspn(socketT, "\n")] = '\0';
			if ((socketT[0] != '-'))/*checking whether the user is willing to enter*/
			{
				socket = atoi(socketT);
				temp->socket = socket;
			}

			puts("technologicalProcess");
			fgets(technologicalProcessT, 100, stdin);/*reading and writing to a structure*/
			technologicalProcessT[strcspn(technologicalProcessT, "\n")] = '\0';
			if ((technologicalProcessT[0] != '-'))/*checking whether the user is willing to enter*/
			{
				technologicalProcess = atoi(technologicalProcessT);
				temp->technologicalProcess = technologicalProcess;
			}

			puts("frequency");
			fgets(frequencyT, 100, stdin);/*reading and writing to a structure*/
			frequencyT[strcspn(frequencyT, "\n")] = '\0';
			if ((frequencyT[0] != '-'))/*checking whether the user is willing to enter*/
			{
				frequency = atof(frequencyT);
				temp->frequency = frequency;
			}

			puts("frequencyInTurboBoost");
			fgets(frequencyInTurboBoostT, 100, stdin);/*reading and writing to a structure*/
			frequencyInTurboBoostT[strcspn(frequencyInTurboBoostT, "\n")] = '\0';
			if ((frequencyInTurboBoostT[0] != '-'))/*checking whether the user is willing to enter*/
			{
				frequencyInTurboBoost = atof(frequencyInTurboBoostT);
				temp->frequencyInTurboBoost = frequencyInTurboBoost;
			}
			puts("cache");

			puts("press the dash sign if you do not want to change this parameter, if not, then press any other button");
			fgets(cacheT, 100, stdin);
			cacheT[strcspn(cacheT, "\n")] = '\0';/*reading and writing to a structure*/
			if ((cacheT[0] != '-')) /*checking whether the user is willing to enter*/
				for (int i = 0; i < 3; i++)
				{
					scanf("%d", &cache[i]);
					temp->cache[i] = cache[i];
				}
		}

		i++;
		temp = temp->next;
	}
}

void removeChoseCard(PROCESSOR_STRUCT** record, int remove)
{
	if (record == NULL || *record == NULL)
		return;  /*List is empty or invalid pointer*/

	PROCESSOR_STRUCT* temp = *record;
	PROCESSOR_STRUCT* prev = NULL;
	int searchRemoveCard;

	searchRemoveCard = 1;

	/*If the node to be removed is the head node*/
	if (remove == 1) {
		*record = temp->next;
		free(temp->name);
		free(temp->nameGenerations);
		free(temp->cache);
		free(temp);
		return;
	}

	/*Traverse the list to find the node to remove*/
	while (temp != NULL && searchRemoveCard != remove)
	{
		prev = temp;
		temp = temp->next;
		searchRemoveCard++;
	}

	if (temp == NULL) /*if there is no such element*/
	{
		puts("there is no such element");
		system("pause");
	}
	else if (temp->next == NULL)/*if the last element*/
	{
		free(temp->name);
		free(temp->nameGenerations);
		free(temp->cache);
		free(temp);
		prev->next = NULL;
	}
	else
	{
		temp = temp->next;  /*Moving to the next element*/

		free(prev->next->name);
		free(prev->next->nameGenerations);
		free(prev->next->cache);
		free(prev->next);

		prev->next = temp;
	}
}



PROCESSOR_STRUCT* addInSruct(PROCESSOR_STRUCT* processor, char* pathFile)
{
	/*declaration of variables*/
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

	/*memory allocation*/
	name = (char*)malloc(50 * sizeof(char));
	nameGenerations = (char*)malloc(100 * sizeof(char));
	cache = (int*)malloc(3 * sizeof(int));


	FILE* file;
	file = fopen(pathFile, "r"); /*opening a file*/
	if (file == NULL)
		exit(1);
	while (fgets(buffer, 1000, file) != NULL) /*reading from file line by line*/
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

		if (TMP == 0) /*if one element*/
		{
			processor = init(name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);
			processor->TMP = 0;
		}
		else /*in any other case*/
			addFront(&processor, name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);

		TMP++;
		processor->TMP++;
	}

	/*closing the file and freeing up memory*/
	fclose(file);
	free(name);
	free(nameGenerations);
	free(cache);
	return processor;

}

int cmpNameLineal(const void* v1, const void* v2)
{
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;
	return strcmp(case_1->name, case_2->name); /*comparison of variables*/
}

int cmpNameGenerationsLineal(const void* v1, const void* v2)
{
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;
	return strcmp(case_1->nameGenerations, case_2->nameGenerations);/*comparison of variables*/
}

int cmpSoketLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;

	/*comparison of variables*/
	if (case_1->socket > case_2->socket)
		cmp = 1;
	else if (case_1->socket < case_2->socket)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpFrequencyLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;

	/*comparison of variables*/
	if (case_1->frequency > case_2->frequency)
		cmp = 1;
	else if (case_1->frequency < case_2->frequency)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpFrequencyInTurboBoostLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;

	/*comparison of variables*/
	if (case_1->frequencyInTurboBoost > case_2->frequencyInTurboBoost)
		cmp = 1;
	else if (case_1->frequencyInTurboBoost < case_2->frequencyInTurboBoost)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpTechnologicalProcessLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;

	/*comparison of variables*/
	if (case_1->technologicalProcess > case_2->technologicalProcess)
		cmp = 1;
	else if (case_1->technologicalProcess < case_2->technologicalProcess)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpCacheLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const struct PROCESSOR_STRUCT* case_1 = v1;
	const struct PROCESSOR_STRUCT* case_2 = v2;

	/*comparison of variables*/
	if (case_1->cache[0] > case_2->cache[0])
		cmp = 1;
	else if (case_1->cache[0] < case_2->cache[0])
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int destroyList(PROCESSOR_STRUCT** processor)
{
	PROCESSOR_STRUCT* temp = *processor;
	int i = 0;

	while (temp != NULL)
	{
		/*memory allocation*/
		PROCESSOR_STRUCT_TEMP[i].name = malloc(50 * sizeof(char));
		if (!PROCESSOR_STRUCT_TEMP[i].name)
			exit(1);

		PROCESSOR_STRUCT_TEMP[i].nameGenerations = malloc(100 * sizeof(char));
		if (!PROCESSOR_STRUCT_TEMP[i].nameGenerations)
		{
			free(PROCESSOR_STRUCT_TEMP[i].name);
			exit(1);
		}

		PROCESSOR_STRUCT_TEMP[i].cache = (int*)malloc(3 * sizeof(int));
		if (!PROCESSOR_STRUCT_TEMP[i].cache)
		{
			free(PROCESSOR_STRUCT_TEMP[i].cache);
			exit(1);
		}

		
		strcpy(PROCESSOR_STRUCT_TEMP[i].name, temp->name);/*copying structure fields*/

		strcpy(PROCESSOR_STRUCT_TEMP[i].nameGenerations, temp->nameGenerations);/*copying structure fields*/

		PROCESSOR_STRUCT_TEMP[i].socket = temp->socket;/*copying structure fields*/
		PROCESSOR_STRUCT_TEMP[i].technologicalProcess = temp->technologicalProcess;/*copying structure fields*/
		PROCESSOR_STRUCT_TEMP[i].frequency = temp->frequency;/*copying structure fields*/
		PROCESSOR_STRUCT_TEMP[i].frequencyInTurboBoost = temp->frequencyInTurboBoost;/*copying structure fields*/

		for (int j = 0; j < MAXCACHE; j++)
			PROCESSOR_STRUCT_TEMP[i].cache[j] = temp->cache[j];/*copying structure fields*/

		temp = temp->next;
		i++;
	}


	return i;
}

PROCESSOR_STRUCT* createSortList(PROCESSOR_STRUCT* processor)
{
	/*declaration and initialization of variables*/
	int qualityNode = 0;
	int TMP = 0;
	int j = 0;

	while (PROCESSOR_STRUCT_TEMP[j].name != NULL)
	{
		qualityNode++;
		j++;
	}

	for (int i = 0; i < qualityNode; i++)
	{
		/*creating a list*/
		if (TMP == 0)
		{
			processor = init(PROCESSOR_STRUCT_TEMP[i].name, PROCESSOR_STRUCT_TEMP[i].nameGenerations, PROCESSOR_STRUCT_TEMP[i].socket,
				PROCESSOR_STRUCT_TEMP[i].technologicalProcess, PROCESSOR_STRUCT_TEMP[i].frequency, PROCESSOR_STRUCT_TEMP[i].frequencyInTurboBoost, PROCESSOR_STRUCT_TEMP[i].cache);
		}
		else
		{
			addFront(&processor, PROCESSOR_STRUCT_TEMP[i].name, PROCESSOR_STRUCT_TEMP[i].nameGenerations, PROCESSOR_STRUCT_TEMP[i].socket,
				PROCESSOR_STRUCT_TEMP[i].technologicalProcess, PROCESSOR_STRUCT_TEMP[i].frequency, PROCESSOR_STRUCT_TEMP[i].frequencyInTurboBoost, PROCESSOR_STRUCT_TEMP[i].cache);
		}

		TMP++;
	}


	return processor;
}

void SigBreak_Handler(int n_signal)
{
	FILE* tempFile;

	tempFile = fopen("temp_signal_data.bin", "rb");/*Serialization file covering*/
	if (tempFile == NULL)
	{
		perror("fopen");
		exit(3);
	}

	/*read structure*/
	SIGNAL_DATA signal_data;
	fread(&signal_data, sizeof(SIGNAL_DATA), 1, tempFile);
	fclose(tempFile);

	if (signal_data.processor != NULL) /*carrying out actions before closing*/
	{
		writeInFile(signal_data.processor, 2, signal_data.pathFile);
		remove("temp_signal_data.bin");
	}

}
