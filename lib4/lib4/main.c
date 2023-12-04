#include <stdio.h>
#define Mrows 10
#define Mcols 10


void inputArray(int, int, int arr[Mrows][Mcols]);

int isColumnOdd(int, int, int arr[Mrows][Mcols], int);

void deleteOddColumns(int, int*, int arr[Mrows][Mcols]);

void printArray(int, int, int arr[Mrows][Mcols]);

int main() {
	int rows=11, cols=11;

	printf("Enter the number of rows and columns not exceeding 10:");
	while (Mrows < rows)
		scanf_s("%d", &rows);
	while (Mcols < cols)
		scanf_s("%d", &cols);

	int arr[Mrows][Mcols];

	inputArray(rows, cols, arr);
	deleteOddColumns(rows, &cols, arr);
	printArray(rows, cols, arr);
	
	return 0;
}

void inputArray(int r, int c, int arr[Mrows][Mcols]) {
	printf("Enter array elements:\n");

	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			scanf_s("%d", &arr[i][j]);
	for (int i = 0; i < r; i++)
	{
		int max = 0;
		for (int j = 0; j < c; j++)
		{
			if (arr[i][j] < 0)
			{
				for (int p = 0; p < c; p++)
					if (max < arr[i][p])
					{
						max = arr[i][p];
					}
				for (int k = j; k < c; k++)
					arr[i][k + 1] = max;
			}
		}
	}
}

int isColumnOdd(int rows, int col, int arr[Mrows][Mcols], int colIndex) 
{
	int key = 1;
	for (int i = 0; i < rows; ++i) 
	{
		if (arr[i][colIndex] % 2 == 0) 
		{
			key=0;
		}
	}
	return key;
}

void deleteOddColumns(int rows, int* cols, int arr[Mrows][Mcols]) 
{
	int newCols = *cols;

	for (int j = 0; j < *cols; ++j) 
	{
		if (isColumnOdd(rows, *cols, arr, j))
		{
			for (int i = 0; i < rows; ++i)
				for (int k = j; k < *cols - 1; ++k)
					arr[i][k] = arr[i][k + 1];

			--newCols;
			--j;
		}
	}

	*cols = newCols;
}

void printArray(int rows, int cols, int arr[Mrows][Mcols]) 
{
	printf("Converted array:\n");

	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < cols; ++j)
			printf("%d\t", arr[i][j]);
		printf("\n");
	}
}