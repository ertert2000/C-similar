#include <iostream>
#include <bitset>
#include <limits>

//Выполнить циклический сдвиг в заданную пользователем сторону на не-которое количество разрядов в 
//пределах определённой группы разрядов, количе-ство которых и номер младшего разряда в группе задаются с клавиатуры.

int main()
{
	unsigned int initialNumber;

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

	while (!(std::cin >> qantityBits) || (qantityBits < 0))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}


	unsigned int mask = ((1 << qantityBits) - 1) << mostSignificantChanged;
	std::bitset<16> bit2(mask);

	std::cout << bit2 << std::endl;

	unsigned int group = (initialNumber & mask) >> mostSignificantChanged;

	std::bitset<16> bit3(group);

	std::cout << bit3 << std::endl;

	group = (group << 1) | (group >> (qantityBits - 1));

	group = (group << mostSignificantChanged); //& mask;

	std::bitset<16> bit4(group);

	std::cout << bit4 << std::endl;

	unsigned int res = (initialNumber & ~mask) | group;

	std::bitset<16> bit5(res);

	std::cout << bit5 << std::endl;

	std::cout << res << std::endl;

	return 0;
}