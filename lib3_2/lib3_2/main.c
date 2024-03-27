#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include "ControlNode.h"
#include "ReadInStruct.h"

int main()
{
	PROCESSOR_STRUCT* processor = NULL;
	COPY_PROCESSOR_STRUCT* copyProcessor = NULL;

	processor = addInSruct(processor);

	puts("original table");

	printNode(processor);

	puts("");

	copyProcessor = copyNodes(processor);

	puts("");

	puts("copied table");

	printNode(copyProcessor);

	free(processor);
	free(copyProcessor);
	

	return 0;
}