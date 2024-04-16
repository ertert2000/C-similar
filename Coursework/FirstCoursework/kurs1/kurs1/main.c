#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define MAX_LEN_STRING_NUMBER 6
#define _(String) gettext(String)
#define PACKAGE "main"
#define LOCALEDIR "locale"

#ifdef _WIN32
#define clear() system("cls");
#else
#define clear() system("clear");
#endif // linux

struct numbers
{
	const char* num[30];
};

struct declensions
{
	const char* numDeclensions[30];
};

struct thousands
{
	const char* thousands[50];
};

struct numbersFromTenToNineteen
{
	const char* numNumbersFromTenToNineteen[30];
};

struct rubel
{
	const char* rub[30];
};

struct hundreds
{
	const char* Hundred[50];
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
	setlocale(LC_ALL, "");
	bindtextdomain("main", "locale");
	textdomain("main");
	//declaration of variables
	size_t endInputNunber;
	struct numbers num[] = { "", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine " };
	struct thousands thousands[] = { "", "one thousands ", "two thousands ", "three thousands ", "four thousands ", "five thousands ", "six thousands ", "seven thousands ", "eight thousands ", "nine thousands " };
	struct hundreds Hundred[] = { "", "one hundred ", "two hundred ", "three hundred ", "four hundred ", "five hundred ", "six hundred ", "seven hundred ", "eight hundred ", "nine hundred " };
	struct declensions numDeclensions[] = { "", "", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety " };
	struct numbersFromTenToNineteen numNumbersFromTenToNineteen[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	struct rubel rub[] = { "rubel ", "rubels ", "rurubels" };
	char inputNumber[MAX_LEN_STRING_NUMBER] = { '\0' };
	char outputStringNumber[300];
	char variableJinFor;
	char variableJinForNumbersFromTenToNineteen;
	int lenInputNumber = 0;
	int digitOfTheNumber;
	int workWhile = 20;
	int next;

	
	//create an endless loop
	while (1)
	{
		//clearing important variables after each iteration switch
		outputStringNumber[0] = '\0';
		inputNumber[0] = '\0';
		digitOfTheNumber = 0;
		lenInputNumber = 0;
		variableJinFor = '\0';
		
		//program menu
		puts("#===============================#");
		puts("1 - working in the console");
		puts("2 - working with a file");
		puts("3 - shutdown");
		puts("#===============================#");
		
		//transition to a new one switch
		scanf_s("%d", &next);
		while ((getchar()) != '\n');

		clear(); //clearing the console

		switch (next)
		{
		case 1:
			puts("enter a number from 0 to 9999");
			fgets(inputNumber, MAX_LEN_STRING_NUMBER, stdin); //request to enter a number

			//search for penultimate element
			endInputNunber = strlen(inputNumber);
			if (inputNumber[endInputNunber - 1] == '\n')
				inputNumber[endInputNunber - 1] = '\0';

			for (int i = 0; i < endInputNunber; i++)
				if (inputNumber[i] != '\0')
					lenInputNumber++;

			digitOfTheNumber = lenInputNumber;

			while (digitOfTheNumber > 0)              /*1245 - тысяча двсети сорок пять*/
				for (int i = 0; i < lenInputNumber; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						variableJinFor = j + '0';
						if (inputNumber[i] == variableJinFor)
						{
							if (digitOfTheNumber == 4) //if 4 characters
							{
								strcat(outputStringNumber, thousands->thousands[j]);
							}
						
							if (digitOfTheNumber == 3) //if 3 characters
							{
								strcat(outputStringNumber, Hundred->Hundred[j]);
							}
							if (digitOfTheNumber == 2) //if 2 characters
							{
								if (inputNumber[0] == '1' && lenInputNumber < 3)
								{
									for (int n = 0; n < 10; n++)
									{
										variableJinForNumbersFromTenToNineteen = n + '0';
										if (inputNumber[1] == variableJinForNumbersFromTenToNineteen)
											strcat(outputStringNumber, numNumbersFromTenToNineteen->numNumbersFromTenToNineteen[n]);
									}
									digitOfTheNumber = 0;
								}
								else
									strcat(outputStringNumber, numDeclensions->numDeclensions[j]);
							}
							if (digitOfTheNumber == 1) //if 1 characters
								strcat(outputStringNumber, num->num[j]);
							if (inputNumber[0] == '0') //if 0
								strcat(outputStringNumber, "zero ");
					
						}

				
					}
					digitOfTheNumber--;
				}
			//adding the word rubles
			if ((inputNumber[lenInputNumber - 1] == '1') || (inputNumber[lenInputNumber - 1] == '0'))
				strcat(outputStringNumber, rub->rub[0]);
			else if (inputNumber[lenInputNumber - 1] == '2' || inputNumber[lenInputNumber - 1] == '3' || inputNumber[lenInputNumber - 1] == '4')
				strcat(outputStringNumber, rub->rub[1]);
			else
				strcat(outputStringNumber, rub->rub[2]);

			puts(outputStringNumber); //output result

			puts("press any key to continue");
			getchar();
			clear();
			break;
		case 2:
			//function for writing elements from a file to a string
			openinput(inputNumber);

			//search for penultimate element
			endInputNunber = strlen(inputNumber);
			if (inputNumber[endInputNunber - 1] == '\n')
				inputNumber[endInputNunber - 1] = '\0';

			for (int i = 0; i < endInputNunber; i++)
				if (inputNumber[i] != '\0')
					lenInputNumber++;

			digitOfTheNumber = lenInputNumber;

			while (digitOfTheNumber > 0)              /*1245 - тысяча двсети сорок пять*/
				for (int i = 0; i < lenInputNumber; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						variableJinFor = j + '0';
						if (inputNumber[i] == variableJinFor)
						{
							if (digitOfTheNumber == 4) //if 4 characters
							{
								strcat(outputStringNumber, thousands->thousands[j]);
							}

							if (digitOfTheNumber == 3) //if 3 characters
							{
								strcat(outputStringNumber, Hundred->Hundred[j]);
							}
							if (digitOfTheNumber == 2) //if 2 characters
							{
								if (inputNumber[0] == '1' && lenInputNumber < 3)
								{
									for (int n = 0; n < 10; n++)
									{
										variableJinForNumbersFromTenToNineteen = n + '0';
										if (inputNumber[1] == variableJinForNumbersFromTenToNineteen)
											strcat(outputStringNumber, numNumbersFromTenToNineteen->numNumbersFromTenToNineteen[n]);
									}
									digitOfTheNumber = 0;
								}
								else
									strcat(outputStringNumber, numDeclensions->numDeclensions[j]);
							}
							if (digitOfTheNumber == 1) //if 1 characters
								strcat(outputStringNumber, num->num[j]);
							if (inputNumber[0] == '0') //if 0
								strcat(outputStringNumber, "zero ");

						}


					}
					digitOfTheNumber--;
				}
			//adding the word rubles
			if ((inputNumber[lenInputNumber - 1] == '1') || (inputNumber[lenInputNumber - 1] == '0'))
				strcat(outputStringNumber, rub->rub[0]);
			else if (inputNumber[lenInputNumber - 1] == '2' || inputNumber[lenInputNumber - 1] == '3' || inputNumber[lenInputNumber - 1] == '4')
				strcat(outputStringNumber, rub->rub[1]);
			else
				strcat(outputStringNumber, rub->rub[2]);
			
			//function to output the response to a file
			puts("the file with the answer is in a directory called output.txt");
			output(outputStringNumber);

			puts("press any key to continue");
			getchar();
			clear();
			break;
		case 3:
			return 0;
			break;
		}

	}
}
