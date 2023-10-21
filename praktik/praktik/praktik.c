#include <stdio.h>

int main() {
    int N;
    int count = 0;


    scanf_s("%d", &N);

    if (N < 1 || N >= 10000) {
        return 1;
    }


    for (int i = 0; i < N; i++) {
        int num;
        scanf_s("%d", &num);
        if (num > 0) {
            count++;
        }
    }


    printf("%d\n", count);

    return 0;
}
