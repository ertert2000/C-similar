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




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int a;
} b;

void writeInFileAndStruct(b* b)
{
	FILE* file;
	file = fopen("proc.csv", "a");
	if (file == NULL)
		exit(1);

	char a[5];


	/*--------одно начало--------*/
	puts("");
	scanf("%s", &a);
	fputs(a, file);
	fputs(";\n", file); // поменять потом
	b[0].a = atoi(a);
	/*--------одно конц--------*/






	fclose(file);
}

void printTable(b* b)
{
	printf("%d",b[0].a);

}

void serchByA(b* b, char* serch)
{
	for(int i = 0;i < 10; i++)
		if (tolower(serch) == b[i].a)
			printf("%d", b[i].a);
}

void printHelp()
{
	puts("");
	puts("");
	puts("");

}

void reactStruct(b* b, int serch)
{
	for (int i = 0; i < b.size(); i++)
		if (i == serch)
		{
			FILE* file;
			file = fopen("proc.csv", "a");
			if (file == NULL)
				exit(1);

			char a[5];


			/*--------одно начало--------*/
			puts("");
			scanf("%s", &a);
			fputs(a, file);
			fputs(";\n", file); // поменять потом
			b[i].a = atoi(a);



			fclose(file);
		}
}

void removeChoseCard(int remove)
{

	for (int i = 0; i < b.size(); i++)
		if (i == remove)
		{
			free(b[i].a);
		}




}

b* readInStruct(b* processor)
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

	b* B = NULL;
	int serch;
	int remove;

	int choice, choiceFound, choiceSort;

	scanf("%d", &choice);

	switch (choice)
	{
	case 0: //help
		printHelp();
		break;
	case 1://Добавление карточек об объектах предметной области
		writeInFileAndStruct(B);
		break;
	case 2://Редактирование карточек
		scanf("%d", &serch);
		
		reactStruct(B, serch);
		break;
	case 3://Удаление карточек
		scanf("%d", &remove);

		removeChoseCard(remove);
		break;
	case 4://Вывод картотеки
		printTable(B);
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
