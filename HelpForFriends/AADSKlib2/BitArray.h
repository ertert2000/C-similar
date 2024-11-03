#pragma once
#include <iostream>
class BitArray
{
private:
	bool* sourse = new bool[16];

public:
	BitArray();
	BitArray(const char arr[], int powerOfSet);

	void getResult(BitArray A, BitArray B, BitArray C, BitArray D);

	friend std::ostream& operator<<(std::ostream& sys, const BitArray& bitArray);
};

