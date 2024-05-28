#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define MAXCACHE 3

#ifdef _WIN32
#define clear() system("cls");
#else
#define clear() system("clear");
#endif // linux

typedef struct health_record
{
	char* name;
	char* last_visit_date;
	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours;
	float physical_activity_level;
	int* medical_tests_results;
	int TMP;
	struct health_record* next;
	struct health_record* prev;
} health_record;

struct health_record_temp
{
	char* name;
	char* last_visit_date;
	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours;
	float physical_activity_level;
	int* medical_tests_results;
	int TMP;
	struct health_record* next;
	struct health_record* prev;
} health_record_t[200];

char* mystrtok(char* str, const char* delim);

health_record* init(char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results);

void addFront(health_record** record,
	char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results);

void printHeadTable();

void writeInFileAndStruct(health_record** b, int choose, char* pathfile);

void printNode(health_record* record);

void searchByName(health_record** records, char* search, int choose);

void searchBySleepHours(health_record** records, float search, int choose);

void searchByCholesterol(health_record** records, int search, int choose);

void printHelp();

void reactStruct(health_record** b, int serch);

void removeChoseCard(health_record** record, int remove, char* pathfile);

health_record* addInSruct(health_record* record, char* pathfile);

int cmpLastVisitDateLineal(const void* v1, const void* v2);

int cmpNameLineal(const void* v1, const void* v2);

int cmpCholesterolLevelLineal(const void* v1, const void* v2);

int cmpBloodPressureLineal(const void* v1, const void* v2);

int cmpAverageSleepHoursLineal(const void* v1, const void* v2);

int cmpPhysicalActivityLevelLineal(const void* v1, const void* v2);

int cmpMedicalTestsResultsLineal(const void* v1, const void* v2);

int destroyList(health_record** record);

health_record* createSortList(health_record* record);

