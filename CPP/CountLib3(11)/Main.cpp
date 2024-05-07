#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define OI 0.1
#define OU 0.1
#define OtH 1
#define OTH 1
#define aT 0.92
#define a2 0.0144

using namespace std;
int main()
{
	vector<double> I = { 0.68, 1.1, 1.6, 1.9, 2.2, 2.5, 2.9 };
	vector<double> U = { 1.1, 1.8, 2.7, 3.2, 3.7, 4.2, 4.8 };
	vector<double> tH = { 824, 924, 965, 1000, 1482, 1621, 1898 };
	vector<double> TH;
	vector<double> T;
	vector<double> OT;
	vector<double> a;
	vector<double> P;
	vector<double> OP;
	double Lamda = 0.0000006;


	puts("OI=0.1 , OU=0.1 , OtH=1 , OTH=1 , aT=0.92 , a2=0.0144");

	puts("");
	puts("P=I * U");
	for (int i = 0; i < I.size(); i++) 
	{
		P.push_back(I[i] * U[i]);
		cout << i << ")P=" << I[i] * U[i] << endl;
	}
	puts("");
	puts("OP = U * OI + I * OU");
	for (int i = 0; i < I.size(); i++)
	{
		OP.push_back(U[i] * OI + I[i] * OU);
		cout << i << ")∅=" << U[i] * OI + I[i] * OU << endl;
	}
	puts("");
	puts("TH = tH + 273");
	for (int i = 0; i < tH.size(); i++)
	{
		TH.push_back(tH[i] + 273);
		cout << i << ")Th=" << tH[i] + 273 << endl;
	}
	puts("");
	puts("T = (TH) / (1 + ( (Lamda*TH) / a2) * log(aT)   //где лямда в метрах и меняется на 5,6,7 мых элементах");
	for (int i = 0; i < tH.size(); i++) 
	{
		if (i > 3) 
		{
			Lamda = 0.000000665;
			//cout << i;
		}
		T.push_back((TH[i]) / (1 + ( (Lamda*TH[i]) / a2) * log(aT) ) );
		cout << i << ")T=" << (TH[i]) / (1 + ((Lamda * TH[i]) / a2) * log(aT)) << endl;
	}
	puts("");
	puts("OT = ((T / TH) ^ 2) * OTH");
	for (int i = 0; i < T.size(); i++)
	{
		OT.push_back(pow( (T[i]/TH[i]), 2) * OTH);
		cout << i << ")OT=" << pow((T[i] / TH[i]), 2) * OTH << endl;
	}
	puts("");
	puts("a in *10^-12  // (P / (T ^ 4)) * 10 ^ 12");
	for (int i = 0; i < T.size(); i++)
	{
		a.push_back((P[i] / pow(T[i], 4)) * pow(10, 12));
		cout << i << ")a=" << a[i] << endl;
	}
	puts("");
	puts("Oa in *10^-12  // a*( (OP/P) + ( (4 * OT) / T) )");
	for (int i = 0; i < T.size(); i++)
	{
		cout << i << ")Oa=" << a[i]*( (OP[i]/P[i]) + ( (4 * OT[i]) / T[i]) ) << endl;
	}

	puts("");
	puts("");
	puts("1. Рассчитаем выборочным методом а = а +- да:");
	puts("");

	double R;
	sort(a.begin(),a.end());

	R=abs(a[6] - a[0]);
	cout << "R = " << a[6]<< " - " << a[0] << " = " << R << endl;

	puts("");
	puts("razmach");
	
	if (abs(a[6] - a[5]) < (0.49 * R)) 
	{
		cout << "|" << a[6] << " - " << a[5] << "| <  0.49 * " << R << endl;
		cout << abs(a[6] - a[5]) << " < " << (0.49 * R) << endl;
	}

	if (abs(a[0] - a[1]) < (0.49 * R))
	{
		cout << "|" << a[0] << " - " << a[1] << "| <  0.49 * " << R << endl;
		cout << abs(a[0] - a[1]) << " < " << (0.49 * R) << endl;
	}
	puts("промахов нет");
	puts("");

	puts("среднее значение выборки");

	double aWithSchtrih;
	double help = 0;

	for (int i = 0; i < a.size(); i++)
		help += a[i];

	aWithSchtrih = help / 7;

	cout << aWithSchtrih << endl;

	puts("");
	puts("Вычислим случайную погрешность измерения через размах :");
	double deltaA;
	deltaA = 0.29 * R;

	cout << "0.29 * R = " << deltaA << endl;

	puts("");
	puts("Рассчитаем среднюю приборную погрешность:");
	double OWithSchtrihFromA = 0.1074;

	cout << OWithSchtrihFromA << endl;

	puts("");
	puts("Рассчитаем полную погрешность измерения:");
	double deltaAWithSchtrih;

	deltaAWithSchtrih = sqrt(pow(deltaA, 2) + pow(OWithSchtrihFromA, 2));

	cout << "sqrt((deltaA ^ 2) + (OWithSchtrihFromA ^ 2)) = " << deltaAWithSchtrih << endl;

	puts("");
	puts("После округления получим:");

	cout << "Aэксп = " << round(aWithSchtrih * 100) / 100 << " +- " << round(deltaAWithSchtrih * 100) / 100 << endl;
	cout << "Aтеор = aT∂S = "<< aT*5.67*25*0.01 << endl;

	puts("");
	puts("2. Методом переноса погрешностей найдём постоянную Стефана-Больцмана:");
	puts("сигма штрих:");
	double sigmaWithSchtrih;

	sigmaWithSchtrih = (aWithSchtrih / (aT * 25))*100;
	cout << sigmaWithSchtrih << " * 10^-8" << endl;
	
	puts("");
	puts("дельта сигма штрих:");
	double deltaSigmaWithSchtrih;

	deltaSigmaWithSchtrih = (deltaAWithSchtrih / (aT * 25)) * 100;
	cout << deltaSigmaWithSchtrih << " * 10^-8" << endl;

	puts("");
	puts("δ сигма :");
	double bettaSigma;

	bettaSigma = (deltaSigmaWithSchtrih / sigmaWithSchtrih)*100;
	cout << bettaSigma << " * 10^-8" << endl;

	puts("");
	puts("После округления получим:");
	cout << "σэксп = " << round(sigmaWithSchtrih) << " +- " << round(deltaSigmaWithSchtrih) << " * 10^-8" << endl;

	cout << "σтеор = 5,67 * 10^-8" << endl;

	getchar();
}