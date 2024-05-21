#include <iostream>
#include <string>


using namespace std;
void strhashing()
{
	string h1 = "Educba";
	cout << "The string given to get the hash value is " << h1 << "\n" << endl;
	hash<string> hash_obj;
	cout << "The hash value of the given string is : " << hash_obj(h1) << endl;
}
int main()
{
	cout << "Program to demonstrate the string hash values that are returned using hash class and its objects." << "\n" << endl;
	strhashing();

	return 0;
}