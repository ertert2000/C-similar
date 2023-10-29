#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

struct MyStruct
{
	int w, h;
};

void c(struct MyStruct *ob);

int main()
{
	const int M = 5;
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
	t = NULL;
	return 0;
}

void c(struct MyStruct *ob)
{
	int res = ob->w * ob->h;
	printf("%d\n", res);
}