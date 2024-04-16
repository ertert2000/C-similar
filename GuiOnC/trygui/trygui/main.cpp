#include <iostream>
#include <math.h>


using namespace std;
int main()
{
	int n, k, res=0;
	printf("enter n");
	cin >> n;
	cin >> k;

	for (int i = 1; i <= n; i++)
		res = res + pow(i, k);

	cout << "summ:" << res;
	return 0;
}