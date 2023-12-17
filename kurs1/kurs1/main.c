#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define MAX_LEN_STRING_NUMBER 6
#define _(String) gettext(String)
#define PACKAGE "main"
#define LOCALEDIR "locale"


struct numbers
{
	char num[30];
};

struct declensions
{
	char numDeclensions[30];
};

struct words
{
	char word[30];
};

struct numbersFromTenToNineteen
{
	char numNumbersFromTenToNineteen[30];
};

struct rubel
{
	char rub[30];
};

struct hundreds
{
	char Hundred[50];
};

char * openinput(char * inputNumber[MAX_LEN_STRING_NUMBER])
{
	FILE* f;
	int lenPathToFile;
	char pathToFile[300];
	puts("enter the path to the file");

	fgets(pathToFile, 300, stdin);

	lenPathToFile = strlen(pathToFile);
	if (pathToFile[lenPathToFile - 1] = '\n')
		pathToFile[lenPathToFile - 1] = '\0';

	f = fopen(pathToFile, "r");
	if (f == NULL)
		return 1;

	fgets(inputNumber, MAX_LEN_STRING_NUMBER, f);
	
	fclose(f);
	return inputNumber;
}

void output(char* outputStringNumber[300])
{
	FILE* f;

	f = fopen("output.txt", "w");

	fputs(outputStringNumber, f);

	fclose(f);
}


int main()
{
	size_t endInputNunber;
	struct numbers num[] = { {""}, {"one "}, {"two "}, {"three "}, {"four "}, {"five "}, {"six "}, {"seven "}, {"eight "}, {"nine "} };
	struct words word[] = { {"thousands "}, {"hundreds "}, {"dozens "} };
	struct hundreds Hundred[] = { {""}, {"one hundred "}, {"two hundred "}, {"three hundred "}, {"four hundred "}, {"five hundred "}, {"six hundred "}, {"seven hundred "}, {"eight hundred "}, {"nine hundred "} };
	struct declensions numDeclensions[] = { {""}, {""}, {"twenty "}, {"thirty "}, {"forty "}, {"fifty "}, {"sixty "}, {"seventy "}, {"eighty "}, {"ninety "} };
	struct numbersFromTenToNineteen numNumbersFromTenToNineteen[] = { {"ten"}, {"eleven"}, {"twelve"}, {"thirteen"}, {"fourteen"}, {"fifteen"}, {"sixteen"}, {"seventeen"}, {"eighteen"}, {"nineteen"} };
	struct rubel rub[] = { {"rubel "}, {"rubels "}, {"rurubels"} };
	char inputNumber[MAX_LEN_STRING_NUMBER] = { '\0' };
	char outputStringNumber[300];
	char variableJinFor;
	char variableJinForNumbersFromTenToNineteen;
	int lenInputNumber = 0;
	int digitOfTheNumber;
	int workWhile = 20;
	int next;

	outputStringNumber[0] = '\0';

	while (1)
	{
		scanf_s("%d", &next);
		while ((getchar()) != '\n');

		system("cls");

		switch (next)
		{
		case 1:
			puts("enter a number from 0 to 9999");
			fgets(inputNumber, MAX_LEN_STRING_NUMBER, stdin);

			endInputNunber = strlen(inputNumber);
			if (inputNumber[endInputNunber - 1] == '\n')
				inputNumber[endInputNunber - 1] = '\0';

			for (int i = 0; i < endInputNunber; i++)
				if (inputNumber[i] != '\0')
					lenInputNumber++;

			digitOfTheNumber = lenInputNumber;

			while (digitOfTheNumber > 0)
				for (int i = 0; i < lenInputNumber; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						variableJinFor = j + '0';
						if (inputNumber[i] == variableJinFor)
						{
							if (digitOfTheNumber == 4)
							{
								if (inputNumber[0] == '1')
									strcat(outputStringNumber, word[2].word);
								else
								{
									strcat(outputStringNumber, num[j].num);
									strcat(outputStringNumber, word[i].word);
								}
							}
						
						if (digitOfTheNumber == 3)
						{
							strcat(outputStringNumber, Hundred[j].Hundred);
						}
						if (digitOfTheNumber == 2)
						{
							if (inputNumber[0] == '1' && lenInputNumber < 3)
							{
								for (int n = 0; n < 10; n++)
								{
									variableJinForNumbersFromTenToNineteen = n + '0';
									if (inputNumber[1] == variableJinForNumbersFromTenToNineteen)
										strcat(outputStringNumber, numNumbersFromTenToNineteen[n].numNumbersFromTenToNineteen);
								}
								digitOfTheNumber = 0;
							}
							else
								strcat(outputStringNumber, numDeclensions[j].numDeclensions);
						}
						if (digitOfTheNumber == 1)
							strcat(outputStringNumber, num[j].num);
						if (inputNumber[0] == '0')
							strcat(outputStringNumber, "zero");
					
						}

				
					}
					digitOfTheNumber--;
				}	
			if (inputNumber[endInputNunber] == '1' || inputNumber[endInputNunber] == '0')
				strcat(outputStringNumber, rub[0].rub);
			else
				strcat(outputStringNumber, rub[1].rub);
			puts(outputStringNumber);

			puts("press any key to continue");
			getchar();
			break;
		case 2:

			openinput(inputNumber);

			endInputNunber = strlen(inputNumber);
			if (inputNumber[endInputNunber - 1] == '\n')
				inputNumber[endInputNunber - 1] = '\0';

			for (int i = 0; i < endInputNunber; i++)
				if (inputNumber[i] != '\0')
					lenInputNumber++;

			digitOfTheNumber = lenInputNumber;

			while (digitOfTheNumber > 0)
				for (int i = 0; i < lenInputNumber; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						variableJinFor = j + '0';
						if (inputNumber[i] == variableJinFor)
						{
							if (digitOfTheNumber == 4)
							{
								strcat(outputStringNumber, num[j].num);
								strcat(outputStringNumber, word[i].word);
							}
							if (digitOfTheNumber == 3)
							{
								strcat(outputStringNumber, num[j].num);
								strcat(outputStringNumber, word[1].word);
							}
							if (digitOfTheNumber == 2)
							{
								if (inputNumber[0] == '1' && lenInputNumber < 3)
								{
									for (int n = 0; n < 10; n++)
									{
										variableJinForNumbersFromTenToNineteen = n + '0';
										if (inputNumber[1] == variableJinForNumbersFromTenToNineteen)
											strcat(outputStringNumber, numNumbersFromTenToNineteen[n].numNumbersFromTenToNineteen);
									}
									digitOfTheNumber = 0;
								}
								else
									strcat(outputStringNumber, numDeclensions[j].numDeclensions);
							}
							if (digitOfTheNumber == 1)
								strcat(outputStringNumber, num[j].num);
							if (inputNumber[0] == '0')
								strcat(outputStringNumber, "zero");
						}
					}
					digitOfTheNumber--;
				}
			if (inputNumber[endInputNunber] == '1' || inputNumber[endInputNunber] == '0')
				strcat(outputStringNumber, rub[0].rub);
			else
				strcat(outputStringNumber, rub[1].rub);

			output(outputStringNumber);

			puts("press any key to continue");
			getchar();
			break;
		case 3:
			return 0;
			break;
		}

	}
}
