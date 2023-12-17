#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char* langPtr = getenv("LANG"); // получить значение переменной LANG

	if (langPtr != NULL)
		printf("Переменная окружения LANG: %s", langPtr);
	
	return 0;
}