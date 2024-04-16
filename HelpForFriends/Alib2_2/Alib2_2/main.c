#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* last_visit_date;
    int cholesterol_level;
    int blood_pressure;
    float average_sleep_hours;
    float physical_activity_level;
    int* medical_tests_results;
} health_record;

char* mystrtok(char* str, const char* delim);

void add_in_file();

int cmp(const void* v1, const void* v2);

int main()
{
	int size = 3;
	int TMP;
	int flag = 0;
	int what_we_do_in_start = 0;
	int what_we_do_in_end = 0;
	char buffer[1000];
	char Serch[100];
	char* token;
	char* name;
	FILE* file;

	health_record* health;
	health = (health_record*)malloc(3 * sizeof(health_record));
	if (health)
	{
		TMP = 0;
		for (int i = 0; i < 3; i++)
			health[i].name = (char*)malloc(50 * sizeof(char));
		for (int i = 0; i < 3; i++)
			health[i].medical_tests_results = (int*)malloc(3 * sizeof(int));
		for (int i = 0; i < 3; i++)
			health[i].last_visit_date = (char*)malloc(100 * sizeof(char));


		puts("1 - read file");
		puts("2 - add person");

		scanf("%d", &what_we_do_in_start);
		switch (what_we_do_in_start)
		{
		case 1:
			file = fopen("health.csv", "r");
			if (file == NULL)
				exit(1);

			while (fgets(buffer, 1000, file) != NULL)
			{

				if (TMP == size)
				{
					size *= 2;
					health_record* temp;

					temp = (health_record*)realloc(health, size * sizeof(health_record));
					if (temp)
					{
						health = temp;
						for (int i = TMP; i < size; i++)
						{
							health[i].name = malloc(50 * sizeof(char));
							health[i].medical_tests_results = malloc(3 * sizeof(int));
							health[i].last_visit_date = malloc(100 * sizeof(char));
						}
					}
				}

				token = mystrtok(buffer, ";");
				strcpy(health[TMP].name, token);

				token = mystrtok(NULL, ";");
				strcpy(health[TMP].last_visit_date, token);

				token = mystrtok(NULL, ";");
				health[TMP].cholesterol_level = atoi(token);

				token = mystrtok(NULL, ";");
				health[TMP].blood_pressure = atoi(token);

				token = mystrtok(NULL, ";");
				health[TMP].average_sleep_hours = atof(token);

				token = mystrtok(NULL, ";");
				health[TMP].physical_activity_level = atof(token);

				for (int i = 0; i < 3; i++)
				{
					token = mystrtok(NULL, ",");
					health[TMP].medical_tests_results[i] = atoi(token);
				}

				TMP++;
			}

			fclose(file);

			qsort(health, TMP, sizeof(health_record), cmp);
			break;
		case 2:
			add_in_file();

			file = fopen("health.csv", "r");
			if (file == NULL)
				exit(1);

			while (fgets(buffer, 1000, file) != NULL)
			{

				if (TMP == size)
				{
					size *= 2;
					health_record* temp;

					temp = (health_record*)realloc(health, size * sizeof(health_record));
					if (temp)
					{
						health = temp;
						for (int i = TMP; i < size; i++)
						{
							health[i].name = malloc(50 * sizeof(char));
							health[i].medical_tests_results = malloc(3 * sizeof(int));
							health[i].last_visit_date = malloc(100 * sizeof(char));
						}
					}
				}

				token = mystrtok(buffer, ";");
				strcpy(health[TMP].name, token);

				token = mystrtok(NULL, ";");
				strcpy(health[TMP].last_visit_date, token);

				token = mystrtok(NULL, ";");
				health[TMP].cholesterol_level = atoi(token);

				token = mystrtok(NULL, ";");
				health[TMP].blood_pressure = atoi(token);

				token = mystrtok(NULL, ";");
				health[TMP].average_sleep_hours = atof(token);

				token = mystrtok(NULL, ";");
				health[TMP].physical_activity_level = atof(token);

				for (int i = 0; i < 3; i++)
				{
					token = mystrtok(NULL, ",");
					health[TMP].medical_tests_results[i] = atoi(token);
				}

				TMP++;
			}

			fclose(file);

			qsort(health, TMP, sizeof(health_record), cmp);
			break;
		}
	}
	system("cls");


	puts("|------------------------------------------Source table------------------------------------------------|");
	puts("|Name       |last visit  |cholester |blood pressure|sleep per/hour|sleep per/hour |medical test results|");
	puts("|-----------+------------+----------+--------------+--------------+---------------+--------------------|");
	for (int i = 0; i < TMP; i++)
	{
		printf("|%-10s | %-10s | %-8d | %-12d | %-12.3f | %-13.3f |", health[i].name, health[i].last_visit_date, health[i].cholesterol_level, health[i].blood_pressure, health[i].average_sleep_hours, health[i].physical_activity_level);
		for (int j = 0; j < 3; j++) 
		{
			if (j == 2)
				printf("%-14d|", health[i].medical_tests_results[j]);
			else
				printf("%d, ", health[i].medical_tests_results[j]);

		}
		puts("");
	}
	puts("");

	puts("1 - search by name");
	puts("2 - search by date");

	scanf("%d", &what_we_do_in_end);
	switch (what_we_do_in_end)
	{
	case 1:
		puts("Enter name");
		scanf("%s", Serch);
		for (int i = 0; Serch[i]; i++)
			Serch[i] = tolower(Serch[i]);


		for (int i = 0; i < TMP; i++)
		{
			name = health[i].name;
			for (int j = 0; name[j]; j++)
				name[j] = tolower(name[j]);

			if (strstr(name, Serch) != NULL)
			{
				flag += 1;
				if (flag == 1)
				{
					puts("|------------------------------------------------------------------------------------------------------|");
					puts("|Name       |last visit  |cholester |blood pressure|sleep per/hour|sleep per/hour |medical test results|");
					puts("|-----------+------------+----------+--------------+--------------+---------------+--------------------|");
				}
				if (flag)
				{
					printf("|%-10s | %-10s | %-8d | %-12d | %-12.3f | %-13.3f |", health[i].name, health[i].last_visit_date, health[i].cholesterol_level, health[i].blood_pressure, health[i].average_sleep_hours, health[i].physical_activity_level);
					for (int j = 0; j < 3; j++)
					{
						if (j == 2)
							printf("%-14d|", health[i].medical_tests_results[j]);
						else
							printf("%d, ", health[i].medical_tests_results[j]);

					}
					puts("");
				}
			}

		}
		if (flag == 0)
			puts("Nothing found");
		break;
	case 2:
		puts("enter date");
		scanf("%s", Serch);
		for (int i = 0; Serch[i]; i++)
			Serch[i] = tolower(Serch[i]);



		for (int i = 0; i < TMP; i++)
		{
			name = health[i].last_visit_date;
			for (int j = 0; name[j]; j++)
				name[j] = tolower(name[j]);

			if (strstr(name, Serch) != NULL)
			{
				flag += 1;
				if (flag == 1)
				{
					puts("|------------------------------------------------------------------------------------------------------|");
					puts("|Name       |last visit  |cholester |blood pressure|sleep per/hour|sleep per/hour |medical test results|");
					puts("|-----------+------------+----------+--------------+--------------+---------------+--------------------|");
				}
				if (flag)
				{
					printf("|%-10s | %-10s | %-8d | %-12d | %-12.3f | %-13.3f |", health[i].name, health[i].last_visit_date, health[i].cholesterol_level, health[i].blood_pressure, health[i].average_sleep_hours, health[i].physical_activity_level);
					for (int j = 0; j < 3; j++)
					{
						if (j == 2)
							printf("%-14d|", health[i].medical_tests_results[j]);
						else
							printf("%d, ", health[i].medical_tests_results[j]);

					}
					puts("");
				}
			}

		}
		if (flag == 0)
			puts("Nothing found");
		break;
	}

	free(health);
    return 0;
}

