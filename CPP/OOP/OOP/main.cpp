#include <iostream>

using namespace std;


class Person
{
public:
	std::string name;
	int age;
	void print()
	{
		cout << "Name: " << name << "\tAge: " << age << endl;
	}
};


int main()
{
	Person person;
	Person *ptr = &person;
	

	person.name = "Alex";
	person.age = 19;


	std::string name = person.name; //8
	int age = person.age;
	person.print();

	cout << "Name: " << name << "\tAge: " << age << endl;

	//puts("");
	ptr->name = "Tom";
	ptr->age = 25;

	ptr->print();

	return 0;
}