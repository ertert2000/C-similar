#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int inputUpperLimit, try, temp;
	puts("");
	scanf("%d", &inputUpperLimit);
	temp = 1 + rand() % inputUpperLimit;
	if (temp == scanf("%d", &try))
		puts("OK");
	else
		puts("neOK");
	return 0;
}