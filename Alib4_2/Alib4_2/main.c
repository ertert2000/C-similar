//Перепроектировать структуру, созданную при выполнении лабораторной работы №7(по выбранной предметной области), так, чтобы одно из информационных полей,
//  содержащих характеристику группы объектов (издательство, модель, тип и т. п.), стало ссылкой на элемент двусвязного линейного списка  и выполнить задание 
// в соответствии с вариантом.
//
//Разработать подалгоритм и написать функцию, удаляющую в двусвязном списке заданный по номеру элемент. Номер элемента задается с конца списка. 
// При недостаточном количестве элементов в списке удалить элемент из начала списка (первый). При пустом списке вывести соответствующее сообщение.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int id;
	char* name;
	struct heder* next;
	struct heder* prev;
}heder;

typedef struct health_record
{
	heder* name;
	char* last_visit_date;
	int cholesterol_level;
	int blood_pressure;
	float average_sleep_hours;
	float physical_activity_level;
	int* medical_tests_results;
	struct health_record* next;
	struct health_record* prev;
} health_record;

typedef struct Head
{
	health_record* first_pos;
	health_record* last_pos;
} head;

heder* init_heder(int id, char* name)
{
	heder* node = (heder*)malloc(sizeof(heder));
	if (!node)
		exit(1);

	node->id = id;

	node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(node->name, name);

	node->next = NULL;
	node->prev = NULL;

	return node;
}


void add(head* head, health_record* cur_position, health_record* health_record)
{
	if (cur_position == NULL)
	{
		head->first_pos = health_record;
		head->last_pos = health_record;
	}

	else
	{
		cur_position->next = health_record;
		health_record->prev = cur_position;
		head->last_pos = health_record;
	}
}


void addHead(health_record* health_record, char* Name, heder** header)
{
	heder* cur_health_record, * prev_name;
	cur_health_record = *header;
	prev_name = NULL;

	while (cur_health_record != NULL)
	{
		if (strcmp(Name, cur_health_record->name) == 0)
			health_record->name = cur_health_record;


		prev_name = cur_health_record;
		cur_health_record = cur_health_record->next;
	}
	if (health_record->name == NULL)
	{
		cur_health_record = (heder*)malloc(sizeof(heder));
		cur_health_record->name = (char*)malloc(strlen(Name) + 1);
		if (cur_health_record->name == NULL)
		{
			printf("Memory allocation for name failed.\n");
			free(cur_health_record);
		}
		else
		{
			strcpy(cur_health_record->name, Name);
			if (prev_name != NULL)
				cur_health_record->id = prev_name->id + 1;

			else
				cur_health_record->id = 1;

			cur_health_record->prev = prev_name;
			cur_health_record->next = NULL;

			if (prev_name)
				prev_name->next = cur_health_record;

			else
				*header = cur_health_record;

			health_record->name = cur_health_record;
		}
	}
}


health_record* createNew(
	char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results,
	heder** header)
{
	health_record* newNode = NULL;

	newNode = (health_record*)malloc(sizeof(health_record));
	if (newNode)
	{
		newNode->name = malloc(sizeof(char) * 100);

		newNode->name = NULL;

		newNode->last_visit_date = (char*)malloc(sizeof(last_visit_date) * 100);
		strcpy(newNode->last_visit_date, last_visit_date);

		newNode->cholesterol_level = cholesterol_level;
		newNode->blood_pressure = blood_pressure;
		newNode->average_sleep_hours = average_sleep_hours;
		newNode->physical_activity_level = physical_activity_level;

		newNode->medical_tests_results = (int*)malloc(sizeof(medical_tests_results) * 3);
		for (int i = 0; i < 3; i++)
			newNode->medical_tests_results[i] = medical_tests_results[i];

		newNode->next = NULL;
		newNode->prev = NULL;

		addHead(newNode, name, header);
	}
	return newNode;
}


void readFromFile(head* head, heder** name)
{
	health_record* new_pos;

	char Name[100], last_visit_date[100];
	int cholesterol_level, blood_pressure;
	float average_sleep_hours, physical_activity_level;
	int medical_tests_results[3];
	char pathfile[100];

	FILE* f;

	printf("Enter the path to the file:");
	fgets(pathfile, 100, stdin);
	pathfile[strcspn(pathfile, "\n")] = '\0';

	f = fopen(pathfile, "r");
	if (!f)
		exit(1);

	if (f == NULL)
	{
		printf("Invalid file name \nEnter the path to the file again:\n");
		fgets(pathfile, 100, stdin);
		pathfile[strcspn(pathfile, "\n")] = '\0';
		f = fopen(pathfile, "r");
	}

	while (fscanf(f, "%[^;];%[^;];%d;%d;%f;%f;%d,%d,%d\n", Name, last_visit_date, &cholesterol_level, &blood_pressure, &average_sleep_hours,
		&physical_activity_level, &medical_tests_results[0], &medical_tests_results[1], &medical_tests_results[2]) == 9)
	{
		new_pos = createNew(Name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results, name);

		if (head->first_pos == NULL)
		{
			head->first_pos = new_pos;
			head->last_pos = new_pos;
		}
		else
			add(head, head->last_pos, new_pos);
	}
	fclose(f);
}


void deleteElementFromEnd(head* head, int num) 
{
	num--;
	if (head == NULL || head->first_pos == NULL)
	{
		printf("Empty list\n");
		return;
	}

	health_record* temp = head->last_pos;
	int count = 0;

	health_record* current = head->first_pos;
	while (current != NULL) {
		current = current->next;
		count++;
	}

	if (num > count) {
		printf("Index out of range\n");
		return;
	}
	for (int i = 0; i < num; i++)
		temp = temp->prev;

	if (temp->prev == NULL)
	{
		head->first_pos = temp->next;
		if (head->first_pos != NULL)
			head->first_pos->prev = NULL;
	}
	else
	{
		temp->prev->next = temp->next;
		if (temp->next != NULL)
			temp->next->prev = temp->prev;
	}
	free(temp->name);
	free(temp->last_visit_date);
	free(temp->medical_tests_results);
	free(temp);
}


void printList(health_record* health)
{
	int flag = 0;

	while (health != NULL)
	{
		flag += 1;
		if (flag == 1)
		{
			puts("|-----------------------------------------------------------------------------------------------------------|");
			puts("|id|Name       |last visit  |activity per hour|cholester |blood pressure|sleep per/hour|medical test results|");
			puts("|--------------+------------+-----------------+----------+--------------+--------------+--------------------|");
		}
		if (flag)
		{
			printf("|%d |%-10s | %-10s | %-15.3f | %-8d | %-12d | %-12.3f |", health->name->id, health->name->name, health->last_visit_date, health->physical_activity_level, health->cholesterol_level, health->blood_pressure, health->average_sleep_hours);
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
					printf("%-14d|", health->medical_tests_results[i]);
				else
					printf("%d, ", health->medical_tests_results[i]);
			}
			puts("");
		}

		health = health->next;
	}
}

int main()
{
	system("cls");
	int choice;

	head* Head = (head*)malloc(sizeof(head));

	Head->first_pos = NULL;
	Head->last_pos = NULL;
	heder* header = NULL;

	readFromFile(Head, &header);

	printList(Head->first_pos);

	printf("\n");

	printf("Enter the number of elements to delete from the end:\n");
	scanf("%d", &choice);

	deleteElementFromEnd(Head, choice);

	system("cls");

	printList(Head->first_pos);

	return 0;
}