int main()
{
	health_record* B = NULL;
	int serch;
	int remove;
	int i;
	int serchCholesterolAndBlood;

	char serchName[100];
	char pathfile[100];

	float serchSleep;

	FILE* file;

	printf("Enter the path to the file:");
	fgets(pathfile, 100, stdin);
	pathfile[strcspn(pathfile, "\n")] = '\0';

	file = fopen(pathfile, "r");

	while (!file)
	{
		printf("Invalid file name \nEnter the path to the file again:\n");
		fgets(pathfile, 100, stdin);
		pathfile[strcspn(pathfile, "\n")] = '\0';
		file = fopen(pathfile, "r");
		system("cls");
	}

	fclose(file);
	system("cls");

	B = addInSruct(B, pathfile);

	int choice, choiceFound, choiceSort;


	while (1)
	{

		puts("#========================================#");
		puts("0 - Help");
		puts("1 - Adding cards about domain objects");
		puts("2 - Editing cards");
		puts("3 - Removing cards");
		puts("4 - Card index output");
		puts("5 - Search for cards by parameter");
		puts("6 - Sorting a file cabinet by parameter");
		puts("7 - Exit");
		puts("#========================================#");

		scanf("%d", &choice);

		clear();
		switch (choice)
		{
		case 0: //help  ^
			printHelp();
			system("pause");
			clear();
			break;
		case 1://Adding cards about domain objects ^
			writeInFileAndStruct(&B, 1, pathfile);
			clear();
			break;
		case 2://Editing cards +-
			puts("Enter the id of the element you want to change");
			scanf("%d", &serch);


			reactStruct(&B, serch);
			clear();
			break;
		case 3://Removing cards   ^
			puts("Enter the id of the element you want to delete");
			scanf("%d", &remove);

			removeChoseCard(&B, remove, pathfile);
			clear();
			break;

		case 4://Card index output    ^
			printNode(B);
			system("pause");
			clear();
			break;
		case 5://Search for cards by parameter

			puts("#======================================#");
			puts("1 - Search by name");
			puts("2 - Search by last Visit Date");
			puts("3 - Search by Cholesterol Level");
			puts("4 - Search by Blood Pressure");
			puts("5 - Search by Average Sleep Hours");
			puts("6 - Search by Physical Activity Level");
			puts("7 - Search by cache");
			puts("#======================================#");

			scanf("%d", &choiceFound);

			switch (choiceFound)
			{ //number of parameters   
			case 1:
				puts("Enter your name:");
				while ((getchar()) != '\n');
				fgets(serchName, 100, stdin);

				searchByName(&B, serchName, choiceFound);
				break;
			case 2:
				puts("Enter the date of your last visit:");
				while ((getchar()) != '\n');
				fgets(serchName, 100, stdin);

				searchByName(&B, serchName, choiceFound);
				break;
			case 3:
				puts("Enter your chalestyrine level:");
				scanf("%d", &serchCholesterolAndBlood);
				searchByCholesterol(&B, serchCholesterolAndBlood, 5);
				break;
			case 4:
				puts("Enter blood pressure:");
				scanf("%d", &serchCholesterolAndBlood);
				searchByCholesterol(&B, serchCholesterolAndBlood, 6);
				break;
			case 5:
				puts("Enter average sleep hours:");
				scanf("%f", &serchSleep);
				searchBySleepHours(&B, serchSleep, 3);
				break;
			case 6:
				puts("Enter physical activity level:");
				scanf("%f", &serchSleep);
				searchBySleepHours(&B, serchSleep, 4);
				break;
			case 7:
				puts("Enter medical tests results:");
				scanf("%d", &serchCholesterolAndBlood);
				searchByCholesterol(&B, serchCholesterolAndBlood, 7);
				break;
			}
			system("pause");
			clear();
			break;
		case 6://Sorting a file cabinet by parameter ^

			puts("#======================================#");
			puts("1 - Sort by name");
			puts("2 - Sort by last Visit Date");
			puts("3 - Sort by Physical Activity Level");
			puts("4 - Sort by Cholesterol Level");
			puts("5 - Sort by Blood Pressure");
			puts("6 - Sort by Average Sleep Hours");
			puts("7 - Sort by medical test results");
			puts("#======================================#");

			scanf("%d", &choiceSort);

			switch (choiceSort)
			{ //number of parameters
			case 1:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpNameLineal);
				B = createSortList(B);
				break;
			case 2:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpLastVisitDateLineal);
				B = createSortList(B);
				break;
			case 3:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpPhysicalActivityLevelLineal);
				B = createSortList(B);
				break;
			case 4:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpCholesterolLevelLineal);
				B = createSortList(B);
				break;
			case 5:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpBloodPressureLineal);
				B = createSortList(B);
				break;
			case 6:
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpAverageSleepHoursLineal);
				B = createSortList(B);
				break;
			case 7: //тута еще
				i = destroyList(&B);
				qsort(health_record_t, i, sizeof(struct health_record_temp), cmpMedicalTestsResultsLineal);
				B = createSortList(B);
				break;
			}
			clear();
			break;
		case 7://Exit
			writeInFileAndStruct(&B, 2, pathfile);
			return 0;
			break;
		default://
			break;
		}
	}


}


