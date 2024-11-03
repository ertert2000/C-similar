#include "WordSet.h"
#include <iostream>


WordSet::WordSet(){}

WordSet::WordSet(const char array[], int powerOfSet)
{
    sourse = 0;
    for (int i = 0; i < powerOfSet; ++i)
    {
        if (array[i] >= '0' && array[i] <= '9')
            sourse |= 1 << (array[i] - '0');
        else if (array[i] >= 'A' && array[i] <= 'F')
            sourse |= 1 << (array[i] - 'A' + 10);
    }
}

void WordSet::getResult(WordSet A, WordSet B, WordSet C, WordSet D)
{
    sourse = (A.sourse | C.sourse) & ~(B.sourse | D.sourse);
}

std::ostream& operator<<(std::ostream& sys, const WordSet& wordSet)
{
    for (int i = 15; i >= 0; --i)
        if (wordSet.sourse & (1 << i))
        {
            if (i >= 10)
                sys << static_cast<char>('A' + (i - 10));
            else
                sys << static_cast<char>('0' + i);
        }

    return sys;
}
