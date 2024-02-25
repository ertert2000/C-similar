#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

using namespace std;
int main()
{
	const float R = 2.8;
	const float eps = 8.85*pow(10, -12);
	float arr[18][2] = { {1, 2.31},{4, 1.98},{7, 0.7},{9.2, 0},{11, 0.26},{13, 2.23},{15, 3.63},{17, 4.92},{19, 6.03},{21, 6.98},{23, 7.94},{25, 9.21},{27, 10.67},{29, 12.45},{30.4, 12.95},{32.6, 12.30},{35.6, 10.96}, {38.6, 10.54} };
	float resExp[18];
	float resTeor[18];
	float pointH[3][3] = { {20, 7, 6.68}, {20.5, 7, 6.78}, {20, 7.5, 6.56} };
	float pointL[3][3] = { {20, 21, 6.43}, {20.5, 21, 6.67}, {20.5, 21.5, 6.4} };


	for (int i = 0; i < 17; i++)
		resExp[i] = (arr[i][1] - arr[i + 1][1]) / ((arr[i + 1][0] - arr[i][0])/100);

	puts("first point");
	for (int i = 0; i < 17; i++)
		cout << i+1 << ") " << resExp[i] << "\n";

	puts("");


	long double tau = (2 * M_PI * eps * resExp[5]) / (((static_cast < float>(1) / (14 - 9.2)) + (static_cast <float>(1) / (30.4 - 14))) * 100);
	//long double tau = (2 * M_PI * eps * res[8]) / (((static_cast <float>(1) / (20 - 9.2)) + (static_cast <float>(1) / (30.4 - 20))) * 100);
	cout <<"Tau =" << tau << "\n";

	for (int i = 0; i < 17; i++)
		resTeor[i] = ((tau) / (2 * M_PI * eps) * static_cast <float>(1) / ((arr[i][0] - 9.2) / 100)) + ((tau) / (2 * M_PI * eps) * static_cast <float>(1) / ((30.4 - arr[i][0]) / 100));
	
	puts("");
	puts("second point");
	for (int i = 0; i < 17; i++) 
	{
		if (i + 1 == 5 || i + 1 == 15)
			puts("");
		cout << i + 1 << ") " << resTeor[i] << "\n";
	}

	puts("");
	puts("third point");

	long double EyOne, ExOne, AbsExEyOne;
	EyOne = -((static_cast <float>(pointH[0][2]) - static_cast <float>(pointH[2][2])) / ((static_cast <float>(pointH[0][1]) - static_cast <float>(pointH[2][1])) / 100));
	ExOne = -((static_cast <float>(pointH[0][2]) - static_cast <float>(pointH[1][2])) / ((static_cast <float>(pointH[0][0]) - static_cast <float>(pointH[1][0])) / 100));
	AbsExEyOne = sqrt(pow(round(ExOne), 2) + pow(EyOne, 2));
	cout << "x = " << round(ExOne) << "\ny = " << EyOne << "\nmodule = " << AbsExEyOne << endl;

	puts("");

	long double EyTwo, ExTwo, AbsExEyTwo;
	EyTwo = -((static_cast <float>(pointL[0][2]) - static_cast <float>(pointL[2][2])) / ((static_cast <float>(pointL[0][1]) - static_cast <float>(pointL[2][1])) / 100));
	ExTwo = -((static_cast <float>(pointL[0][2]) - static_cast <float>(pointL[1][2])) / ((static_cast <float>(pointL[0][0]) - static_cast <float>(pointL[1][0])) / 100));
	AbsExEyTwo = sqrt(pow(ExTwo, 2) + pow(round(EyTwo), 2));
	cout << "x = " << ExTwo << "\ny = " << round(EyTwo) << "\nmodule = " << AbsExEyTwo << endl;

	puts("\n");
	puts("\\____tolerance____/\n");

	const double tetaFi = 0.01;
	const double tetaL = 0.0005;
	
	long double tetaExOne, tetaEyOne, tetaErrorOne;
	tetaExOne = sqrt(pow((ExOne/ ((static_cast <float>(pointH[0][0]) - static_cast <float>(pointH[1][0])) / 100) * tetaL),2))+sqrt(pow(tetaFi/ ((static_cast <float>(pointH[0][0]) - static_cast <float>(pointH[1][0])) / 100),2));
	tetaEyOne = sqrt(pow((EyOne / ((static_cast <float>(pointH[0][1]) - static_cast <float>(pointH[2][1])) / 100) * tetaL), 2)) + sqrt(pow(tetaFi / ((static_cast <float>(pointH[0][1]) - static_cast <float>(pointH[2][1])) / 100), 2));
	tetaErrorOne = sqrt(pow(tetaExOne, 2) + pow(tetaEyOne, 2));
	
	cout << "top points" << endl;
	cout << "teta Ex = " << round(tetaExOne) << "\nteta Ey = " << tetaEyOne << "\nteta tolerance = " << tetaErrorOne << endl;
	
	
	long double tetaExTwo, tetaEyTwo, tetaErrorTwo;
	tetaExTwo = sqrt(pow((ExTwo / ((static_cast <float>(pointL[0][0]) - static_cast <float>(pointL[1][0])) / 100) * tetaL), 2)) + sqrt(pow(tetaFi / ((static_cast <float>(pointL[0][0]) - static_cast <float>(pointL[1][0])) / 100), 2));
	tetaEyTwo = sqrt(pow((EyTwo / ((static_cast <float>(pointL[0][1]) - static_cast <float>(pointL[2][1])) / 100) * tetaL), 2)) + sqrt(pow(tetaFi / ((static_cast <float>(pointL[0][1]) - static_cast <float>(pointL[2][1])) / 100), 2));
	tetaErrorTwo = sqrt(pow(tetaExTwo, 2) + pow(tetaEyTwo, 2));
	
	puts("");
	cout << "Low points" << endl;
	cout << "teta Ex = " << round(tetaExTwo*10)/10 << "\nteta Ey = " << round(tetaEyTwo*10)/10 << "\nteta tolerance = " << tetaErrorTwo << endl;

	printf("\nteta tolerance top = %.3f +- %.1f \nteta tolerance low = %.3f +- %.1f \n", round(AbsExEyOne*1000)/1000, round(tetaErrorOne*10)/10, round(AbsExEyTwo*1000)/1000, round(tetaErrorTwo*10)/10);

	system("Pause");
	return 0;
}