#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//C:\Users\vanya\Documents\teest.txt
//C:\\Users\\»ван\\Documents\\teets.txt
//F:\teets.txt

int main()
{
	setlocale(LC_ALL, "RUS");
	int ckl=10;
	int ASCLL[256] = { 0 };
	int next;
	int	next1;
	int len;
	char string[1000];
	char rasdeliteli[100];
	char wakefilerasd[500];
	size_t endstring;
	FILE* polsovat;
	

	while (ckl < 11)
	{
		puts("1 - determining the number of delimiter characters with manual line input\n2 - determining the number of delimiter characters with file input\n3 - to complete the program");

		scanf_s("%d", &next);
		while ((getchar()) != '\n');

		system("cls");

		switch (next)
		{
		case 1:
			puts("1 - English\n2 - Russian");
			
			scanf_s("%d", &next1);
			while ((getchar()) != '\n');

			switch (next1)
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

				for (int j = 0; j < strlen(string); j++)
					if (strchr(rasdeliteli, string[j]) != NULL)
						ASCLL[string[j]]++;

				for (int i = 0; i < 256; i++)
					if (ASCLL[i] != 0)
						printf("'%c' Found: % d once\n", i, ASCLL[i]);

				getchar();
				system("cls");
				break;
			case 2:
				system("cls");

				puts("¬ведите текстовую строку, состо€щую из слов и произвольного количества символов-разделителей после слов");
				fgets(string, 1000, stdin);

				puts("¬ведите символы, которые вы хотите использовать в качестве разделителей.");
				fgets(rasdeliteli, 100, stdin);

				endstring = strlen(string);
				if (string[endstring - 1] = '\n')
					string[endstring - 1] = '\0';

				for (int j = 0; j < strlen(string); j++)
					if (strchr(rasdeliteli, string[j]) != NULL)
						ASCLL[string[j]]++;

				for (int i = 0; i < 256; i++)
					if (ASCLL[i] != 0)
						printf("'%c' найдено: % d раз\n", i, ASCLL[i]);

				getchar();
				system("cls");
				break;
			}
			break;
		case 2:
			puts("1 - English\n2 - Russian");

			scanf_s("%d", &next1);
			while ((getchar()) != '\n');

			switch (next1)
			{
			case 1:
				system("cls");

				puts("enter the path to the file");

				fgets(wakefilerasd, 100, stdin);

				len = strlen(wakefilerasd);
				if (wakefilerasd[len - 1] = '\n')
					wakefilerasd[len - 1] = '\0';

				polsovat = fopen(wakefilerasd, "r");
				if (polsovat == NULL)
					return 1;

				fgets(string, 1000, polsovat);

				endstring = strlen(string);
				if (string[endstring - 1] == '\n')
					string[endstring - 1] = '\0';

				puts("enter delimiter characters");
				fgets(rasdeliteli, 100, stdin);

				for (int j = 0; j < strlen(string); j++)
					if (strchr(rasdeliteli, string[j]) != NULL)
						ASCLL[string[j]]++;

				for (int i = 0; i < 256; i++)
					if (ASCLL[i] != 0)
						printf("'%c' Found: % d once\n", i, ASCLL[i]);

				fclose(polsovat);
				getchar();
				system("cls");
				break;
			case 2:
				system("cls");

				puts("введите путь к файлу");

				fgets(wakefilerasd, 100, stdin);

				len = strlen(wakefilerasd);
				if (wakefilerasd[len - 1] = '\n')
					wakefilerasd[len - 1] = '\0';

				polsovat = fopen(wakefilerasd, "r");
				if (polsovat == NULL)
					return 1;

				fgets(string, 1000, polsovat);

				endstring = strlen(string);
				if (string[endstring - 1] == '\n')
					string[endstring - 1] = '\0';

				puts("введите символы разделители");
				fgets(rasdeliteli, 100, stdin);

				for (int j = 0; j < strlen(string); j++)
					if (strchr(rasdeliteli, string[j]) != NULL)
						ASCLL[string[j]]++;

				for (int i = 0; i < 256; i++)
					if (ASCLL[i] != 0)
						printf("'%c' Found: % d once\n", i, ASCLL[i]);

				fclose(polsovat);
				getchar();
				system("cls");
				break;
			}
			break;
		case 3:
			return 0;
			break;
		}
	}
}
