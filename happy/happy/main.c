#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void delay(int number_of_seconds)
{
	int milli_seconds = 500 * number_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int loop = 1;
	while (loop == 1) {
		puts("\t\t\t\t\t\tС днем рождения");
		delay(1);
	}
	return 0;
}