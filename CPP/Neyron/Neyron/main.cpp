#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <windows.h>
#define wiegts 3


using namespace std;

double w[wiegts];

double activate(double a)
{
	return (a <= 0) ? 0 : 1;
	//return 1 / (1 + pow(2.7182818284, -a));
}

double rightProp(double inputs[wiegts])
{
	double res = 0;

	for (int i = 0; i < wiegts; i++)
		res += w[i] * inputs[i];

	return res;
}

void traing(int data[4][3], int exp[4])
{
	const double LR = 0.1, EPCH = 5; //скорость ; кол-во итераций
	double error;
	for (int i = 0; i < EPCH; i++)
		for (int j = 0; j < 4; j++)
		{
			error = exp[j] - activate(rightProp((double*)data[j]));
			for (int n = 0; n < wiegts; n++) {
				w[n] += LR * error * data[j][n];

				cout << i << ") interation generations " << j << ") wiegts" << w[n] << endl;
			}
		}
}

int main()
{
	int traingData[4][3] = { {0, 12548, 1}, {0, 10, 1}, {1, 0, 24}, {0, 1, 3547} }, expResultat[4] = {0, 0, 1, 0};

	int answer;
	cout << "solve a problem:" << endl;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (j != 2)
				cout << traingData[i][j] << " ";
			else
			{
				if (i == 3)
					cout << traingData[i][j] << "|?" << endl;
				else
					cout << traingData[i][j] << "|" << expResultat[i] << endl;
			}
		}

	cout << "what answer?" << endl;
	cin >> answer;
	if (answer == 0)
		cout << "fucking handsome" << endl;
	else
		cout << "the neural network is smarter than you, fool :)" << endl;

	/*cout << "and now she will learn" << endl;
	Sleep(4000);
	system("cls");

	for (int i = 0; i < 3; i++)
	{
		cout << i+1 << endl;
		Sleep(3000);
		system("cls");
	}*/
	
	srand(1);
	for (int i = 0; i < wiegts; i++)
		w[i] = fmod(rand() % 100000000 * 0.1, 1.05);

	traing(traingData, expResultat);

	for (int i = 0; i < wiegts; i++)
		w[i] = (w[i] > 0) ? w[i] : 0;

	bool flag = true;
	double enterMy[3];
	char yesNo;

	while (flag)
	{
		cout << "enter your numbers (three numbers)" << endl;
		for (int i = 0; i < wiegts; i++)
			cin >> enterMy[i];

		cout << "answer: " << activate(rightProp(enterMy)) << endl;

		cout << "do you want to continue? (Y/N)" << endl;

		cin >> yesNo;
		if (yesNo == 'n' || yesNo == 'N')
			flag = false;
		else
			system("cls");
	}
	return 0;
}