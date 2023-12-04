//���������� ������� substring_count, ������� ������������ ���������� ��������� ��������� � ������

//��������� ������� : string ���� char*, substring ���� char*

//������������ ��� : int
#include <stdio.h>
#include <locale.h>

// ������� ��� ����� ������ �������
void inputRow(int* row, int size) {
    for (int i = 0; i < size; ++i) {
        scanf_s("%d", &row[i]);
        if (row[i] < 0) {
            break;
        }
    }
}

// ������� ��� ������ ������ �������
void printRow(int* row, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", row[i]);
    }
    printf("\n");
}

// ������� ��� ����������� ���������� ������ ����� � �������
int countEvenInColumn(int** array, int rows, int colIndex, int evenCount) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        if (array[i][colIndex] % 2 == 0) {
            count++;
        }
    }
    return (count == evenCount) ? 1 : 0;
}

// ������� ��� ������������ ��������������� �������
void generateResultArray(int** array, int rows, int cols, int evenCount) {
    printf("\n�������� ������:\n");
    for (int i = 0; i < rows; ++i) {
        printRow(array[i], cols);
    }

    printf("\n������� � %d ������� �������:\n", evenCount);
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

    // ������ ���������� �����
    printf("������� ���������� �����: ");
    scanf_s("%d", &rows);

    // �������� ������ ��� ��������� ������
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        printf("������ ��������� ������.\n");
        return 1;
    }

    // ������ �������� �������
    printf("������� �������� �������. ��������� ������ ������������� ������:\n");
    int size = 0;
    for (int i = 0; i < rows; ++i) {
        array[i] = (int*)malloc(sizeof(int));
        if (array[i] == NULL) {
            printf("������ ��������� ������.\n");
            return 1;
        }

        inputRow(array[i], size);
        if (i == 0) {
            // ����������� ������� ������ ��� ����������� �����
            while (array[i][size] >= 0) {
                size++;
                array[i] = realloc(array[i], (size + 1) * sizeof(int));
                if (array[i] == NULL) {
                    printf("������ ��������� ������.\n");
                    return 1;
                }
                scanf_s("%d", &array[i][size]);
            }
        }
    }

    // ������ ���������� ������ ����� � ������� ��� ������������ ��������������� �������
    int evenCount;
    printf("������� ���������� ������ ����� � �������: ");
    scanf_s("%d", &evenCount);

    // ��������� �������������� ������ � ������� ���������
    generateResultArray(array, rows, size, evenCount);

    // ����������� ���������� ������
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

