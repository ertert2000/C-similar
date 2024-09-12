#include <iostream>
#include <bitset>
#include <conio.h>


int main()
{ 
	//max value = -32768 - 32767
	short int x = 32767;

	for (std::size_t i = 0; i < sizeof x; i++)
		std::cout << " " << std::bitset<8>(reinterpret_cast<unsigned char*>(&x)[i]);

	std::cout << "\n" << sizeof x;

	return 0;
}