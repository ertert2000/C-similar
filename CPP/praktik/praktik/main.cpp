#include <iostream>
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
	Car CAR;
	CAR.speed = 230.5f;
	//CAR.model = "BMW";

	printf("max speed: %f, model: ", CAR.speed);
	return 0;
}