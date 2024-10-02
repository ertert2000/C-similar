#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <stdlib.h>

int Aarr[16], Barr[16], Carr[16], Darr[16];

int globalResPower = 0;

using namespace std;

struct set 
{
    char value;
    set* next;
};

void prinset(char* toout)
{
    int i = 0;
    cout << " array ";
    while (toout[i] != '\0') 
    {
        cout << toout[i];
        i++;
    }
    cout << endl;
}

void buildBool(const char arr[], bool* bBool, int powerOfSet)
{
    int index;
    for (int i = 0; i < 16; i++)
        bBool[i] = false;

    for (int i = 0; i < powerOfSet; i++)
    {
        index = 0;
        if (arr[i] == 'A' || arr[i] == 'D' || arr[i] == 'B' || arr[i] == 'C' || arr[i] == 'E' || arr[i] == 'F')
            index = (arr[i] - 'A') + 10;
        else
            index = arr[i] - '0';
        bBool[index] = true;
    }
}

char* buildSet(int powerOfset)
{
    char* res = new char[powerOfset + 1];
    const char* digital = "0123456789ABCDEF";

    for (int i = 0; i < powerOfset; i++)
        res[i] = digital[rand() & 15];

    res[powerOfset] = '\0';
    return res;
}

void buildWord(const char array[], int len, unsigned int& result)
{
    result = 0;
    for (int i = 0; i < len; ++i)
    {
        if (array[i] >= '0' && array[i] <= '9')
            result |= 1 << (array[i] - '0');
        else if (array[i] >= 'A' && array[i] <= 'F')
            result |= 1 << (array[i] - 'A' + 10);
    }
}

bool inSet(char n, char* set)
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


bool isinlist(char n, set* first)
{
    bool res = false;

    for (set* tamp = first; tamp != nullptr; tamp = tamp->next) 
        if (n == tamp->value) 
            res = true;


    return res;
}


void print_list(set* toout)
{
    for (; toout != nullptr; toout = toout->next)
        cout << toout->value;
}

set* creatingASeparateNode(char data)
{
    set* node = nullptr;
    node = new set;

    node->value = data;
    node->next = nullptr;

    return node;
}

void begin(set*& pattern, char data)
{
    set* temp = creatingASeparateNode(data);
    if (pattern == nullptr)
    {
        pattern = temp;
        return;
    }
    set* tmp = pattern;
    while (tmp->next != nullptr)
        tmp = tmp->next;

    tmp->next = temp;

}

set* buildLists(set* A, set* B, set* C, set* D, char* universe)
{
    set* elbefore = nullptr, * resfirst = nullptr, * restamp;
    for (int elem = 0; elem < 16; elem++)
        if (((isinlist(universe[elem], A) || isinlist(universe[elem], C))) && (!(isinlist(universe[elem], B) || isinlist(universe[elem], D))))
        {
            if (resfirst == nullptr)
            {
                resfirst = creatingASeparateNode(universe[elem]);
            }
            else
            {
                begin(resfirst, universe[elem]);
            }
        }

    return resfirst;
}

void workingArray(char* A, char* B, char* C, char* D, char res[], char* universe)
{
    for (int i = 0; i < 16; i++)
        if ((inSet(universe[i], A) | inSet(universe[i], C)) & ~(inSet(universe[i], B) | inSet(universe[i], D))) 
        {
            res[globalResPower] = universe[i];
            globalResPower++;
        }

    res[globalResPower] = '\0';
}

