#include <stdio.h>
#include "func.h"

#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int rows, cols;

    scanf_s("%d", &rows);

    scanf_s("%d", &cols);

    if (rows > MAX_ROWS || cols > MAX_COLS)
        return 1;

    double arr[MAX_ROWS][MAX_COLS + 1]; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d %d", i, j);
            scanf_s("%lf", &arr[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
        arr[i][cols] = sum / cols;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            printf("%10.2f ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
