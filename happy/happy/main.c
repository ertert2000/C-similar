#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
//#include "func.h"

//struct MyStruct
//{
//	int w, h;
//};
//
//void c(struct MyStruct *ob);

int main()
{
	/*const int M = 5;
	int A[5] = { 1,2,3,4,5 };
	int n=0, x = sizeof(A[5]);
	int * pn = &n;

	void* p;

	int o,*t=NULL;
	o = sizeof(pn);
	printf("%d\n", o);

	o = sizeof(char);
	printf("%d\n", o);

	t = malloc(sizeof(int));
	*t = 325;
	printf("%d\n", *t);
	
	
	struct MyStruct sq = { 5, 7 };
	c(&sq);

	printf("%d\n", x);
	printf("%p\n", &x);
	printf("%p\n", &pn);
	printf("%d\n", *pn);
	

	free(t);
	t = NULL;*/

	int chang = 2;
	int* mass = NULL;
	mass = malloc(sizeof(int) * chang);

	
	*mass = 4444;
	*(mass + 1) = 222;

	for (int i = 0; i < chang; i++)
		mass[i] = 123;
	
	
	for (int j = 0; j < chang; j++)
		printf("%d\t", mass+j);

	

	free(mass);
	mass = NULL;

	/*int i;
	int n;
	i = 0;
	n = i++;
	printf("%d,%d", i, n);*/
	int n = 3, a = 12, b = 10;
	(n >= a) || (n <= b) ? puts("R") : puts("F");
	int c;

	c = getchar();
	printf("%c", c);

	return 0;
}

//void c(struct MyStruct *ob)
//{
//	int res = ob->w * ob->h;
//	printf("%d\n", res);
//}