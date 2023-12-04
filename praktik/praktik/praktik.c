//Реализуйте функцию substring_count, которая подсчитывает количество вхождений фрагмента в тексте

//Аргументы функции : string типа char*, substring типа char*

//Возвращаемый тип : int
#include <stdio.h>
#include <locale.h>

// Функция для ввода строки массива
void inputRow(int* row, int size) {
    for (int i = 0; i < size; ++i) {
        scanf_s("%d", &row[i]);
        if (row[i] < 0) {
            break;
        }
    }
}

// Функция для вывода строки массива
void printRow(int* row, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", row[i]);
    }
    printf("\n");
}

// Функция для определения количества четных чисел в столбце
int countEvenInColumn(int** array, int rows, int colIndex, int evenCount) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        if (array[i][colIndex] % 2 == 0) {
            count++;
        }
    }
    return (count == evenCount) ? 1 : 0;
}

// Функция для формирования результирующего массива
void generateResultArray(int** array, int rows, int cols, int evenCount) {
    printf("\nИсходный массив:\n");
    for (int i = 0; i < rows; ++i) {
        printRow(array[i], cols);
    }

    printf("\nСтолбцы с %d четными числами:\n", evenCount);
    for (int j = 0; j < cols; ++j) {
        if (countEvenInColumn(array, rows, j, evenCount)) {
            for (int i = 0; i < rows; ++i) {
                printf("%d ", array[i][j]);
            }
            printf("\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int rows;

    // Вводим количество строк
    printf("Введите количество строк: ");
    scanf_s("%d", &rows);

    // Выделяем память под двумерный массив
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    // Вводим элементы массива
    printf("Введите элементы массива. Завершите строку отрицательным числом:\n");
    int size = 0;
    for (int i = 0; i < rows; ++i) {
        array[i] = (int*)malloc(sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            return 1;
        }

        inputRow(array[i], size);
        if (i == 0) {
            // Определение размера строки для последующих строк
            while (array[i][size] >= 0) {
                size++;
                array[i] = realloc(array[i], (size + 1) * sizeof(int));
                if (array[i] == NULL) {
                    printf("Ошибка выделения памяти.\n");
                    return 1;
                }
                scanf_s("%d", &array[i][size]);
            }
        }
    }

    // Вводим количество четных чисел в столбце для формирования результирующего массива
    int evenCount;
    printf("Введите количество четных чисел в столбце: ");
    scanf_s("%d", &evenCount);

    // Формируем результирующий массив и выводим результат
    generateResultArray(array, rows, size, evenCount);

    // Освобождаем выделенную память
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);

int main()
{
    int a;
    a = 2500 - (690 * 3);
    printf("%d",a);
    return 0;
}

