#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double min(double a, double b)
{
    if (a>=b) return b;
    else return a;
}

double summ(double a,double b)
{
    return a+b;
}

double max(double a, double b)
{
    if (a>=b) return a;
    else return b;
}

int fact(int a)
{
    int i,res=1;
    for (i=a;i>=1;i--)
        res = res*i;
    return res;
}

void printmas(int M[],int n)
{
    int j = 0;
    for (int j = 0; j < n; j++)
        printf("%d\t", M[j]);
}

double summas(double A[],int n)
{
    int i;
    double res = 0;
    for (i = 0; i < n; i++)
        res = res + A[i];
    return res;
}

int bin(int n)
{
    int B[1000];
    int j,i = 0;
    while (n>0)
    {
        B[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (j = i - 1; j >= 0; j--)
        return B[j];
}

char* mystrtok(char* str, const char* delim) {
    static char* next;

    if (str) {
        next = str;
        while (*next && strchr(delim, *next))
            *next++ = '\0';
    }

    if (!*next) {
        str = NULL;

    }
    else {
        str = next;

        while (*next && !strchr(delim, *next)) {
            ++next;
        }

        while (*next && strchr(delim, *next))
            *next++ = '\0';

    }

    return str;
}