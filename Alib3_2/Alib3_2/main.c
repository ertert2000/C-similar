#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* last_visit_date;
    int cholesterol_level;
    int blood_pressure;
    float average_sleep_hours;
    float physical_activity_level;
    int* medical_tests_results;
	struct health_record* next;
} health_record;

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

    node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(node->name, name);

    node->last_visit_date = (char*)malloc((strlen(last_visit_date) + 1) * sizeof(char));
    strcpy(node->last_visit_date, last_visit_date);

    node->cholesterol_level = cholesterol_level;
    node->blood_pressure = blood_pressure;
    node->average_sleep_hours = average_sleep_hours;
    node->physical_activity_level = physical_activity_level;

    node->medical_tests_results = (int*)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++)
        node->medical_tests_results[i] = medical_tests_results[i];

    node->next = NULL;
    return node;
}

void add(health_record** health,
	char* name,
	char* last_visit_date,
	int cholesterol_level,
	int blood_pressure,
	float average_sleep_hours,
	float physical_activity_level,
	int* medical_tests_results)
{
    health_record* newNode = init(name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);


    health_record* temp = *health;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void printNode(health_record* health)
{
	int flag = 0;

	while (health != NULL)
	{
		flag += 1;
		if (flag == 1)
		{
			puts("|--------------------------------------------------------------------------------------------------------|");
			puts("|Name       |last visit  |activity per/hour|cholester |blood pressure|sleep per/hour|medical test results|");
			puts("|-----------+------------+-----------------+----------+--------------+--------------+--------------------|");
		}
		if (flag)
		{
			printf("|%-10s | %-10s | %-15.3f | %-8d | %-12d | %-12.3f |", health->name, health->last_visit_date, health->physical_activity_level, health->cholesterol_level, health->blood_pressure, health->average_sleep_hours);
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

void deleteNodesWithValue(health_record** health, int value) {
	health_record* current = *health;
	health_record* prev = NULL;
	int deleted = 0;

	while (current != NULL) {
		if (current->cholesterol_level == value) {
			health_record* temp = current;
			if (prev != NULL)
				prev->next = current->next;
			else
				*health = current->next;
			current = current->next;
			free(temp);
			deleted = 1;
		}
		else {
			prev = current;
			current = current->next;
		}
	}

	if(deleted)
		printNode(*health);
	if (!deleted)
		printf("Elements with the specified value are not in the list\n");
}



int main()
{

	struct health_record* health = NULL;

	int element_to_delete;

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
	file = fopen("health.csv", "r");
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
			health = init(name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);
		else
			add(&health, name, last_visit_date, cholesterol_level, blood_pressure, average_sleep_hours, physical_activity_level, medical_tests_results);


		TMP++;
	}

	fclose(file);
	free(name);
	free(last_visit_date);
	free(medical_tests_results);

	puts("source table");

	printNode(health);

	puts("enter the item you want to remove");
	scanf("%d", &element_to_delete);

	puts("result:");

	deleteNodesWithValue(&health, element_to_delete);

	return 0;
}