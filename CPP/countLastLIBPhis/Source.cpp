#include <iostream>
#include <vector>
#include <cmath>


int main()
{
	std::vector<double> red_max = { 15, 16, 14, 14.5, 14, 14 };
	std::vector<double> red_min = { 4, 4, 5, 3.5, 2, 3 };

	std::vector<double> orange_max = { 37, 34, 36, 38, 34, 34 };
	std::vector<double> orange_min = { 9, 8.5, 15, 10, 9, 14 };

	std::vector<double> yellow_max = { 51, 50.5, 49, 43, 57, 47 };
	std::vector<double> yellow_min = { 12, 14, 12, 8, 18, 15 };

	std::vector<double> green_max = { 57, 56, 50, 55, 48, 54 };
	std::vector<double> green_min = { 11, 12, 19, 14, 15, 15 };

	std::vector<double> blue_max = { 10, 9, 10, 10, 10, 9 };
	std::vector<double> blue_min = { 4, 4.5, 5.5, 4, 5.5, 4 };

	std::vector<double> fiol_max = { 1.5, 1.5, 1.2, 1.5, 1.4, 1.6 };
	std::vector<double> fiol_min = { 0.5, 1, 0.9, 1, 0.8, 1 };

	double ImaxRed = 0;
	double sigmaImaxRed = 0;
	double SImaxRed = 0;
	double VImaxRed = 0;
	double SstrichImaxRed = 0;
	double DeltaStrichImaxRed = 0;
	double saveMaxValue = 0;
	

	std::vector<double> red_max_delta;
	std::vector<double> red_min_delta;
	std::vector<double> orange_max_delta;
	std::vector<double> orange_min_delta;
	std::vector<double> yellow_max_delta;
	std::vector<double> yellow_min_delta;
	std::vector<double> green_max_delta;
	std::vector<double> green_min_delta;
	std::vector<double> blue_max_delta;
	std::vector<double> blue_min_delta;
	std::vector<double> fiol_max_delta;
	std::vector<double> fiol_min_delta;

	std::cout << "красные максимальные значения: " << std::endl;
	for(int i = 0; i < 6; i++)
		std::cout << i << ") " << red_max[i] << std::endl;

	puts("");
	for (int i = 0; i < red_max.size(); i++)
	{
		ImaxRed += red_max[i];
	}
	ImaxRed = ImaxRed / red_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < red_max.size(); i++)
	{
		red_max_delta.push_back(red_max[i] - ImaxRed);
		red_max_delta[i] = pow(red_max_delta[i], 2);
		std::cout << i << ") " << red_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < red_max_delta.size(); i++)
	{
		sigmaImaxRed += red_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");

	
	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(red_max.begin(), red_max.end()) - *min_element(red_max.begin(), red_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(red_max.begin(), red_max.end()) << "-" << *min_element(red_max.begin(), red_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;
	//==========================================

	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "красные минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << red_min[i] << std::endl;

	puts("");
	for (int i = 0; i < red_min.size(); i++)
	{
		ImaxRed += red_min[i];
	}
	ImaxRed = ImaxRed / red_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < red_min.size(); i++)
	{
		red_min_delta.push_back(red_min[i] - ImaxRed);
		red_min_delta[i] = pow(red_min_delta[i], 2);
		std::cout << i << ") " << red_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < red_min_delta.size(); i++)
	{
		sigmaImaxRed += red_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(red_min.begin(), red_min.end()) - *min_element(red_min.begin(), red_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(red_min.begin(), red_min.end()) << "-" << *min_element(red_min.begin(), red_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");

	std::cout << "P красные(поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");
	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;
	saveMaxValue = 0;

	std::cout << "оранжевые максимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << orange_max[i] << std::endl;

	puts("");
	for (int i = 0; i < orange_max.size(); i++)
	{
		ImaxRed += orange_max[i];
	}
	ImaxRed = ImaxRed / orange_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < orange_max.size(); i++)
	{
		orange_max_delta.push_back(orange_max[i] - ImaxRed);
		orange_max_delta[i] = pow(orange_max_delta[i], 2);
		std::cout << i << ") " << orange_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < orange_max_delta.size(); i++)
	{
		sigmaImaxRed += orange_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(orange_max.begin(), orange_max.end()) - *min_element(orange_max.begin(), orange_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(orange_max.begin(), orange_max.end()) << "-" << *min_element(orange_max.begin(), orange_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "оранжевые минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << orange_min[i] << std::endl;

	puts("");
	for (int i = 0; i < orange_min.size(); i++)
	{
		ImaxRed += orange_min[i];
	}
	ImaxRed = ImaxRed / orange_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < orange_min.size(); i++)
	{
		orange_min_delta.push_back(orange_min[i] - ImaxRed);
		orange_min_delta[i] = pow(orange_min_delta[i], 2);
		std::cout << i << ") " << orange_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < orange_min_delta.size(); i++)
	{
		sigmaImaxRed += orange_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(orange_min.begin(), orange_min.end()) - *min_element(orange_min.begin(), orange_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(orange_min.begin(), orange_min.end()) << "-" << *min_element(orange_min.begin(), orange_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	std::cout << "P оранжевые(поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;
	saveMaxValue = 0;

	std::cout << "желтые максимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << yellow_max[i] << std::endl;

	puts("");
	for (int i = 0; i < yellow_max.size(); i++)
	{
		ImaxRed += yellow_max[i];
	}
	ImaxRed = ImaxRed / yellow_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < yellow_max.size(); i++)
	{
		yellow_max_delta.push_back(yellow_max[i] - ImaxRed);
		yellow_max_delta[i] = pow(yellow_max_delta[i], 2);
		std::cout << i << ") " << yellow_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < yellow_max_delta.size(); i++)
	{
		sigmaImaxRed += yellow_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(yellow_max.begin(), yellow_max.end()) - *min_element(yellow_max.begin(), yellow_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(yellow_max.begin(), yellow_max.end()) << "-" << *min_element(yellow_max.begin(), yellow_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "желтые минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << yellow_min[i] << std::endl;

	puts("");
	for (int i = 0; i < yellow_min.size(); i++)
	{
		ImaxRed += yellow_min[i];
	}
	ImaxRed = ImaxRed / yellow_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < yellow_min.size(); i++)
	{
		yellow_min_delta.push_back(yellow_min[i] - ImaxRed);
		yellow_min_delta[i] = pow(yellow_min_delta[i], 2);
		std::cout << i << ") " << yellow_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < yellow_min_delta.size(); i++)
	{
		sigmaImaxRed += yellow_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(yellow_min.begin(), yellow_min.end()) - *min_element(yellow_min.begin(), yellow_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(yellow_min.begin(), yellow_min.end()) << "-" << *min_element(yellow_min.begin(), yellow_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	std::cout << "P желтые(поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;
	saveMaxValue = 0;

	std::cout << "зеленые максимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << green_max[i] << std::endl;

	puts("");
	for (int i = 0; i < green_max.size(); i++)
	{
		ImaxRed += green_max[i];
	}
	ImaxRed = ImaxRed / green_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < green_max.size(); i++)
	{
		green_max_delta.push_back(green_max[i] - ImaxRed);
		green_max_delta[i] = pow(green_max_delta[i], 2);
		std::cout << i << ") " << green_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < green_max_delta.size(); i++)
	{
		sigmaImaxRed += green_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(green_max.begin(), green_max.end()) - *min_element(green_max.begin(), green_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(green_max.begin(), green_max.end()) << "-" << *min_element(green_max.begin(), green_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "зеленые минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << green_min[i] << std::endl;

	puts("");
	for (int i = 0; i < green_min.size(); i++)
	{
		ImaxRed += green_min[i];
	}
	ImaxRed = ImaxRed / green_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < green_min.size(); i++)
	{
		green_min_delta.push_back(green_min[i] - ImaxRed);
		green_min_delta[i] = pow(green_min_delta[i], 2);
		std::cout << i << ") " << green_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < green_min_delta.size(); i++)
	{
		sigmaImaxRed += green_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(green_min.begin(), green_min.end()) - *min_element(green_min.begin(), green_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(green_min.begin(), green_min.end()) << "-" << *min_element(green_min.begin(), green_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	std::cout << "P зеленые(поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;
	saveMaxValue = 0;

	std::cout << "синие максимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << blue_max[i] << std::endl;

	puts("");
	for (int i = 0; i < blue_max.size(); i++)
	{
		ImaxRed += blue_max[i];
	}
	ImaxRed = ImaxRed / blue_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < blue_max.size(); i++)
	{
		blue_max_delta.push_back(blue_max[i] - ImaxRed);
		blue_max_delta[i] = pow(blue_max_delta[i], 2);
		std::cout << i << ") " << blue_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < blue_max_delta.size(); i++)
	{
		sigmaImaxRed += blue_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(blue_max.begin(), blue_max.end()) - *min_element(blue_max.begin(), blue_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(blue_max.begin(), blue_max.end()) << "-" << *min_element(blue_max.begin(), blue_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "синие минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << blue_min[i] << std::endl;

	puts("");
	for (int i = 0; i < blue_min.size(); i++)
	{
		ImaxRed += blue_min[i];
	}
	ImaxRed = ImaxRed / blue_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < blue_min.size(); i++)
	{
		blue_min_delta.push_back(blue_min[i] - ImaxRed);
		blue_min_delta[i] = pow(blue_min_delta[i], 2);
		std::cout << i << ") " << blue_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < blue_min_delta.size(); i++)
	{
		sigmaImaxRed += blue_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(blue_min.begin(), blue_min.end()) - *min_element(blue_min.begin(), blue_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(blue_min.begin(), blue_min.end()) << "-" << *min_element(blue_min.begin(), blue_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	std::cout << "P синие(поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");

	//==========================================
	puts("\n\n");
	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;
	saveMaxValue = 0;

	std::cout << "фиолетовые максимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << fiol_max[i] << std::endl;

	puts("");
	for (int i = 0; i < fiol_max.size(); i++)
	{
		ImaxRed += fiol_max[i];
	}
	ImaxRed = ImaxRed / fiol_max.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < fiol_max.size(); i++)
	{
		fiol_max_delta.push_back(fiol_max[i] - ImaxRed);
		fiol_max_delta[i] = pow(fiol_max_delta[i], 2);
		std::cout << i << ") " << fiol_max_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < fiol_max_delta.size(); i++)
	{
		sigmaImaxRed += fiol_max_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(fiol_max.begin(), fiol_max.end()) - *min_element(fiol_max.begin(), fiol_max.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(fiol_max.begin(), fiol_max.end()) << "-" << *min_element(fiol_max.begin(), fiol_max.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	saveMaxValue = ImaxRed;

	//==========================================

	puts("\n\n");

	ImaxRed = 0;
	sigmaImaxRed = 0;
	SImaxRed = 0;
	VImaxRed = 0;
	SstrichImaxRed = 0;
	DeltaStrichImaxRed = 0;


	std::cout << "фиолетовые минимальные значения: " << std::endl;
	for (int i = 0; i < 6; i++)
		std::cout << i << ") " << fiol_min[i] << std::endl;

	puts("");
	for (int i = 0; i < fiol_min.size(); i++)
	{
		ImaxRed += fiol_min[i];
	}
	ImaxRed = ImaxRed / fiol_min.size();

	std::cout << "(среднее значение)Imax = " << ImaxRed << std::endl;
	puts("");


	puts("дельта Imax в квадрате: ");
	for (int i = 0; i < fiol_min.size(); i++)
	{
		fiol_min_delta.push_back(fiol_min[i] - ImaxRed);
		fiol_min_delta[i] = pow(fiol_min_delta[i], 2);
		std::cout << i << ") " << fiol_min_delta[i] << std::endl;
	}
	puts("");

	puts("сумма дельта Imax в квадрате (всех шести):");
	for (int i = 0; i < fiol_min_delta.size(); i++)
	{
		sigmaImaxRed += fiol_min_delta[i];
	}
	std::cout << sigmaImaxRed << std::endl;
	puts("");


	SImaxRed = sqrt((sigmaImaxRed / 5));
	std::cout << "SImax = sqrt(сумма дельта Imax в квадрате / N - 1) = " << "sqrt(" << sigmaImaxRed << "/" << 5 << ") = " << SImaxRed << std::endl;
	puts("");

	VImaxRed = abs(*max_element(fiol_min.begin(), fiol_min.end()) - *min_element(fiol_min.begin(), fiol_min.end())) / SImaxRed;
	std::cout << "VImax = |maxKрасные максимальные значения - minKрасные максимальные значения| / SImax = " << "|" << *max_element(fiol_min.begin(), fiol_min.end()) << "-" << *min_element(fiol_min.begin(), fiol_min.end()) << "| / " << SImaxRed << " = " << VImaxRed << std::endl;
	puts("");

	SstrichImaxRed = SImaxRed / (sqrt(6));
	std::cout << "SstrichImax = SImax / sqtr(6) = " << SImaxRed << " / " << sqrt(6) << " = " << SstrichImaxRed << std::endl;
	puts("");

	DeltaStrichImaxRed = 2.6 * SstrichImaxRed;
	std::cout << "DeltaStrichImax = t(P,N) * SstrichImax = " << 2.6 << " * " << SstrichImaxRed << " = " << DeltaStrichImaxRed << std::endl;
	puts("");

	std::cout << "Ответ: " << ImaxRed << "+-" << DeltaStrichImaxRed;
	puts("");
	std::cout << "P фиолетовый (поляризация) = sqrt((Imax^2 - Imin^2) / (Imax^2 + Imin^2)) = sqrt((" << saveMaxValue << " - " << ImaxRed << ") / (" << saveMaxValue << " + " << ImaxRed << ")) = " << sqrt((saveMaxValue - ImaxRed) / (saveMaxValue + ImaxRed)) << std::endl;
	puts("");
	return 0;
}