#include "ArraySet.h"
#include <iostream>


const char ArraySet::universe[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

ArraySet::ArraySet(){}

ArraySet::ArraySet(char input[], int power)
{
    this->sourse = input;
    this->powerSet = power;
}

void ArraySet::getResult(ArraySet A, ArraySet B, ArraySet C, ArraySet D)
{
    int resPower = 0;

    for (int i = 0; i < 16; i++)
        if ((inSet(universe[i], A.sourse) | inSet(universe[i], C.sourse)) & ~(inSet(universe[i], B.sourse) | inSet(universe[i], D.sourse)))
        {
            this->sourse[resPower] = universe[i];
            resPower++;
        }

    this->sourse[resPower] = '\0';
}

bool ArraySet::inSet(char n, char* set)
{
    int i = 0;
    bool res = false;
    while ((set[i] != '\0') && (res != 1))
    {
        if (n == set[i])
            res = true;
        i++;
    }
    return res;
}

std::ostream& operator<< (std::ostream& sys, const ArraySet& arraySet)
{
    sys << arraySet.sourse;
    return sys;
}
