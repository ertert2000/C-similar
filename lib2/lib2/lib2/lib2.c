#include <stdio.h>
#define N 9

void printmas(int M[], int n)
{
    int j;
    for (j = 0; j < n; j++)
        printf("%d\t", M[j]);
}

int main()
{
    int m, k, s;
    int i, temp = 0, j;
    int A[N];


    puts("enter array");
    for (j = 0; j < N; j++)
        scanf_s("%d", &A[j]);

    puts("how many elements do you want to rearrange");
    scanf_s("%d", &m);

    puts("enter the number of the element you want to start the permutation from");
    scanf_s("%d", &k);

    puts("enter the number of the position where you want to rearrange the group of elements");
    scanf_s("%d", &s);


    size_t n = sizeof(A) / sizeof(int);


    for (i = k; i < k + m; i++)
    {
        temp = A[s];
        A[s] = A[i];
        A[i] = temp;
        s++;
    }


    puts("");
    printmas(A, n);


    return 0;
}