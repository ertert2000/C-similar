#pragma once
#include <iostream>
class WordSet
{
private:
    unsigned int sourse;
public:
    WordSet();
    WordSet(const char array[], int powerOfSet);

    void getResult(WordSet A, WordSet B, WordSet C, WordSet D);

    friend std::ostream& operator<<(std::ostream& sys, const WordSet& wordSet);
};

