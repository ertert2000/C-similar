#include <stdio.h>
//#include "func.h"
//#include <locale.h>
//#include "libxl.h"
#define M 1000

//int main()
//{
//	//setlocale(LC_ALL, "Rus");
//	char vector[255];
//	
//	FILE* file = fopen("test.txt", "r");
//
//	fgets(vector,255,file);
//	printf("%s", file);
//	
//	fclose(file);
//	return 0;
//}
struct car
{
	int weht;
	char * model;
};

int main()
{
	/*int ar[3] = {5,2,4};
	int arr[3] = { 4,9,6 };
	char chy[4] = { 'x' ,'a' ,'h','w' };*/
	int mass = 10001;
	
	/*FILE* file = fopen("test.xls", "w");

	fprintf(file, "переменная\tчисло 1\tчисло 2\tсумма чисел\n");

	for (int i = 0; i < 3; i++)
		fprintf(file, "%c\t%d\t%d\t%d\n", chy[i], ar[i], arr[i], ar[i] + arr[i]);

	fclose(file);
	*/
	puts("0");
	while (mass > M)
		scanf_s("%d", &mass);

	struct car aut[M];
	puts("1");
	for (int i = 0; i < mass; i++)
	{
		scanf_s("%d\n", &aut[i].weht);
		scanf("%c\n", &aut[i].model);
	}

	FILE* fi = fopen("car.xls", "w");

	fprintf(fi, "модель\tвес\n");

	for (int j = 0; j < mass; j++)
		fprintf(fi, "%s\t%d\n", aut[j].model, aut[j].weht);

	fclose(fi);
	return 0;
}
