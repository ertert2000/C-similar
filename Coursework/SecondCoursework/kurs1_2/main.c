/*Создать электронную картотеку, хранящуюся на диске, и программу, обеспечивающую взаимодействие с ней.

Программа должна выполнять следующие действия :

занесение данных в электронную картотеку;
внесение изменений(исключение, корректировка, добавление);
поиск данных по различным признакам;
сортировку по различным признакам;
вывод результатов на экран и сохранение на диске.
Выбор подлежащих выполнению команд должен быть реализован с помощью основного меню и вложенных меню.

Задача должна быть структурирована и отдельные части должны быть оформлены как функции.

Исходные данные должны вводиться с клавиатуры.В процессе обработки картотека должна храниться в памяти компьютера в виде списков и массивов структур, связанных указателями.Типы списков и структур выбираются исходя из предметной области.

Картотека составляется по выбранной предметной области.

В программе должно быть реализовано простейшее меню.Выполнение программы должно быть многократным по желанию пользователя.Данные первоначально считываются из файла(файлов), в процессе работы данные вводятся с клавиатуры.

Примерный перечень пунктов меню :

0 : Справка

1 : Добавление карточек об объектах предметной области

2 : Редактирование карточек

3 : Удаление карточек

4 : Вывод картотеки

5 : Поиск карточек по параметру

6 : Сортировка картотеки по параметру

7 : Выход

Дополнительно :
Программа должна быть работоспособна в Windows.Linux и Mac OS.

Варианты предметных областей для выполнения работы :

Люди(спортсмены, артисты …)
Покупатели
Пациенты
Здания, сооружения
Транспортные средства(автомобили, велосипеды …)
Фильмы
Медиа - каналы
Страны(государства)
Спортивные команды
Студенты могут предлагать свои варианты предметных областей.

* Программа должна обеспечивать устойчивую работу при ошибочном вводе(дополнительный бонус).*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCACHE 3

typedef struct PROCESSOR_STRUCT
{
	char* name;
	char* nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency; //       
	float frequencyInTurboBoost;
	int* cache;
	int* TMP;
	struct PROCESSOR_STRUCT* next;
	struct PROCESSOR_STRUCT* prev;
} PROCESSOR_STRUCT;

char* mystrtok(char* str, const char* delim) {
	static char* next;

	if (str) {
		next = str;
		while (*next && strchr(delim, *next))
			*next++ = '\0';
	}

	if (!*next) {
		str = NULL;

	}
	else {
		str = next;

		while (*next && !strchr(delim, *next)) {
			++next;
		}

		while (*next && strchr(delim, *next))
			*next++ = '\0';

	}

	return str;
}

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
	node->prev = NULL;
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

void writeInFileAndStruct(PROCESSOR_STRUCT** b, int choose)
{
	FILE* file;
	file = fopen("pros.csv", "a");
	if (file == NULL)
		exit(1);

	char name[50];
	char nameGenerations[100];
	char tempSocket[50];
	char tempTechnologicalProcess[50];
	char tempFrequency[50]; //       
	char tempFrequencyInTurboBoost[50];
	char tempCache[3];

	int socket;
	int technologicalProcess;
	float frequency;
	float frequencyInTurboBoost;
	int cache[3];

	PROCESSOR_STRUCT* temp = *b;

	FILE* newFile;

	switch (choose)
	{
	case 1:
		while ((getchar()) != '\n');
		puts("name");
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", name);

		puts("nameGenerations");
		fgets(nameGenerations, sizeof(nameGenerations), stdin);
		nameGenerations[strcspn(nameGenerations, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", nameGenerations);

		puts("socket");
		fgets(tempSocket, sizeof(tempSocket), stdin);
		tempSocket[strcspn(tempSocket, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", tempSocket);
		socket = atoi(tempSocket);

		puts("technologicalProcess");
		fgets(tempTechnologicalProcess, sizeof(tempTechnologicalProcess), stdin);
		tempTechnologicalProcess[strcspn(tempTechnologicalProcess, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", tempTechnologicalProcess);
		technologicalProcess = atoi(tempTechnologicalProcess);

		puts("frequency");
		fgets(tempFrequency, sizeof(tempFrequency), stdin);
		tempFrequency[strcspn(tempFrequency, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", tempFrequency);
		frequency = atof(tempFrequency);

		puts("frequencyInTurboBoost");
		fgets(tempFrequencyInTurboBoost, sizeof(tempFrequencyInTurboBoost), stdin);
		tempFrequencyInTurboBoost[strcspn(tempFrequencyInTurboBoost, "\n")] = "\0";  // Удаление символа новой строки
		fprintf(file, "%s;", tempFrequencyInTurboBoost);
		frequencyInTurboBoost = atof(tempFrequencyInTurboBoost);

		puts("cache");
		for (int i = 0; i < 3; i++) {
			memset(&tempCache[0], 0, sizeof(tempCache));
			fgets(tempCache, sizeof(tempCache), stdin);
			tempCache[strcspn(tempCache, "\n")] = "\0";  // Удаление символа новой строки
			fprintf(file, "%s", tempCache);
			if (i != 2) {
				fprintf(file, ",");
				while ((getchar()) != '\n');
			}

			cache[i] = atoi(tempCache);
		}
		fprintf(file, "\n");
		//while ((getchar()) != '\n');
		///*--------одно начало--------*/
		//puts("name");
		//fgets(name, 50, stdin);
		//fprintf(file, name);
		//fputs(";", file); // поменять потом

		////while ((getchar()) != '\n');
		///*--------одно конц--------*/
		//puts("nameGenerations");
		//fgets(nameGenerations, 100, stdin);
		//fputs(nameGenerations, file);
		//fputs(";", file); // поменять потом


		//puts("socket");
		//fgets(tempSocket, 50, stdin);
		//fputs(tempSocket, file);
		//fputs(";", file); // поменять потом
		//socket = atoi(tempSocket);

		//puts("technologicalProcess");
		//fgets(tempTechnologicalProcess, 50, stdin);
		//fputs(tempTechnologicalProcess, file);
		//fputs(";", file); // поменять потом
		//technologicalProcess = atoi(tempTechnologicalProcess);

		////while ((getchar()) != '\n');
		//puts("frequency");
		//fgets(tempFrequency, 50, stdin);
		//fputs(tempFrequency, file);
		//fputs(";", file); // поменять потом
		//frequency = atof(tempFrequency);


		////while ((getchar()) != '\n');
		//puts("frequencyInTurboBoost");
		//fgets(tempFrequencyInTurboBoost, 50, stdin);
		//fputs(tempFrequencyInTurboBoost, file);
		//fputs(";", file); // поменять потом
		//frequencyInTurboBoost = atof(tempFrequencyInTurboBoost);

		//puts("cache");
		//for (int i = 0; i < 3; i++)
		//{
		//	//char tempCache[3];
		//	memset(&tempCache[0], 0, sizeof(tempCache));
		//	fgets(tempCache, 3, stdin);
		//	fputs(tempCache, file);
		//	if (i != 2)
		//	{
		//		fputs(",", file);
		//		while ((getchar()) != '\n');
		//	}

		//	cache[i] = atoi(tempCache);
		//	//*tempCache = NULL;
		//	//free(tempCache);
		//}
		//fputs("\n", file);

		addFront(&temp, name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);
		break;
	case 2:
		remove(file);
		newFile = fopen("pros.csv", "w+");
		while (temp->next != NULL)
		{
			fputs(temp->name, newFile);
			fputs(";", newFile); // поменять потом

			/*--------одно конц--------*/
			fputs(temp->nameGenerations, newFile);
			fputs(";", newFile); // поменять потом


			fputs(temp->socket, newFile);
			fputs(";", newFile); // поменять потом

			fputs(temp->technologicalProcess, newFile);
			fputs(";", newFile); // поменять потом


			fprintf(newFile,"%f", temp->frequency);
			fputs(";", newFile); // поменять потом

			fprintf(newFile, "%f", temp->frequencyInTurboBoost);
			fputs(";", newFile); // поменять потом

			for (int i = 0; i < 3; i++)
			{
				fputs(cache[i], newFile);
				if (i != 2)
					fputs(",", newFile);
			}
			fputs("\n", newFile);

			temp = temp->next;
		}
		fclose(newFile);
		break;
	}

	fclose(file);
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
			puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");//!!!!!!!!!!!!!!!!! id !!!!!!!!!!!!!!!!!
			puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
		}
		if (flag)
		{
			printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", processor->name, processor->nameGenerations,
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

		processor = processor->next;
	}
}

