#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct band {
    int id;
    char* name_group;
    char* member_of_group;
    int age;
    int number_of_solo_songs;
    float member_height;
    float maximum_monthly_income;
    struct band* prev;
    struct band* next;
} list;

typedef struct GROUPS {
    list* name_group;
    char* member_of_group;
    int age;
    int number_of_solo_songs;
    float member_height;
    float maximum_monthly_income;

} GROUPS;

void insertAtBeginning(list** head_ref, int new_data, char* new_name_group, char* new_member_of_group, int new_age, int new_number_of_solo_songs, float new_member_height, float new_maximum_monthly_income) {
    list* new_node = (list*)malloc(sizeof(list));
    new_node->id = new_data;
    new_node->name_group = new_name_group;
    new_node->member_of_group = new_member_of_group;
    new_node->age = new_age;
    new_node->number_of_solo_songs = new_number_of_solo_songs;
    new_node->member_height = new_member_height;
    new_node->maximum_monthly_income = new_maximum_monthly_income;
    new_node->next = (*head_ref);
    new_node->prev = NULL;
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
    (*head_ref) = new_node;
}
void deleteNode(list** head_ref, int key) {
    list* temp = *head_ref, * prev;
    char* group_to_delete = NULL;
    int found = 0;
    while (temp != NULL && !found) {
        if (temp->id == key) {
            group_to_delete = temp->name_group;
            found = 1;
        }
        else {
            temp = temp->next;
        }
    }

    if (!found) {
        printf("Group not found\n");
        return;
    }
    temp = *head_ref;
    while (temp != NULL) {
        if (strcmp(temp->name_group, group_to_delete) == 0) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                *head_ref = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            list* next_node = temp->next;
            free(temp);
            temp = next_node;
        }
        else {
            temp = temp->next;
        }
    }
}
void readFromFile(list** head_ref, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    char line[1024];
    int id;
    char name_group[1024];
    char member_of_group[1024];
    int age;
    int number_of_solo_songs;
    float member_height;
    float maximum_monthly_income;

    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = line;
        char* next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            id = atoi(token);
            token = next_token + 1;
        }
        next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            strncpy(name_group, token, sizeof(name_group) - 1);
            name_group[sizeof(name_group) - 1] = '\0';
            token = next_token + 1;
        }
        next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            strncpy(member_of_group, token, sizeof(member_of_group) - 1);
            member_of_group[sizeof(member_of_group) - 1] = '\0';
            token = next_token + 1;
        }
        next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            age = atoi(token);
            token = next_token + 1;
        }
        next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            number_of_solo_songs = atoi(token);
            token = next_token + 1;
        }
        next_token = strchr(token, ',');
        if (next_token != NULL) {
            *next_token = '\0';
            member_height = atof(token);
            token = next_token + 1;
        }
        if (token != NULL) {
            maximum_monthly_income = atof(token);
        }

        insertAtBeginning(head_ref, id, strdup(name_group), strdup(member_of_group), age, number_of_solo_songs, member_height, maximum_monthly_income);
    }
    fclose(file);
}
void printList(list* node) {
    printf("|%5s|%12s|%20s|%3s|%10s|%14s|%15s|\n", "ID", "Name group", "Member", "Age", "Solo songs", "Member height", "Monthly income");
    printf("+-----+------------+--------------------+---+----------+--------------+---------------+\n");
    while (node != NULL) {
        printf("|%5d|%12s|%20s|%3d|%10d|%14.2f|%15.2f|\n", node->id, node->name_group, node->member_of_group, node->age, node->number_of_solo_songs, node->member_height, node->maximum_monthly_income);
        node = node->next;
    }
}
int main() {
    list* head = NULL;

    readFromFile(&head, "lab2.csv");
    printf("Initial list:\n");
    printList(head);

    int key;
    printf("\nEnter the ID of the element to delete: ");
    scanf("%d", &key);
    deleteNode(&head, key);

    printf("\nList after deletion:\n");
    printList(head);

    return 0;
}

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define N 128
//#define classes 5
//
//typedef struct list {
//    int id;
//    char* airline;
//    struct list* next;
//    struct list* prev;
//} list;
//
//typedef struct plane {
//    int id;
//    char* model;
//    list* airline;
//    int passengers;
//    int weight;
//    float length;
//    float width;
//    int classSeats[classes];
//    struct plane* next;
//    struct plane* prev;
//} plane;
//
//typedef struct head_list {
//    struct list* first;
//    struct list* last;
//} head_list;
//
//typedef struct head {
//    struct plane* first;
//    struct plane* last;
//} head;
//
//head* make_head() {
//    head* ph = (head*)malloc(sizeof(head));
//    ph->first = NULL;
//    ph->last = NULL;
//    return ph;
//}
//
//head_list* make_head2() {
//    head_list* ph = (head_list*)malloc(sizeof(head_list));
//    ph->first = NULL;
//    ph->last = NULL;
//    return ph;
//}
//
//void add_plane(head* ph, plane* newPlane) {
//    if (ph->first == NULL) {
//        ph->first = newPlane;
//        ph->last = newPlane;
//        newPlane->next = NULL;
//        newPlane->prev = NULL;
//    }
//    else {
//        ph->last->next = newPlane;
//        ph->last = newPlane;
//        newPlane->next = NULL;
//        newPlane->prev = ph->last;
//    }
//}
//
//list* add_airline(head_list* ph_airline, char* s2) {
//    list* newAirline = (list*)malloc(sizeof(list));
//
//    newAirline->airline = (char*)malloc((strlen(s2) + 1) * sizeof(char));
//    strcpy(newAirline->airline, s2);
//    newAirline->next = NULL;
//
//    if (ph_airline->first == NULL) {
//        ph_airline->first = newAirline;
//        ph_airline->last = newAirline;
//        newAirline->prev = NULL;
//    }
//    else {
//        ph_airline->last->next = newAirline;
//        newAirline->prev = ph_airline->last;
//        ph_airline->last = newAirline;
//    }
//    return newAirline;
//}
//
//void setdata(plane* planes, char* s1, char* s2, int p1, int p2, float p3, float p4, int m1, int m2, int m3, int m4, int m5, int* k, head_list* airlines) {
//
//    planes->id = (*k);
//    (*k)++;
//
//    planes->model = (char*)malloc((strlen(s1) + 1) * sizeof(char));
//    strcpy(planes->model, s1);
//
//    list* existing_airline = NULL;
//    list* current = airlines->first;
//    while (current != NULL && existing_airline == NULL) {
//        if (strcmp(current->airline, s2) == 0) {
//            existing_airline = current;
//        }
//        current = current->next;
//    }
//
//    if (existing_airline == NULL) {
//        existing_airline = add_airline(airlines, s2);
//    }
//
//    planes->airline = existing_airline;
//
//    planes->passengers = p1;
//    planes->weight = p2;
//    planes->length = p3;
//    planes->width = p4;
//
//    planes->classSeats[0] = m1;
//    planes->classSeats[1] = m2;
//    planes->classSeats[2] = m3;
//    planes->classSeats[3] = m4;
//    planes->classSeats[4] = m5;
//}
//
//void data_file(head* ph, int* k, head_list* airlines) {
//    FILE* f;
//    char pathfile[N];
//    char s1[N], s2[N];
//    int p1, p2, m1, m2, m3, m4, m5;
//    float p3, p4;
//
//    printf("Enter the path to the file: ");
//    fgets(pathfile, N, stdin);
//    pathfile[strcspn(pathfile, "\n")] = '\0';
//    f = fopen(pathfile, "r");
//    while (f == NULL) {
//        printf("Invalid file name \nEnter the path to the file again: ");
//        fgets(pathfile, N, stdin);
//        pathfile[strcspn(pathfile, "\n")] = '\0';
//        f = fopen(pathfile, "r");
//    }
//
//    while (fscanf(f, "%[^,],%[^,],%d,%d,%f,%f,%d,%d,%d,%d,%d\n", s1, s2, &p1, &p2, &p3, &p4, &m1, &m2, &m3, &m4, &m5) == 11) {
//
//        plane* newPlane = (plane*)malloc(sizeof(plane));
//
//        setdata(newPlane, s1, s2, p1, p2, p3, p4, m1, m2, m3, m4, m5, k, airlines);
//
//        add_plane(ph, newPlane);
//    }
//
//    fclose(f);
//}
//
//void data_console(head* ph, int n, int* k, head_list* airlines) {
//    char s1[N], s2[N];
//    int p1, p2, m1, m2, m3, m4, m5;
//    float p3, p4;
//
//    printf("Input the following information about the plane, separated by commas:\n");
//    printf("Model, Airline, Number of Passengers, Weight, Length, Width, Number of seats in each class (5 classes)\n\n");
//
//    for (int i = 0; i < n; i++) {
//
//        plane* newPlane = (plane*)malloc(sizeof(plane));
//        printf("%d plane: ", i + 1);
//        scanf("%[^,], %[^,], %d, %d, %f, %f, %d, %d, %d, %d, %d", s1, s2, &p1, &p2, &p3, &p4, &m1, &m2, &m3, &m4, &m5);
//
//        memmove(s1, s1 + 1, strlen(s1));
//
//        setdata(newPlane, s1, s2, p1, p2, p3, p4, m1, m2, m3, m4, m5, k, airlines);
//
//        add_plane(ph, newPlane);
//    }
//    printf("\n");
//}
//
//void output_console(head* ph) {
//    printf("| %-2s | %-14s | %-17s | %-10s | %-9s | %-9s | %-9s | %-24s |\n", "id", "Model", "Airline", "Passengers", "Weight, t", "Length, m", "Width, m", "Class Seats (F,J,P,C,Y)");
//    printf("+----+----------------+-------------------+------------+-----------+-----------+-----------+--------------------------+\n");
//
//    plane* c_plane = ph->first;
//    while (c_plane != NULL) {
//        printf("| %-2d | %-14s | %-17s | %-10d | %-9d | %-9.2f | %-9.2f | %-4d %-4d %-4d %-4d %-4d |\n",
//            c_plane->id,
//            c_plane->model, c_plane->airline->airline, c_plane->passengers,
//            c_plane->weight, c_plane->length, c_plane->width,
//            c_plane->classSeats[0], c_plane->classSeats[1],
//            c_plane->classSeats[2], c_plane->classSeats[3],
//            c_plane->classSeats[4]);
//
//        c_plane = c_plane->next;
//    }
//}
//
//void delete_plane(head* ph, list* airline) {
//    plane* current = ph->first;
//    plane* previous = NULL;
//
//    while (current != NULL) {
//        if (current->airline == airline) {
//            if (previous == NULL) {
//                ph->first = current->next;
//                if (current->next != NULL) {
//                    current->next->prev = NULL;
//                }
//                else {
//                    ph->last = NULL;
//                }
//            }
//            else {
//                previous->next = current->next;
//                if (current->next != NULL) {
//                    current->next->prev = previous;
//                }
//                else {
//                    ph->last = previous;
//                }
//            }
//
//            free(current->model);
//            free(current);
//
//            if (previous != NULL) {
//                current = previous->next;
//            }
//            else {
//                current = ph->first;
//            }
//        }
//        else {
//            previous = current;
//            current = current->next;
//        }
//    }
//}
//
//void free_memory(head* ph, head_list* ph_airline) {
//    plane* current = ph->first;
//    plane* next = NULL;
//    while (current != NULL) {
//        next = current->next;
//        free(current->model);
//        free(current);
//        current = next;
//    }
//    free(ph);
//
//    list* current = ph_airline->first;
//    list* next = NULL;
//    while (current != NULL) {
//        next = current->next;
//        free(current->airline);
//        free(current);
//        current = next;
//    }
//    free(ph_airline);
//}
//
//int main() {
//    head* ph;
//    head_list* ph_airline;
//    list* penultimate_airline;
//    int add, incr = 1;
//
//    ph = make_head();
//    ph_airline = make_head2();
//
//    data_file(ph, &incr, ph_airline);
//    printf("Do you want add elements? Input number of elements to add (0 if no): ");
//    scanf("%d", &add);
//    printf("\n");
//    if (add != 0) {
//        data_console(ph, add, &incr, ph_airline);
//    }
//
//    output_console(ph);
//
//    if (incr > 2) {
//        penultimate_airline = ph->last->prev->airline;
//        delete_plane(ph, penultimate_airline);
//        if (ph->first == NULL) {
//            printf("\nAll elements deleted\n");
//        }
//        else {
//            printf("\n\t\t\t\t\t\tAfter deleting elements\n");
//            output_console(ph);
//        }
//    }
//    else {
//        printf("\nNot enough elements for delete penultimate element\n");
//    }
//
//    free_memory(ph, ph_airline);
//
//    return 0;
//}