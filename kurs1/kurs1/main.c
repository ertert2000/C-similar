#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_LEN_STRING_NUMBER 6


struct numbers
{
	char num[10];
};

struct declensions
{
	char numDeclensions[10];
};

struct words
{
	char word[11];
};

struct numbersFromTenToNineteen
{
	char numNumbersFromTenToNineteen[11];
};

struct rubel
{
	char rub[8];
};

int main()
{
	struct numbers num[] = { {""}, {"one "}, {"two "}, {"three "}, {"four "}, {"five "}, {"six "}, {"seven "}, {"eight "}, {"nine "} };
	struct words word[] = { {"thousands "}, {"hundreds "}, {"dozens "} };
	struct declensions numDeclensions[] = { {""}, {""}, {"twenty "}, {"thirty "}, {"forty "}, {"fifty "}, {"sixty "}, {"seventy "}, {"eighty "}, {"ninety "} };
	struct numbersFromTenToNineteen numNumbersFromTenToNineteen[] = { {"ten"}, {"eleven"}, {"twelve"}, {"thirteen"}, {"fourteen"}, {"fifteen"}, {"sixteen"}, {"seventeen"}, {"eighteen"}, {"nineteen"} };
	struct rubel rub[] = { {"rubel "}, {"rubels "} };
	char inputNumber[MAX_LEN_STRING_NUMBER];
	char outputStringNumber[300];
	char variableJinFor;
	char variableJinForNumbersFromTenToNineteen;
	int lenInputNumber = 0;
	int digitOfTheNumber;

	outputStringNumber[0] = '\0';

	puts("enter a number from 0 to 9999");
	fgets(inputNumber, MAX_LEN_STRING_NUMBER, stdin);

	size_t endInputNunber = strlen(inputNumber);
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
						strcat(outputStringNumber, word[i].word);
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
	return 0;
}


/*char one = "one";
	char two = "two";
	char three = "three";
	char four = "four";
	char five = "five";
	char six = "six";
	char seven = "seven";
	char eight = "eight";
	char nine = "nine";
	char zero = "";
	char wordThousands = "thousands";
	char wordhundreds = "hundreds";
	char worddozens = "dozens";
	char wordunits = "units";*/