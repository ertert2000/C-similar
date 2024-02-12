//#include <stdio.h> 
//#include <locale.h>
//int main()
//{
//    setlocale(LC_ALL, "RUS");
//    int N, n, i, c, size, mul;
//    int res[100000]; // Пусть массив способен хранить до 3000 цифр
//    // Числа будут храниться в массиве в обратном порядке
//
//    printf("\nEnter number для вычисления факториала: ");
//    scanf("%d", &N);
//
//    res[0] = 1; // Инициализируем массив только 1 цифрой, т.е. 1 
//    c = 0; // Перенос изначально равен 0 
//    size = 1; // Инициализирует счетчик цифр как 1 (в массиве нет цифр)
//
//    for (n = 2; n <= N; n++)
//    {
//        for (i = 0; i < size; i++) // Цикл для умножения чисел n и res[]
//        {
//            mul = (res[i] * n) + c; // Произведение n на каждую цифру + перенос из предыдущей операции
//            res[i] = mul % 10; // Поместите первую цифру произведения с i-й цифрой в самой позиции i 
//            c = mul / 10; // Оставшееся переносное значение, которое будет сохранено в последующих индексах
//        }
//
//        while (c > 0) // Цикл для сохранения оставшегося значения переноса в массив
//        {
//            res[size++] = c % 10;
//            c /= 10;
//        }
//    }
//
//    printf("\nFactorial = "); // Вывод результата 
//    for (i = size - 1; i >= 0; i--) // Массив хранится в обратном порядке, поэтому выводится в обратном 
//        printf("%d", res[i]);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//void printMatrix(int** matrix, int rows, int cols) {
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            printf("%3d ", matrix[i][j]);
//        }
//        printf("\n");
//    }
//}
//
//int main() {
//    int N, M;
//
//    // Вводим размеры матрицы
//    printf("Введите количество строк (N): ");
//    scanf("%d", &N);
//    printf("Введите количество столбцов (M): ");
//    scanf("%d", &M);
//
//    // Создаем матрицу и заполняем случайными числами
//    int** matrix = (int**)malloc(N * sizeof(int*));
//    for (int i = 0; i < N; i++) {
//        matrix[i] = (int*)malloc(M * sizeof(int));
//    }
//
//    srand(time(NULL)); // Инициализация генератора случайных чисел
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < M; j++) {
//            matrix[i][j] = rand() % 21 - 10; // Генерация случайных чисел от -10 до 10
//        }
//    }
//
//    // Выводим исходную матрицу
//    printf("Исходная матрица:\n");
//    printMatrix(matrix, N, M);
//
//    // Формируем последовательность B1...Bn
//    int* sequenceB = (int*)malloc(N * sizeof(int));
//    for (int i = 0; i < N; i++) {
//        sequenceB[i] = 0;
//        for (int j = 0; j < M; j++) {
//            if (matrix[i][j] < 0) {
//                sequenceB[i]++;
//            }
//        }
//    }
//
//    // Выводим последовательность B1...Bn
//    printf("Последовательность B1...Bn:\n");
//    for (int i = 0; i < N; i++) {
//        printf("%d ", sequenceB[i]);
//    }
//    printf("\n");
//
//    // Освобождаем выделенную память
//    for (int i = 0; i < N; i++) {
//        free(matrix[i]);
//    }
//    free(matrix);
//    free(sequenceB);
//
//    return 0;
//}

#define MAX_LEN 100
#define MAX_STUDENT 100

struct STUDENT
{
	char FIO[MAX_LEN];
	int numGrup;
	float mark[5];
}student[MAX_STUDENT];


int main()
{
	for (int i = 0; i < MAX_STUDENT; i++)
	{
		ptus("");
		fgets(student[i].FIO, MAX_LEN, stdin);
		ptus("");
		scanf_s("%d", &student[i].numGrup);
		ptus("");
		for(int j = 0; j < 5; j++)
			scanf_s("%f", &student[i].mark[j]);
	}

	for (int i = 0; i < MAX_STUDENT; i++)
	{
		float res=0;
		for (int j = 0; j < 5; j++)
		{
			res += student[i].mark[j];
			res = res / 5;
		}
		printf("%s %d %f", student[i].FIO, student[i].numGrup, res);
	}


	return 0;
}