void serchByA(PROCESSOR_STRUCT** b, char* serch)
{
	int flag = 0;
	PROCESSOR_STRUCT* temp = *b;



	while (temp->next != NULL)
	{
		if (tolower(serch) == tolower(temp->name))
		{
			flag += 1;
			if (flag == 1)
			{
				puts("|-----------------------------------------------------------------------------------------------|");
				puts("|Name processor         |Generations |Socket    |Tech.Proc.|Frequency   |Turbo Boost |Cache     |");//!!!!!!!!!!!!!!!!! id !!!!!!!!!!!!!!!!!
				puts("|-----------------------+------------+----------+----------+------------+------------+----------|");
			}
			if (flag)
			{
				printf("|%-22s | %-10s | %-8d | %-8d | %-10.3f | %-10.3f |", temp->name, temp->nameGenerations,
					temp->socket, temp->technologicalProcess, temp->frequency,
					temp->frequencyInTurboBoost);
				for (int i = 0; i < 3; i++)
				{
					if (i == 2)
						printf("%-4d|", temp->cache[i]);
					else
						printf("%d, ", temp->cache[i]);

				}
				puts("");
			}

			temp = temp->next;
		}
	}
}

void printHelp()
{
	puts("");
	puts("");
	puts("");

}

void reactStruct(PROCESSOR_STRUCT** b, int serch)
{
	PROCESSOR_STRUCT* temp = *b;
	int i = 1;

	char name[50];
	char nameGenerations[100];
	int socket;
	int technologicalProcess;
	float frequency; //       
	float frequencyInTurboBoost;
	int cache[3];

	while (temp != NULL)
	{
		if (i == serch)
		{
			free(temp->name);
			free(temp->nameGenerations);
			free(temp->cache);

			while ((getchar()) != '\n');
			puts("name");
			fgets(name, 50, stdin);
			name[strcspn(name, "\n")] = "\0";
			strcpy(temp->name, name);

			//while ((getchar()) != '\n');
			puts("nameGenerations");
			fgets(nameGenerations, 100, stdin);
			nameGenerations[strcspn(nameGenerations, "\n")] = "\0";
			strcpy(temp->nameGenerations, nameGenerations);

			puts("socket");
			scanf("%d", &socket);
			temp->socket = socket;

			puts("technologicalProcess");
			scanf("%d", &technologicalProcess);
			temp->technologicalProcess = technologicalProcess;

			puts("frequency");
			scanf("%f", &frequency);
			temp->frequency = frequency;

			puts("frequencyInTurboBoost");
			scanf("%f", &frequencyInTurboBoost);
			temp->frequencyInTurboBoost = frequencyInTurboBoost;

			puts("cache");
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

void removeChoseCard(PROCESSOR_STRUCT** processor, int remove)
{
	/*PROCESSOR_STRUCT* temp = *processor;
	int serchRemoveCard = -1;
	int TMP = remove - 3;

	while (serchRemoveCard != TMP)
	{
		temp = temp->next;
		serchRemoveCard++;
	}
	
	free(temp->next->name);
	free(temp->next->nameGenerations);
	free(temp->next->cache);
	free(temp->next);


	temp->next = temp->next->next;*/

	if (processor == NULL || *processor == NULL)
		return;  // List is empty or invalid pointer

	PROCESSOR_STRUCT* temp = *processor;
	PROCESSOR_STRUCT* prev = NULL;
	int searchRemoveCard = 1;

	// If the node to be removed is the head node
	if (remove == 0) {
		*processor = temp->next;
		free(temp->name);
		free(temp->nameGenerations);
		free(temp->cache);
		free(temp);
		return;
	}

	// Traverse the list to find the node to remove
	while (temp != NULL && searchRemoveCard != remove) 
	{
		prev = temp;
		temp = temp->next;
		searchRemoveCard++;
	}

	// If the node to remove was not found
	if (temp == NULL)
		return;

	// Remove the node
	if (prev != NULL) 
		prev->next = temp->next;


	free(temp->name);
	free(temp->nameGenerations);
	free(temp->cache);
	free(temp);

	//возможно понадобится изменение файла

	//writeInFileAndStruct(&processor, 2);
}



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



int main()
{

	PROCESSOR_STRUCT* B = NULL;
	int serch;
	int remove;

	B = addInSruct(B);

	int choice, choiceFound, choiceSort;


	while (1)
	{


		scanf("%d", &choice);

		switch (choice)
		{
		case 0: //help  ^
			printHelp();
			break;
		case 1://Добавление карточек об объектах предметной области ^
			writeInFileAndStruct(&B, 1);
			break;
		case 2://Редактирование карточек +-
			scanf("%d", &serch);

			reactStruct(&B, serch);
			break;
		case 3://Удаление карточек   ^
			scanf("%d", &remove);

			removeChoseCard(&B, remove);
			break;
		case 4://Вывод картотеки    ^
			printNode(B);
			break;
		case 5://Поиск карточек по параметру    
			scanf("%d", &choiceFound);
			switch (choiceFound)
			{ //кол-во параметров
			default:
				break;
			}
			break;
		case 6://Сортировка картотеки по параметру
			scanf("%d", &choiceSort);
			switch (choiceSort)
			{ //кол-во параметров
			default:
				break;
			}
			break;
		case 7://Выход

			return 0;
			break;
		default://
			break;
		}
	}
	

}
