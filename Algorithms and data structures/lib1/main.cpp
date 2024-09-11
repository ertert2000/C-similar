#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
	const int qiality = 4;

	int A[qiality]{ 2, 5, 4, 8 };
	int D[qiality]{ 5, 0, 7, 6 };
	int C[qiality]{ 1, 5, 9, 3 };
	int B[qiality]{ 9, 0, 5, 7 };

	std::vector<int> E;
	std::unordered_set<int> BSet(B, B + qiality);

	for (int i = 0; i < qiality; i++)
		E.push_back(A[i]);

	for (int i = 0; i < qiality; i++)
		if (BSet.find(C[i]) != BSet.end())
			E.push_back(C[i]);

	for (int i = 0; i < qiality; i++)
		E.push_back(D[i]);

	for (int i = 0; i < E.size(); i++)
		std::cout << E[i] << std::endl;


	return 0;
}