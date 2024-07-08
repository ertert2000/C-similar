#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <unordered_map>
#include <sstream>

void RLE()
{
	setlocale(LC_ALL, "rus");
	int i = 0;
	int count = 1;
	std::string output;
	std::string buffer;
	std::ifstream source("24_demo (1).txt");
	std::ofstream out("out.txt");

	std::getline(source, buffer);

	while (buffer[i] != '\0')
	{
		if (buffer[i] == buffer[i + 1])
			count++;

		if (buffer[i] != buffer[i + 1])
		{
			output += std::to_string(count);
			output += buffer[i];
			count = 1;
		}
		i++;
	}

	out << output;
}

void LZW(std::string buffer)
{
	std::vector<int> finalyCode;

	std::unordered_map<std::string, int>table;

	std::ofstream out("out.txt");

	int code = 256;

	for (int i = 0; i < 256; i++)
	{
		std::string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	std::string first = "", center = "";

	first += buffer[0];

	for (int i = 0; i < buffer.length(); i++)
	{
		if (i != buffer.length() - 1)
			center += buffer[i + 1];
		if (table.find(first + center) != table.end())
			first = first + center;

		else
		{
			finalyCode.push_back(table[first]);
			table[first + center] = code;
			code++;
			first = center;
		}
		center = "";
	}

	finalyCode.push_back(table[first]);

	for (int i = 0; i < finalyCode.size(); i++)
	{
		out << finalyCode[i];
		out << '\n';
	}


}

void decoding(std::vector<int> op)
{
	std::string endstr;

	std::ofstream end("2.txt");

	std::unordered_map<int, std::string> table;
	for (int i = 0; i <= 255; i++) 
	{
		std::string ch = "";
		ch += char(i);
		table[i] = ch;
	}

	int old = op[0], num;

	std::string str = table[old];
	std::string center = "";

	center += str[0];

	endstr += str;

	int count = 256;

	for (int i = 0; i < op.size() - 1; i++) 
	{
		num = op[i + 1];
		if (table.find(num) == table.end()) 
		{
			str = table[old];
			str = str + center;
		} 
		else
			str = table[num];


		endstr += str;
		center = "";

		center += str[0];

		table[count] = table[old] + center;

		count++;
		old = num;
	}

	end << endstr;
}

int main()
{
	int i = 0;
	std::string buffer;

	std::stringstream multy;

	std::ifstream source("source.txt");

	multy << source.rdbuf();

	buffer = multy.str();

	std::vector<int> finalyCode;
	LZW(buffer);

	buffer.clear();

	std::ifstream compress("out.txt");

	while (std::getline(compress, buffer))
	{
		finalyCode.push_back(stoi(buffer));
		i++;
	}


	decoding(finalyCode);

	return 0;
}