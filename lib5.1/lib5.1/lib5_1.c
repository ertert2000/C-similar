#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//C:\Users\vanya\Documents\teest.txt


int main()
{
	int ckl=10;
	char string[1000];
	char rasdeliteli[100];
	while (ckl<11)
	{
		int next;
		//int	next1;
		int n = 0, r = 0;
		int ASCLL[256] = {0};
		size_t endstring;
		FILE* polsovat;
		FILE* ras;
		char wakefilestring[500];
		char wakefilerasd[500];
		

		scanf_s("%d", &next);
		switch (next)
		{
		case 1:
			system("cls");
			puts("Enter a text string consisting of words and an arbitrary number of delimiter characters after the words");
			fgets(string, 1000, stdin);

			puts("Enter the characters you want to act as delimiters");
			fgets(rasdeliteli, 100, stdin);

			endstring = strlen(string);
			if (string[endstring - 1] = '\n')
				string[endstring - 1] = '\0';

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
			//switch (next1)
			//{
			//case 1:
			//	puts("");
			//	//fgets(wakefilerasd, 500, stdin);
			//	polsovat = fopen(fgets(wakefilerasd, 500, stdin), "w");
			//	puts("");
			//	fgets(wakefilerasd, 500, stdin);
			//	ras = fopen(wakefilerasd, "w");
			//	while (!feof(polsovat))
			//	{
			//		fgets(string[n], 1000, polsovat);
			//		n++;
			//	}
			//	while (!feof(ras))
			//	{
			//		fgets(rasdeliteli[r], 1000, ras);
			//		r++;
			//	}
			//	endstring = strlen(string);
			//	if (string[endstring - 1] = '\n')
			//		string[endstring - 1] = '\0';

			//	for (int i = 0; i < strlen(rasdeliteli); i++)
			//		ASCLL[rasdeliteli[i]] = 0;
			//	for (int j = 0; j < strlen(string); j++)
			//		if (strchr(rasdeliteli, string[j]) != NULL)
			//			ASCLL[string[j]]++;

			//	for (int i = 0; i < 256; i++)
			//		if (ASCLL[i] != 0)
			//			printf("'%c' Found: % d once\n", i, ASCLL[i]);
			//	fclose(polsovat);
			//	fclose(ras);
			//	break;
			//case 2:
			//	break;
			//}
			break;
		case 3:
			return 0;
			break;
		}
	}
}