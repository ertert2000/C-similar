#include <iostream>
//#include <curl/curl.h>
#include "main.h"

using namespace std;

class Car
{
public:
	float speed;
	char model[100];

private:

};

int main()
{
	int x = 0;
	Car CAR;
	CAR.speed = 230.5f;
	//CAR.model = "BMW";
	int length = 10;

	for (int i = 0; i < length; i++)
	{
		for (int n = 0; n < length; n++)
		{
			for(int j = 0; j< length;j++)
				for (int b = 0; b < length; b++)
				{
					x += 1;
					cout << x <<endl;
				}
		}
	}
	printf("max speed: %f, model: ", CAR.speed);
	return 0;
}