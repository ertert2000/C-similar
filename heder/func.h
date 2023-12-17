#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double minn(double a, double b)
{
    if (a>=b) return b;
    else return a;
}

double summ(double a,double b)
{
    return a+b;
}

double maxx(double a, double b)
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

void delay(int number_of_seconds)
{
    int milli_seconds = 500 * number_of_seconds; /*500 - способ изменения времени*/
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

char* dynamicarrayforstrings() 
{
    size_t bufferSize = 10;

    char* str = (char*)malloc(bufferSize * sizeof(char));

    if (str == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    printf("Enter the string: ");

    char ch;
    size_t index = 0;

    while ((ch = getchar()) != '\n') {
        if (index == bufferSize - 1) {
            bufferSize *= 2;
            char* temp = (char*)realloc(str, bufferSize * sizeof(char));

            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation error\n");
                free(str);
                return NULL;
            }

            str = temp;
        }
        str[index++] = ch;
    }

    str[index] = '\0';

    return str;
    //обязательно в конце main очищать память
}

for(int i = 0;i < strlen(str);i++)
    if (str[i] == ' ')
