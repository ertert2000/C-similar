#include <stdio.h>

struct Car
{
	float speed;
	char model;
};
int main()
{
	struct Car BMW;
	
	BMW.model = "BMW A5";
	BMW.speed = 210;

	struct Car Audi;

	Audi.model = "Audi Q7";
	Audi.speed = 190.5f;

	printf("%f,%f", BMW.speed, Audi.speed);
	return 0;
}