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

    node->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(node->name, name);

    node->last_visit_date = malloc((strlen(last_visit_date) + 1) * sizeof(char));
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

void addFront(health_record** processor,//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char* name,
    char* nameGenerations,
    int socket,
    int technologicalProcess,
    float frequency,
    float frequencyInTurboBoost,
    int* cache)
{
    health_record* newNode = init(name, nameGenerations, socket, technologicalProcess, frequency, frequencyInTurboBoost, cache);


    health_record* temp = *processor;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

int main()
{

	struct health_record* health = NULL;




	return 0;
}