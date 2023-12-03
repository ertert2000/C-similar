#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int next, next1;
	char string[1000];
	char rasdeliteli[100];
	
	switch (next)
	{
	case 1:
		switch (next1)
		{
		case 1:
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

			for (int i = 0; i < 256; i++)
				if (ASCLL[i] != 0)
					printf("'%c' Found: % d once\n", i, ASCLL[i]);
			break;
		case 2:
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

			for (int i = 0; i < 256; i++)
				if (ASCLL[i] != 0)
					printf("'%c' Found: % d once\n", i, ASCLL[i]);
			break;
		}
		break;
	case 2:
		break;
	case 3:
		return 0;
		break;
	}
}