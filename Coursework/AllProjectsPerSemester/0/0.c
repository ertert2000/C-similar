#include <stdio.h>
#include <math.h>

int bolsche (float n)
{
    int i;
    if (sqrt(n)==n)
    {
        puts("kanaet");
    }
    while((sqrt(n))%10==0)
    {
        n++;
        i++;
    }
    return i;
}


int main(){

    float n=11;

    printf("%f",bolsche(n));

    return 0;
}
