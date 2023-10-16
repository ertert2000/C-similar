#include <stdio.h>

#define N 35

int main() {
    int n,i;
    int temp = 0, j,help;
    int arr[N];


    scanf_s("%d", &n);

    for (i = 0; i < n; i++)
        scanf_s("%d", &arr[i]);
    if (n % 2 == 1) 
    {
        for (i = 0; i < n-1; i++)
        {
            i++;
            int s = 1;
            help = arr[i];
            arr[i] = arr[s];
            arr[s] = temp;
            s = s + 2;
            i = i - 1;
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            i++;
            int s=1;
            help = arr[i];
            arr[i] = arr[s];
            arr[s] = temp;
            s = s + 2;
            i = i - 1;
        }
    }
    for (j = 0; j < n; j++)
        printf("%d", arr[j]);
    return 0;
}