int main() 
{
    srand(time(nullptr));

    int poerOfSet;

    char universe[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    char res[17];

    set* sA = nullptr;
    set* sB = nullptr;
    set* sC = nullptr;
    set* sD = nullptr;

    cout << "Enter poer of set: ";
    cin >> poerOfSet;
    cout << endl;

    char* A = buildSet(poerOfSet);
    char* B = buildSet(poerOfSet);
    char* C = buildSet(poerOfSet);
    char* D = buildSet(poerOfSet);

    cout << "Set A: ";
    for (int i = 0; i < poerOfSet; i++)
        cout << A[i];
    cout << endl;
    cout << "Set B: ";
    for (int i = 0; i < poerOfSet; i++)
        cout << B[i];
    cout << endl;
    cout << "Set C: ";
    for (int i = 0; i < poerOfSet; i++)
        cout << C[i];
    cout << endl;
    cout << "Set D: ";
    for (int i = 0; i < poerOfSet; i++)
        cout << D[i];
    cout << endl;
    cout << endl;

    auto startArray = chrono::high_resolution_clock::now();

    workingArray(A, B, C, D, res, universe);

    auto endArray = chrono::high_resolution_clock::now();
    chrono::duration<double> durationArray = endArray - startArray;
    
    cout << "Result of array: ";
    for (int i = 0; i < globalResPower; i++)
        cout << res[i];

    cout << endl;

    for (int i = 0; i < poerOfSet; i++)
    {
        if (i == 0)
            sA = creatingASeparateNode(A[i]);
        else
            begin(sA, A[i]);
    }

    for (int i = 0; i < poerOfSet; i++)
    {
        if (i == 0)
            sB = creatingASeparateNode(B[i]);
        else
            begin(sB, B[i]);
    }

    for (int i = 0; i < poerOfSet; i++)
    {
        if (i == 0)
            sC = creatingASeparateNode(C[i]);
        else
            begin(sC, C[i]);
    }

    for (int i = 0; i < poerOfSet; i++)
    {
        if (i == 0)
            sD = creatingASeparateNode(D[i]);
        else
            begin(sD, D[i]);
    }

    auto startLists = chrono::high_resolution_clock::now();

    set* sE = buildLists(sA, sB, sC, sD, universe);

    auto endLists = chrono::high_resolution_clock::now();
    chrono::duration<double> durationLists = endLists - startLists;
    
    cout << "Result of list: ";
    print_list(sE);

    bool aBool[16], bBool[16], cBool[16], dBool[16];
    buildBool(A, aBool, poerOfSet);
    buildBool(C, cBool, poerOfSet);
    buildBool(B, bBool, poerOfSet);
    buildBool(D, dBool, poerOfSet);
    bool resB[16];
    char ebit[16];

    cout << endl;

    auto startBool = chrono::high_resolution_clock::now();

    for (int j = 0; j < 16; j++)
        resB[j] = (aBool[j] | cBool[j]) & ~(bBool[j] | dBool[j]);


    auto endBool = chrono::high_resolution_clock::now();
    chrono::duration<double> durationBool = endBool - startBool;
    
    cout << "Result of bit array: ";
    int sizeOutputArr = 0;
    for (int i = 0; i < 16; i++)
        if(resB[i])
        {
            if (i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15)
                ebit[sizeOutputArr++] = 'A' + (i - 10);
            else
                ebit[sizeOutputArr++] = '0' + i;
        }

    for (int i = 0; i < sizeOutputArr; i++)
        cout << ebit[i];

    cout << endl;
    unsigned int aWord, bWord, cWord, dWord, resW;

    buildWord(A, poerOfSet, aWord);
    buildWord(B, poerOfSet, bWord);
    buildWord(C, poerOfSet, cWord);
    buildWord(D, poerOfSet, dWord);

    auto startWord = chrono::high_resolution_clock::now();

    resW = (aWord | cWord) & ~(bWord | dWord);

    auto endWord = chrono::high_resolution_clock::now();
    chrono::duration<double> durationWord = endWord - startWord;

    cout << "Result of machine word: ";
    for (int i = 15; i >= 0; --i)
        if (resW & (1 << i))
        {
            if (i >= 10)
                std::cout << static_cast<char>('A' + (i - 10));
            else
                std::cout << static_cast<char>('0' + i);
        }

    cout << endl;
    cout << endl;
    cout << "Runtime results of set views" << endl;

    cout << "Lead time array: " << durationArray.count() << " seconds\n";
    cout << "Lead time lists: " << durationLists.count() << " seconds\n";
    cout << "Lead time bit array: " << durationBool.count() << " seconds\n";
    cout << "Lead time machine word: " << durationWord.count() << " seconds";


    return 0;
}
