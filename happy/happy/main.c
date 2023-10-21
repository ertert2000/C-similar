#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "func.h"



int main()
{
	setlocale(LC_ALL, "Rus");
	int loop = 1;
	char key = "imput";
	
	
	
	
	switch (key)
	{
	case '1':
		while (loop == 1) {
			puts("\t\t\t\t\t\tС днем рождения");
			delay(1);
		}
		break;
	}
	
	
	/*int loop = 1;
	while (loop == 1) {
		puts("\t\t\t\t\t\tС днем рождения");
		delay(1);
	}*/
	
	
	
	
	
	return 0;
}