void add_in_file()
{
	char yesNo;
	int flag = 1;

	FILE* file;
	file = fopen("health.csv", "a");
	if (file == NULL)
		exit(1);

	while (flag)
	{
		char name[50];
		char last_visit_date[50];
		int cholesterol_level;
		int blood_pressure;
		float average_sleep_hours;
		float physical_activity_level;
		int medical_tests_results[3];

		puts("Enter person name:");
		scanf("%s", name);
		fprintf(file, "%s;", name);

		puts("Enter date of last visit:");
		scanf("%s", last_visit_date);
		fprintf(file, "%s;", last_visit_date);

		puts("Enter cholesterol level:");
		scanf("%d", &cholesterol_level);
		fprintf(file, "%d;", cholesterol_level);

		puts("Enter blood pressure:");
		scanf("%d", &blood_pressure);
		fprintf(file, "%d;", blood_pressure);

		puts("Enter average sleep time in hours:");
		scanf("%f", &average_sleep_hours);
		fprintf(file, "%f;", average_sleep_hours);

		puts("Enter physical activity time in hours:");
		scanf("%f", &physical_activity_level);
		fprintf(file, "%f;", physical_activity_level);

		puts("Enter medical test results where 1 is positive, 0 is negative (3 values):");
		for (int i = 0; i < 3; i++)
		{
			scanf("%f", &medical_tests_results[i]);
			fprintf(file, "%f", medical_tests_results[i]);
			if (i != 2)
				fprintf(file, ",");
		}
		fprintf(file, "\n");

		puts("Do you want to add another pocient? (Y/N)");
		scanf(" %c", &yesNo);
		if (yesNo == 'N' || yesNo == 'n')
			flag = 0;
		system("cls");
	}

	fclose(file);
}

int cmp(const void* v1, const void* v2)
{
	int cmp = 0;
	const health_record* case_1 = v1;
	const health_record* case_2 = v2;
	if (case_1->cholesterol_level < case_2->cholesterol_level)
		cmp = -1;
	else if (case_1->cholesterol_level > case_2->cholesterol_level)
		cmp = 1;
	else
		cmp = 0;
	return cmp;
}

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