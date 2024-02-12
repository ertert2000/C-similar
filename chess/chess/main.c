#include <stdio.h>

int main()
{
	char field[9][9];
	

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
				field[i][j] = 48;

	for (int i = 0; i < 8; i++)
		field[i][8] = 65+i; 
	for (int i = 0; i < 8; i++)
		field[8][i] = 49+i;
	
	field[8][8] = 127;

	for (int i = 0; i < 8; i++)
	{
		field[1][i] = 49;
		field[6][i] = 49;
	}

	for (int i = 0; i < 4; i++)
		field[0][i] = 50+i;
	for (int i = 7; i > 3; i--)
		field[0][i] = 57 - i;

	for (int i = 0; i < 4; i++)
		field[7][i] = 50 + i;
	for (int i = 7; i > 3; i--)
		field[7][i] = 57 - i;

	puts(""); puts("");
	for (int i = 0; i < 9; i++)
	{
		
		printf("\t\t\t\t");
		for (int j = 0; j < 9; j++)
			printf("%c ",field[i][j]);

		puts("");
	}
	
	return 0;
}