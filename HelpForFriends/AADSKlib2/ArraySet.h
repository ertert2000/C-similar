#pragma once
#include <ostream>
class ArraySet
{
private:
	char* sourse = new char[16];
	int powerSet;
    static const char universe[];

    bool inSet(char n, char* set);

public:
    ArraySet();
    ArraySet(char input[], int power);

    void getResult(ArraySet A, ArraySet B, ArraySet C, ArraySet D);

    friend std::ostream& operator<<(std::ostream& sys, const ArraySet& arraySet);
};

