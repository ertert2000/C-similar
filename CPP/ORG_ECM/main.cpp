#include <iostream>
#include <bitset>
#include <limits>

//Поменять местами заданные пользователем группы рядом стоящих бит, но-мера старших разрядов этих групп и количество бит в группе, вводится с клавиа-туры.

int main()
{
	int initialNumber;

	int mostSignificantChanged;
	int mostSignificantDistynation;
	int qantityBits;

	while (!(std::cin >> initialNumber))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//cout
	}

	std::bitset<16> bit(initialNumber);

	std::cout << bit << std::endl;

	while (!(std::cin >> mostSignificantChanged) || (mostSignificantChanged < 0) || (mostSignificantChanged > 16))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	while (!(std::cin >> mostSignificantDistynation) || (mostSignificantDistynation < 0) || (mostSignificantDistynation > 16))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	while (!(std::cin >> qantityBits))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	//фориком раскрутить битсет и переставлять элементы

	return 0;
}