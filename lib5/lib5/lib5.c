#include <stdio.h>
#include <string.h>

int main()
{
	char string[1000];
	char rasdeliteli[100];
	
	puts("Enter a text string consisting of words and an arbitrary number of delimiter characters after the words");
	fgets(string, 1000, stdin);

	puts("Enter the characters you want to act as delimiters");
	fgets(rasdeliteli, 100, stdin);

	size_t endstring = strlen(string);
	if (string[endstring - 1] = '\n')
		string[endstring - 1] = '\0';

	int ASCLL[256] = { 0 };

	for (int i = 0; i < strlen(rasdeliteli); i++)
		ASCLL[rasdeliteli[i]] = 0;
	for (int j = 0; j < strlen(string); j++)
		if (strchr(rasdeliteli, string[j]) != NULL)
			ASCLL[string[j]]++;

	for (int k = 0; k < 256; k++)
		if (ASCLL[k] != 0)
			printf("'%c' Found: % d once\n", k, ASCLL[k]);
	return 0;
}


for (int i = 0; i < strlen(string); i++)
	if (strchr(rasdeliteli, string[i]) != NULL)
		< действие >