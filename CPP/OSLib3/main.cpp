#include "PIWinAPI.h"
#include "Omp.h"

int main()
{
	int threadsCount[] = { 1,2,4,8,12,16 };


	for (auto i : threadsCount)
	{
		std::cout << "Threads: " << i << std::endl;
		WinAPIThreads(i);
	}

	std::cout << std::endl << std::endl;

	for (auto i : threadsCount)
	{
		std::cout << "Threads: " << i << std::endl;
		OMP(i);
	}
}