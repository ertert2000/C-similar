#include <stdio.h>
#include <string.h>
#define MAX_LEN 100
#define MAX_STUDENT 100

struct STUDENT
{
	char FIO[MAX_LEN];
	int numGrup;
	float mark[5];
};


int main()
{
	struct STUDENT student[MAX_STUDENT];
	int quantity;
	puts("");
	scanf_s("%d", &quantity);
	for (int i = 0; i < quantity; i++)
	{
		puts("enter fio");
		while ((getchar()) != '\n');
		fgets(student[i].FIO, MAX_LEN, stdin);
		puts("");
		scanf_s("%d", &student[i].numGrup);
		puts("");
		for (int j = 0; j < 5; j++)
			scanf_s("%f", &student[i].mark[j]);
	}

	int t;
	for (int i = 0; i < quantity; i++)
	{
		t = 0;
		while (student[i].FIO[t] != '\0')
		{
			if (student[i].FIO[t] == '\n')
				student[i].FIO[t] = '\0';
			t++;
		}
	}


	for (int i = 0; i < quantity; i++)
	{
		float res = 0;
		for (int j = 0; j < 5; j++)
			res += student[i].mark[j];

		res = res / 5;
		if(res>4.0)
			printf("GUIIIIIt %s %d %f", student[i].FIO, student[i].numGrup, res);
	}


	return 0;
}
