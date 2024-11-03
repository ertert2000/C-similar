#include "BitArray.h"
#include <iostream>

BitArray::BitArray() {}

BitArray::BitArray(const char arr[], int powerOfSet)
{
    int index;
    for (int i = 0; i < 16; i++)
        this->sourse[i] = false;

    for (int i = 0; i < powerOfSet; i++)
    {
        index = 0;
        if (arr[i] == 'A' || arr[i] == 'D' || arr[i] == 'B' || arr[i] == 'C' || arr[i] == 'E' || arr[i] == 'F')
            index = (arr[i] - 'A') + 10;
        else
            index = arr[i] - '0';
        this->sourse[index] = true;
    }
}

void BitArray::getResult(BitArray A, BitArray B, BitArray C, BitArray D)
{
    for (int j = 0; j < 16; j++)
        this->sourse[j] = (A.sourse[j] | C.sourse[j]) & ~(B.sourse[j] | D.sourse[j]);
}

std::ostream& operator<<(std::ostream& sys, const BitArray& bitArray)
{
    char ebit[16];
    int sizeOutputArr = 0;
    for (int i = 0; i < 16; i++)
        if (bitArray.sourse[i])
        {
            if (i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15)
                ebit[sizeOutputArr++] = 'A' + (i - 10);
            else
                ebit[sizeOutputArr++] = '0' + i;
        }

    for (int i = 0; i < sizeOutputArr; i++)
        sys << ebit[i];

    return sys;
}
