//10
//Разработать подалгоритм создания односвязного списка из имеющегося односвязного списка 
//путем копирования заданных элементов.Номера копируемых элементов содержатся в полученном массиве.
//Порядок копируемых элементов должен соответствовать их порядку в исходном списке.
//В случае отсутствия элемента с заданным номером вывести сообщение.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node *next;
}Node;
int main()
{
	struct Node *head = NULL;

	Node *tmp = (Node*)malloc(sizeof(Node));
	if (!tmp)
		exit(1);

	tmp->value = 0;
	tmp->next = head;
	head = tmp;

	for (int i = 0; i < 2; i++)
	{
		printf("%d", tmp->value);
	}
	return 0;
}
