#include <stdio.h>
#include "func.h"
#define N 9

int main()
{
    int m,k,s;
    int A[N];
    int i,temp=0,j;


    puts("enter arrey");
    for (j=0;j<9;j++)
        scanf_s("%d",&A[j]);
    puts("kolicheestvo elementov kotoroe hotite perestavit");
    scanf_s("%d",&m);
    puts("enter nomer elementa s rjnjhuj hotite nachat perestanovku");
    scanf_s("%d",&k);
    puts("element kuda hotite perestavit");
    scanf_s("%d",&s);

    size_t n = sizeof(A) / sizeof(int);

    for (i=k;i<k+m;i++)
    {
        temp=A[s];
        A[s]=A[i];
        A[i]=temp;
        s++;
    }

    puts("");
    printmas(A,n);

    return 0;
}

/*#include <stdio.h>


int main()
{
    int m=3,k=5,s=1;
    int A[9]={1,2,3,4,5,6,7,8,9};
    int i,kech=0,j;

    for (i=k;i<k+m;i++)
    {
        kech=A[s];
        A[s]=A[i];
        A[i]=kech;
        s++;
    }

    for (j=0;j<9;j++)
        printf("%d\n",A[j]);


    return 0;
}*/
