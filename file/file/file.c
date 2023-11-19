#include <stdio.h>
#include "func.h"
#include <locale.h>
#include "libxl.h"

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

//int main()
//{
//	int ar[3] = {1,2,3};
//	int arr[3] = { 4,5,6 };
//	char chy[4] = { 'x' ,'a' ,'h','w' };
//	
//	FILE* file = fopen("test.xls", "w");
//
//	for (int i = 0; i < 3; i++)
//		fprintf(file, "%c\t%d\t%d\t%d\n", chy[i], ar[i], arr[i], ar[i] + arr[i]);
//
//	/*for (int i = 0; i < 3; i++)
//	{
//		fprintf(file, "%d\n", ar[i] + arr[i]);
//	}*/
//
//	fclose(file);
//	return 0;
//}
static size_t WD(char* ptr, size_t size, size_t nmemb, FILE * data)
{
	return fwrite(ptr, size, nmemb, data);
}
int main()
{
	int ar[3] = {1,2,3};
	int arr[3] = { 4,5,6 };
	char chy[4] = { 'x' ,'a' ,'h','w' };
	
	FILE* file = fopen("test.xls", "w");

	fclose(heder);
	fclose(body);

	/*for (int i = 0; i < 3; i++)
	{
		fprintf(file, "%d\n", ar[i] + arr[i]);
	}*/

	fclose(file);
	return 0;
}
