#define _CRT_SECURE_NO_WARNINGS
#define ENABLE_NLS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
//#include <windows.h>
#define MAX_LEN_STRING_NUMBER 6
#define _(String) gettext(String)
//#define PACKAGE "kursovaya"
//#define LOCALEDIR "locale"


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


int main()
{
	/*setlocale(LC_ALL, "");
	bindtextdomain("kursovaya", "locale");
	textdomain("kursovaya");*/
	//bind_textdomain_codeset("kursovaya", "UTF-8");
	size_t endInputNunber;
	struct numbers num[] = { {""}, {_("one ")}, {_("two ")}, {_("three ")}, {_("four ")}, {_("five ")}, {_("six ")}, {_("seven ")}, {_("eight ")}, {_("nine ")} };
	struct words word[] = { {_("thousands ")}, {_("hundred ")}, {_("tisacha ")} };
	struct hundreds Hundred[] = { {""}, {_("one hundred ")}, {_("two hundred ")}, {_("three hundred ")}, {_("four hundred ")}, {_("five hundred ")}, {_("six hundred ")}, {_("seven hundred ")}, {_("eight hundred ")}, {_("nine hundred ")} };
	struct declensions numDeclensions[] = { {""}, {""}, {_("twenty ")}, {_("thirty ")}, {_("forty ")}, {_("fifty ")}, {_("sixty ")}, {_("seventy ")}, {_("eighty ")}, {_("ninety ")} };
	struct numbersFromTenToNineteen numNumbersFromTenToNineteen[] = { {_("ten")}, {_("eleven")}, {_("twelve")}, {_("thirteen")}, {_("fourteen")}, {_("fifteen")}, {_("sixteen")}, {_("seventeen")}, {_("eighteen")}, {_("nineteen")} };
	struct rubel rub[] = { {_("rubel ")}, {_("rubels ")}, {_("rurubels")} };
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
			puts(_("enter a number from 0 to 9999"));
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
									strcat(outputStringNumber, word[3].word);
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
								strcat(outputStringNumber, _("zero"));
						}
					}
					digitOfTheNumber--;
				}
			if (inputNumber[endInputNunber] == '1' || inputNumber[endInputNunber] == '0')
				strcat(outputStringNumber, rub[0].rub);
			else
				strcat(outputStringNumber, rub[1].rub);
			
			puts(outputStringNumber);

			printf("%s", num[1].num);

			puts(_("press any key to continue"));
			getchar();
			break;
		case 2:
			//fgets(inputNumber, MAX_LEN_STRING_NUMBER, mass); /*��� ��� �� ��������*/

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
								strcat(outputStringNumber, _("zero"));
						}
					}
					digitOfTheNumber--;
				}
			if (inputNumber[endInputNunber] == '1' || inputNumber[endInputNunber] == '0')
				strcat(outputStringNumber, rub[0].rub);
			else
				strcat(outputStringNumber, rub[1].rub);
			puts(outputStringNumber);

			puts(_("press any key to continue"));
			getchar();
			break;
		case 3:
			return 0;
			break;
		}
	}
}