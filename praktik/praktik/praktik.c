//#include <stdio.h> 
//#include <locale.h>
//int main()
//{
//    setlocale(LC_ALL, "RUS");
//    int N, n, i, c, size, mul;
//    int res[100000]; // ����� ������ �������� ������� �� 3000 ����
//    // ����� ����� ��������� � ������� � �������� �������
//
//    printf("\nEnter number ��� ���������� ����������: ");
//    scanf("%d", &N);
//
//    res[0] = 1; // �������������� ������ ������ 1 ������, �.�. 1 
//    c = 0; // ������� ���������� ����� 0 
//    size = 1; // �������������� ������� ���� ��� 1 (� ������� ��� ����)
//
//    for (n = 2; n <= N; n++)
//    {
//        for (i = 0; i < size; i++) // ���� ��� ��������� ����� n � res[]
//        {
//            mul = (res[i] * n) + c; // ������������ n �� ������ ����� + ������� �� ���������� ��������
//            res[i] = mul % 10; // ��������� ������ ����� ������������ � i-� ������ � ����� ������� i 
//            c = mul / 10; // ���������� ���������� ��������, ������� ����� ��������� � ����������� ��������
//        }
//
//        while (c > 0) // ���� ��� ���������� ����������� �������� �������� � ������
//        {
//            res[size++] = c % 10;
//            c /= 10;
//        }
//    }
//
//    printf("\nFactorial = "); // ����� ���������� 
//    for (i = size - 1; i >= 0; i--) // ������ �������� � �������� �������, ������� ��������� � �������� 
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
//    // ������ ������� �������
//    printf("������� ���������� ����� (N): ");
//    scanf("%d", &N);
//    printf("������� ���������� �������� (M): ");
//    scanf("%d", &M);
//
//    // ������� ������� � ��������� ���������� �������
//    int** matrix = (int**)malloc(N * sizeof(int*));
//    for (int i = 0; i < N; i++) {
//        matrix[i] = (int*)malloc(M * sizeof(int));
//    }
//
//    srand(time(NULL)); // ������������� ���������� ��������� �����
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < M; j++) {
//            matrix[i][j] = rand() % 21 - 10; // ��������� ��������� ����� �� -10 �� 10
//        }
//    }
//
//    // ������� �������� �������
//    printf("�������� �������:\n");
//    printMatrix(matrix, N, M);
//
//    // ��������� ������������������ B1...Bn
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
//    // ������� ������������������ B1...Bn
//    printf("������������������ B1...Bn:\n");
//    for (int i = 0; i < N; i++) {
//        printf("%d ", sequenceB[i]);
//    }
//    printf("\n");
//
//    // ����������� ���������� ������
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

