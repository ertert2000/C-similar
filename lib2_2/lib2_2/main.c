//Общее задание
//
//Для выбранной предметной области создать динамический массив структур, содержащих характеристики объектов предметной области.
//
//Обязательный набор полей :
//
//динамический массив символов, включая пробелы(name)
//
//произвольный динамический массив символов
//
//числовые поля типов int и float(не менее двух полей каждого типа)
//
//поле с числовым массивом.
//
//Написать программу, обеспечивающую начальное формирование массива структур при чтении из файла(текст с разделителями — CSV) с 
//последующим возможным дополнением элементов массива при вводе с клавиатуры.
//Следует использовать указатели на структуры и указатели на функции обработки массива в соответствии с вариантом задания.
//
//Во всех случаях, когда при поиске записей результат отсутствует, следует вывести сообщение.

//Выбор записей, в которых значение любого символьного поля(выбор из меню) 
//начинается с указанной подстроки без учета регистра, сортировка результата по убыванию значений последнего числового поля.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



typedef struct
{
	char *name;
	char *nameGenerations;
	int socket;
	int technologicalProcess;
	float frequency; //частота
	float frequencyInTurboBoost;
	int *cache;
}PROCESSOR;

void addInFile(PROCESSOR Processor);

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

PROCESSOR* addMemory(int size, int TMP, PROCESSOR*processor)
{
	char* temp;

	temp = realloc(processor, size * sizeof(PROCESSOR));
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

int main()
{
	PROCESSOR*processor;
	int size = 3;
	int TMP = 0;
	char buffer[1000];
	char* token;
	

	processor = (PROCESSOR*)malloc(size * sizeof(PROCESSOR));
	if (processor)
	{
		for (int i = 0; i<size; i++)
			processor[i].name = (char*)malloc(50 * sizeof(char));
		for (int i = 0; i < size; i++)
			processor[i].cache = (int*)malloc(3 * sizeof(int));
		for (int i = 0; i < size; i++)
			processor[i].nameGenerations = (char*)malloc(100 * sizeof(char));

		
		FILE* file;
		file = fopen("pros.csv", "r");
		if (file == NULL)
			exit(1);

		while (fgets(buffer, 1000, file) != NULL)
		{
			token = mystrtok(buffer, ";");
			strcpy(processor[TMP].name, token);
			
			token = mystrtok(NULL, ";");
			strcpy(processor[TMP].nameGenerations, token);

			token = mystrtok(NULL, ";");
			processor[TMP].socket = atoi(token);

			token = mystrtok(NULL, ";");
			processor[TMP].technologicalProcess = atoi(token);

			token = mystrtok(NULL, ";");
			processor[TMP].frequency = atof(token);

			token = mystrtok(NULL, ";");
			processor[TMP].frequencyInTurboBoost = atof(token);

			for (int i = 0; i < 3; i++)
			{
				token = mystrtok(NULL, ",");
				processor[TMP].cache[i] = atoi(token);
			}

			TMP++;
			if (TMP == size)
			{
				size *= 2;
				processor = addMemory(size, TMP, processor);
			}
		}


		for (int i = 0; i < TMP; i++)
		{
			printf("%s %s %d %d %f %f ", processor[i].name, processor[i].nameGenerations,
				processor[i].socket, processor[i].technologicalProcess, processor[i].frequency,
				processor[i].frequencyInTurboBoost);
			for (int j = 0; j < 3; j++)
				printf("%d ", processor[i].cache[j]);

			puts("");
		}

		free(processor);
	}

	
	return 0;
}

void addInFile(PROCESSOR Processor)
{
	FILE* file;
	file = fopen("pros.csv", "a");






	fclose(file);
}