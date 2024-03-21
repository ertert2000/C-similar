#include <stdio.h>
#include "Struct.h"
#include "ControlNode.h"
#include "ReadInStruct.h"

int main()
{
	int search[] = { 4, 1, 3 };

	PROCESSOR_STRUCT* processor = NULL;
	COPY_PROCESSOR_STRUCT* copyProcessor = NULL;

	processor = addInSruct(processor);

	printNode(processor);

	int qualytyCopyElements = sizeof(search) / sizeof(search[0]);

	copyProcessor = copyNodes(processor, search, qualytyCopyElements);

	puts("");

	printNode(copyProcessor);

	free(processor);
	free(copyProcessor);

	return 0;
}