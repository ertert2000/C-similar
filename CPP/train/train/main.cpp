#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>


int main()
{
	std::vector<std::string> name;
	std::vector<double> marks;
	std::vector<std::string>::iterator it = begin(name);
	std::string name1;
	int i = 0;

	std::ifstream file;
	file.open("name.txt");
	while (std::getline(file, name1, ' '))
	{
		if(i%2==0)
			name.push_back(name1);

		else
			marks.push_back(std::stoi(name1));

		i++;
	}

	std::cout << *(it) << std::endl;

	file.close();

	std::string &a = name.at(1);

	std::cout << a << std::endl;
	
	for (int i = 0; i < name.size(); i++)
		std::cout << name[i] << " " << marks[i];

	file.open("name.txt", std::ios::app);
	if (file)
	{
		name.push_back("Ivan");

	}


	return 0;
}