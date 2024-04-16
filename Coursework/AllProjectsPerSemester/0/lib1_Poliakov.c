#include <stdio.h>



int prost(int n)
{
    int i;
    if (n==1) return 0;
    for (i=2;i<n;i++)
    {
        if(n%i==0) return 0;
    }
    return 1;
}



int main()
{
    int n=1, chis=0;
    puts("enter a sequence of numbers. to exit, use the number 0. the program will determine the number of prime numbers \n");
    while(scanf("%d",&n) && n!=0)
    {
        if (prost(n)) chis++;
    }
    printf("number of prime numbers: %d",chis);
    return 0;
}
