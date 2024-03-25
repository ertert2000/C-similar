#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include "ControlNode.h"
#include "ReadInStruct.h"

int main()
{
	int* search;
	int size = 3;

	search = (int*)malloc(size * sizeof(int));
	if (!search)
		exit(1);

	for (int i = 0; i < ((sizeof(search) / sizeof(search[0])) + 1); i++)
	{
		if ((sizeof(search) / sizeof(int)) == size)
		{
			size *= 2;

			int* temp = (int*)realloc(search, size * sizeof(int));
			if (temp)
				search = temp;

			free(temp);
		}

		scanf("%d", &search[i]);

	}

	PROCESSOR_STRUCT* processor = NULL;
	COPY_PROCESSOR_STRUCT* copyProcessor = NULL;

	processor = addInSruct(processor);

	printNode(processor);

	puts("");

	int qualytyCopyElements = sizeof(search) / sizeof(search[0]);

	copyProcessor = copyNodes(processor, search, qualytyCopyElements);

	puts("");

	printNode(copyProcessor);

	free(processor);
	free(copyProcessor);
	free(search);

	return 0;
}