char* mystrtok(char* str, const char* delim) 
{
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

health_record* init(char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results)
{
	health_record* node = (health_record*)malloc(sizeof(health_record));
	if (!node)
		exit(1);

	node->name = malloc((strlen(name) + 1) * sizeof(char));
	if (!node->name) {
		free(node);
		exit(1);
	}
	strcpy(node->name, name);

	node->last_visit_date = malloc((strlen(last_visit_date) + 1) * sizeof(char));
	if (!node->last_visit_date) {
		free(node->name);
		free(node);
		exit(1);
	}
	strcpy(node->last_visit_date, last_visit_date);

	node->cholesterol_level = cholesterol_level;
	node->blood_pressure = blood_pressure;
	node->average_sleep_hours = average_sleep_hours;
	node->physical_activity_level = physical_activity_level;

	node->medical_tests_results = (int*)malloc(3 * sizeof(int));
	if (!node->medical_tests_results)
	{
		free(node->medical_tests_results);
		free(node);
		exit(1);
	}
	for (int i = 0; i < 3; i++)
		node->medical_tests_results[i] = medical_tests_results[i];

	node->next = NULL;
	node->prev = NULL;
	return node;
}

// Функция для добавления новой записи в начало списка
void addFront(health_record** record,
	char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results)
{
	health_record* newNode = init(name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);

	health_record* temp = *record;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newNode;
}

void printHeadTable()
{

	puts("|-----------------------------------------------------------------------------------------------------------|");
	puts("|id|Name       |last visit  |cholester|blood pressure |sleep per/hour|activity per hour|medical test results|");
	puts("|--------------+------------+-----------------+----------+--------------+--------------+--------------------|");
}

// Функция для записи данных в файл и структуру
void writeInFileAndStruct(health_record** b, int choose, char* pathfile)
{
	FILE* file;
	file = fopen(pathfile, "a");
	if (file == NULL)
		exit(1);

	char name[50];
	char last_visit_date[100];
	char tempCholesterolLevel[50];
	char tempBloodPressure[50];
	char tempAverageSleepHours[50];
	char tempPhysicalActivityLevel[50];
	char tempMedicalTestsResults[3];

	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours;
	float physical_activity_level;
	int medical_tests_results[3];

	health_record* temp = *b;

	FILE* newFile;

	switch (choose)
	{
	case 1:
		while ((getchar()) != '\n');
		puts("Name:");
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", name);

		puts("Last Visit Date:");
		fgets(last_visit_date, sizeof(last_visit_date), stdin);
		last_visit_date[strcspn(last_visit_date, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", last_visit_date);

		puts("Cholesterol Level:");
		fgets(tempCholesterolLevel, sizeof(tempCholesterolLevel), stdin);
		tempCholesterolLevel[strcspn(tempCholesterolLevel, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", tempCholesterolLevel);
		cholesterol_level = atoi(tempCholesterolLevel);

		puts("Blood Pressure:");
		fgets(tempBloodPressure, sizeof(tempBloodPressure), stdin);
		tempBloodPressure[strcspn(tempBloodPressure, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", tempBloodPressure);
		blood_pressure = atoi(tempBloodPressure);

		puts("Average Sleep Hours:");
		fgets(tempAverageSleepHours, sizeof(tempAverageSleepHours), stdin);
		tempAverageSleepHours[strcspn(tempAverageSleepHours, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", tempAverageSleepHours);
		average_sleep_hours = atof(tempAverageSleepHours);

		puts("Physical Activity Level:");
		fgets(tempPhysicalActivityLevel, sizeof(tempPhysicalActivityLevel), stdin);
		tempPhysicalActivityLevel[strcspn(tempPhysicalActivityLevel, "\n")] = '\0';  // Удаление символа новой строки
		fprintf(file, "%s;", tempPhysicalActivityLevel);
		physical_activity_level = atof(tempPhysicalActivityLevel);

		puts("Medical Tests Results:");
		for (int i = 0; i < 3; i++)
		{
			memset(&tempMedicalTestsResults[0], 0, sizeof(tempMedicalTestsResults));
			fgets(tempMedicalTestsResults, sizeof(tempMedicalTestsResults), stdin);
			tempMedicalTestsResults[strcspn(tempMedicalTestsResults, "\n")] = '\0';  // Удаление символа новой строки
			fprintf(file, "%s", tempMedicalTestsResults);
			if (i != 2)
			{
				fprintf(file, ",");
				//while ((getchar()) != '\n');
			}

			medical_tests_results[i] = atoi(tempMedicalTestsResults);
		}
		fprintf(file, "\n");

		addFront(&temp, name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);
		break;
	case 2:
		remove(file);
		newFile = fopen(pathfile, "w+");
		while (temp != NULL)
		{
			fprintf(newFile, "%s;", temp->name);

			fprintf(newFile, "%s;", temp->last_visit_date);

			fprintf(newFile, "%d;", temp->cholesterol_level);

			fprintf(newFile, "%d;", temp->blood_pressure);

			fprintf(newFile, "%.3f;", temp->average_sleep_hours);

			fprintf(newFile, "%.3f;", temp->physical_activity_level);

			for (int i = 0; i < 3; i++)
			{
				fprintf(newFile, "%d", temp->medical_tests_results[i]);
				if (i != 2)
					fprintf(newFile, ",");
			}

			fprintf(newFile, "\n");

			temp = temp->next;
		}
		fclose(newFile);
		break;
	}

	fclose(file);
}


void printNode(health_record* record)
{
	int flag = 0;
	int id = 0;

	while (record != NULL)
	{
		flag += 1;
		if (flag == 1)
		{
			printHeadTable();
		}
		if (flag)
		{
			printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, record->name, record->last_visit_date, record->cholesterol_level, record->blood_pressure, record->average_sleep_hours, record->physical_activity_level);
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
					printf("%-14d|", record->medical_tests_results[i]);
				else
					printf("%d, ", record->medical_tests_results[i]);
			}
			puts("");
		}
		id++;

		record = record->next;
	}
}

void searchByName(health_record** records, char* search, int choose)
{
	int flag = 0;
	int id = 0;
	health_record* temp = *records;

	char tempName[50];
	char searchName[50];
	search[strcspn(search, "\n")] = '\0';
	for (int i = 0; search[i]; i++)
		search[i] = tolower(search[i]);
	switch (choose)
	{
	case 1:
		while (temp != NULL)
		{
			memset(&tempName[0], 0, 50);
			strcpy(tempName, temp->name);
			for (int i = 0; tempName[i]; i++)
				tempName[i] = tolower(tempName[i]);
			if (!strcmp(search, tempName))
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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
			strcpy(tempName, temp->last_visit_date);
			for (int i = 0; tempName[i]; i++)
				tempName[i] = tolower(tempName[i]);
			if (!strcmp(search, tempName))
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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

void searchBySleepHours(health_record** records, float search, int choose)
{
	int flag = 0;
	int id = 0;
	health_record* temp = *records;

	switch (choose)
	{
	case 3:
		while (temp != NULL)
		{
			if (round(search * 10) / 10 == round(temp->average_sleep_hours * 10) / 10)
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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
			if (round(search * 10) / 10 == round(temp->physical_activity_level * 10) / 10)
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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

void searchByCholesterol(health_record** records, int search, int choose)
{
	int flag = 0;
	int flagMedTest = 0;
	int id = 0;
	health_record* temp = *records;

	switch (choose)
	{
	case 5:
		while (temp != NULL)
		{
			if (search == temp->cholesterol_level)
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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
			if (search == temp->blood_pressure)
			{
				flag += 1;
				if (flag == 1)
				{
					printHeadTable();
				}
				if (flag)
				{
					printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
					for (int i = 0; i < 3; i++)
					{
						if (i == 2)
							printf("%-14d|", temp->medical_tests_results[i]);
						else
							printf("%d, ", temp->medical_tests_results[i]);
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

			for (int i = 0; i < 3 && flagMedTest == 0; i++)
				if (search == temp->medical_tests_results[i])
				{
					flagMedTest = 1;
					flag += 1;
					if (flag == 1)
					{
						printHeadTable();
					}
					if (flag)
					{
						printf("|%d |%-10s | %-10s | %-7d | %-13d | %-15.3f | %-12.3f |", id, temp->name, temp->last_visit_date, temp->cholesterol_level, temp->blood_pressure, temp->average_sleep_hours, temp->physical_activity_level);
						for (int i = 0; i < 3; i++)
						{
							if (i == 2)
								printf("%-14d|", temp->medical_tests_results[i]);
							else
								printf("%d, ", temp->medical_tests_results[i]);
						}
						puts("");
					}
					id++;
				}
			flagMedTest = 0;
			temp = temp->next;
		}
		break;
	}
}

void printHelp()
{
	printf("This program is a database management system designed to store information about objects in the subject area. Here is a brief description of the main functions of the program:\n1. Adding domain object cards: This feature allows users to add new records about objects or entities to the database.\n2. Edit Cards: With this feature, users can make changes to existing cards, correct errors, or update information.\n3. Delete cards: this option allows you to delete unnecessary cards from the database.\n4. Card index output: the function displays the contents of the subject area object cards for viewing.\n5. Search cards by parameter: With this feature, users can search cards by specific parameters to quickly find the information they need.\n6. Sorting Card Index by Parameter: This option allows the user to sort cards in the database by a specified parameter, such as date, title, or other key indicator.\n7. Exit: Exit the program.\nThis program provides convenient database management and processing of information about objects in the subject area.");
}

void reactStruct(health_record** b, int serch)
{
	health_record* temp = *b;
	int i = 1;

	char name[50];
	char last_visit_date[100];
	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours; //       
	float physical_activity_level;
	int medical_tests_results[3];

	while (temp != NULL)
	{
		if (i == serch)
		{
			//free(temp->name);
			//free(temp->last_visit_date);
			//free(temp->medical_tests_results);

			while ((getchar()) != '\n');
			puts("name");
			fgets(name, 50, stdin);
			name[strcspn(name, "\n")] = '\0';
			strcpy(temp->name, name);

			puts("last_visit_date");
			fgets(last_visit_date, 100, stdin);
			last_visit_date[strcspn(last_visit_date, "\n")] = '\0';
			strcpy(temp->last_visit_date, last_visit_date);

			puts("cholesterol_level");
			scanf("%d", &cholesterol_level);
			temp->cholesterol_level = cholesterol_level;

			puts("blood_pressure");
			scanf("%d", &blood_pressure);
			temp->blood_pressure = blood_pressure;

			puts("average_sleep_hours");
			scanf("%f", &average_sleep_hours);
			temp->average_sleep_hours = average_sleep_hours;

			puts("physical_activity_level");
			scanf("%f", &physical_activity_level);
			temp->physical_activity_level = physical_activity_level;

			puts("medical_tests_results");
			for (int i = 0; i < 3; i++)
			{
				scanf("%d", &medical_tests_results[i]);
				temp->medical_tests_results[i] = medical_tests_results[i];
			}
		}

		i++;
		temp = temp->next;
	}
}

void removeChoseCard(health_record** record, int remove, char* pathfile)
{
	if (record == NULL || *record == NULL)
		return;  // List is empty or invalid pointer

	health_record* temp = *record;
	health_record* prev = NULL;
	int searchRemoveCard = 1;

	// If the node to be removed is the head node
	if (remove == 1) {
		*record = temp->next;
		free(temp->name);
		free(temp->last_visit_date);
		free(temp->medical_tests_results);
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

	temp = temp->next;

	free(prev->next->name);
	free(prev->next->last_visit_date);
	free(prev->next->medical_tests_results);
	free(prev->next);

	prev->next = temp;

}

health_record* addInSruct(health_record* record, char* pathfile)
{
	int TMP = 0;
	char buffer[1000];
	char* token;

	char* name;
	char* last_visit_date;
	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours;
	float physical_activity_level;
	int* medical_tests_results;

	name = (char*)malloc(50 * sizeof(char));
	last_visit_date = (char*)malloc(100 * sizeof(char));
	medical_tests_results = (int*)malloc(3 * sizeof(int));

	FILE* file;
	file = fopen(pathfile, "r");
	if (file == NULL)
		exit(1);
	while (fgets(buffer, 1000, file) != NULL)
	{

		token = mystrtok(buffer, ";");
		strcpy(name, token);

		token = mystrtok(NULL, ";");
		strcpy(last_visit_date, token);

		token = mystrtok(NULL, ";");
		cholesterol_level = atoi(token);

		token = mystrtok(NULL, ";");
		blood_pressure = atoi(token);

		token = mystrtok(NULL, ";");
		average_sleep_hours = atof(token);

		token = mystrtok(NULL, ";");
		physical_activity_level = atof(token);

		for (int i = 0; i < 3; i++)
		{
			token = mystrtok(NULL, ",");
			medical_tests_results[i] = atoi(token);
		}

		if (TMP == 0)
		{
			record = init(name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);
			record->TMP = 0;
		}
		else
			addFront(&record, name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);

		TMP++;
		record->TMP++;
	}

	fclose(file);
	free(name);
	free(last_visit_date);
	free(medical_tests_results);
	return record;
}

int cmpNameLineal(const void* v1, const void* v2)
{
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;
	return strcmp(case_1->name, case_2->name);
}

int cmpLastVisitDateLineal(const void* v1, const void* v2)
{
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;
	return strcmp(case_1->last_visit_date, case_2->last_visit_date);
}

int cmpCholesterolLevelLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;

	if (case_1->cholesterol_level > case_2->cholesterol_level)
		cmp = 1;
	else if (case_1->cholesterol_level < case_2->cholesterol_level)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpBloodPressureLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;

	if (case_1->blood_pressure > case_2->blood_pressure)
		cmp = 1;
	else if (case_1->blood_pressure < case_2->blood_pressure)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpAverageSleepHoursLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;

	if (case_1->average_sleep_hours > case_2->average_sleep_hours)
		cmp = 1;
	else if (case_1->average_sleep_hours < case_2->average_sleep_hours)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpPhysicalActivityLevelLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;

	if (case_1->physical_activity_level > case_2->physical_activity_level)
		cmp = 1;
	else if (case_1->physical_activity_level < case_2->physical_activity_level)
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int cmpMedicalTestsResultsLineal(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;

	if (case_1->medical_tests_results[0] > case_2->medical_tests_results[0])
		cmp = 1;
	else if (case_1->medical_tests_results[0] < case_2->medical_tests_results[0])
		cmp = -1;
	else
		cmp = 0;

	return cmp;
}

int destroyList(health_record** record)
{
	health_record* temp = *record;
	int i = 0;

	while (temp != NULL)
	{
		health_record_t[i].name = malloc(50 * sizeof(char));
		if (!health_record_t[i].name)
			exit(1);

		health_record_t[i].last_visit_date = malloc(100 * sizeof(char));
		if (!health_record_t[i].last_visit_date)
		{
			free(health_record_t[i].name);
			exit(1);
		}

		health_record_t[i].medical_tests_results = (int*)malloc(3 * sizeof(int));
		if (!health_record_t[i].medical_tests_results)
		{
			free(health_record_t[i].medical_tests_results);
			exit(1);
		}

		strcpy(health_record_t[i].name, temp->name);

		strcpy(health_record_t[i].last_visit_date, temp->last_visit_date);

		health_record_t[i].cholesterol_level = temp->cholesterol_level;
		health_record_t[i].blood_pressure = temp->blood_pressure;
		health_record_t[i].average_sleep_hours = temp->average_sleep_hours;
		health_record_t[i].physical_activity_level = temp->physical_activity_level;

		for (int j = 0; j < 3; j++)
			health_record_t[i].medical_tests_results[j] = temp->medical_tests_results[j];

		temp = temp->next;
		i++;
	}

	return i;
}

health_record* createSortList(health_record* record)
{
	int qualityNode = 0;
	int TMP = 0;
	int j = 0;

	while (health_record_t[j].name != NULL)
	{
		qualityNode++;
		j++;
	}

	for (int i = 0; i < qualityNode; i++)
	{
		if (TMP == 0)
		{
			record = init(health_record_t[i].name, health_record_t[i].last_visit_date, health_record_t[i].cholesterol_level,
				health_record_t[i].blood_pressure, health_record_t[i].average_sleep_hours, health_record_t[i].physical_activity_level, health_record_t[i].medical_tests_results);
		}
		else
		{
			addFront(&record, health_record_t[i].name, health_record_t[i].last_visit_date, health_record_t[i].cholesterol_level,
				health_record_t[i].blood_pressure, health_record_t[i].average_sleep_hours, health_record_t[i].physical_activity_level, health_record_t[i].medical_tests_results);
		}

		TMP++;
	}

	return record;
}
