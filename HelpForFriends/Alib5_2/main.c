#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct health_record 
{
    char* name;
    char* last_visit_date;
    int cholesterol_level;
    int blood_pressure;
    float average_sleep_hours;
    float physical_activity_level;
    int* medical_tests_results;
    struct health_record* next;
} health_record;

typedef struct node_stack 
{
    health_record* record;
    struct node_stack* next;
} node_stack;

void push(node_stack** stack, health_record* record) 
{
    node_stack* new_node = (node_stack*)malloc(sizeof(node_stack));

    new_node->record = record;
    new_node->next = *stack;

    *stack = new_node;
}

health_record* pop(node_stack** stack) 
{
    if (*stack == NULL)
        return NULL;

    node_stack* temp = *stack;

    health_record* record = temp->record;

    *stack = temp->next;

    free(temp);

    return record;
}

health_record* rearrangeList(health_record* head) 
{
    if (!head) 
        return NULL;

    health_record* current = head;
    node_stack* stack1 = NULL;
    node_stack* stack2 = NULL;

    int count = 0;
    do 
    {
        count++;
        current = current->next;
    } while (current != head);

    int middle = count / 2;
    current = head;

    for (int i = 0; i < count; i++) 
    {

        if (i < middle)
            push(&stack1, current);
        else if (i >= middle && count % 2 == 0)
            push(&stack2, current);
        else if (i > middle && count % 2 == 1)
            push(&stack2, current);
        

        current = current->next;
    }

    health_record* new_head = NULL;
    health_record* new_tail = NULL;
    health_record* TMP = NULL;

    if (count % 2 == 1)
    {
        int tmp = 0;
        while (tmp != count / 2)
        {
            head = head->next;
            tmp++;
        }
        TMP = head;
        TMP->next = NULL;
    }


    while (stack1) 
    {
        health_record* node = pop(&stack1);
        node->next = NULL;

        if (!new_tail)
            new_head = node;
        else
            new_tail->next = node;

        new_tail = node;
    }

    if (count % 2 == 1) 
    {
        new_tail->next = TMP;
        new_tail = TMP;
    }

    while (stack2) 
    {
        health_record* node = pop(&stack2);
        node->next = NULL;

        if (!new_tail)
            new_head = node;
        else 
            new_tail->next = node;

        new_tail = node;
    }

    return new_head;
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




void printList(health_record* health, int TMP)
{
    int flag = 0;
    int j = 0;
    int id = 1;

    while (health != NULL && j!=TMP)
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
            printf("|%d |%-10s | %-10s | %-15.3d | %-8d | %-12f | %-12.3f |",id, health->name, health->last_visit_date, health->cholesterol_level, health->blood_pressure, health->average_sleep_hours, health->physical_activity_level);
            for (int i = 0; i < 3; i++)
            {
                if (i == 2)
                    printf("%-14d|", health->medical_tests_results[i]);
                else
                    printf("%d, ", health->medical_tests_results[i]);
            }
            puts("");
        }
        id++;
        j++;
        health = health->next;
    }
}

void creatingACircularList(health_record** health, int TMP)
{
    health_record* teemp = *health;
    health_record* teeemp = *health;
    int b = 0;
    while (teeemp->next != NULL)
    {
        teeemp = teeemp->next;
    }
    teeemp->next = teemp;
}

int main() {
    
    struct health_record* health = NULL;

    int TMP = 0;
    char buffer[1000];
    char pathfile[100];
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

    printf("Enter the path to the file:");
    fgets(pathfile, 100, stdin);
    pathfile[strcspn(pathfile, "\n")] = '\0';

    file = fopen(pathfile, "r");
    while (file == NULL)
    {
        printf("Invalid file name \nEnter the path to the file again:\n");
        fgets(pathfile, 100, stdin);
        pathfile[strcspn(pathfile, "\n")] = '\0';
        file = fopen(pathfile, "r");
        system("cls");
    }
    system("cls");

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
    
    creatingACircularList(&health, TMP);

    fclose(file);
    free(name);
    free(last_visit_date);
    free(medical_tests_results);

    puts("source table");
    printList(health, TMP);

    health_record* linear_head = rearrangeList(health);

    puts("");
    puts("remade table");
    printList(linear_head, TMP);
    

    return 0;
}