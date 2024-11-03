#include <iostream>
#include <set>
#include <ctime>
#include <chrono>
#include "ArraySet.h"
#include "BitArray.h"
#include "ListSet.h"
#include "WordSet.h"


using namespace std;

char* buildSet(int powerOfset)
{
    char* res = new char[powerOfset + 1];
    const char* digital = "0123456789ABCDEF";
    set<char> setNumbers;

    while (setNumbers.size() < powerOfset)
        setNumbers.insert(digital[rand() & 15]);


    int index = 0;
    for (int num : setNumbers)
        res[index++] = num;

    res[powerOfset] = '\0';
    return res;
}

int main()
{
    srand(time(nullptr));
    int poerOfSet;

    cout << "Enter poer of set: ";
    cin >> poerOfSet;
    cout << endl;

    char* A = buildSet(poerOfSet);
    char* B = buildSet(poerOfSet);
    char* C = buildSet(poerOfSet);
    char* D = buildSet(poerOfSet);

    cout << "Set A: " << A << endl;
    cout << "Set B: " << B << endl;
    cout << "Set C: " << C << endl;
    cout << "Set D: " << D << endl << endl << endl;

    ArraySet As = ArraySet(A, poerOfSet);
    ArraySet Bs = ArraySet(B, poerOfSet);
    ArraySet Cs = ArraySet(C, poerOfSet);
    ArraySet Ds = ArraySet(D, poerOfSet);
    ArraySet Es;

    auto startArray = chrono::high_resolution_clock::now();

    Es.getResult(As, Bs, Cs, Ds);

    auto endArray = chrono::high_resolution_clock::now();
    chrono::duration<double> durationArray = endArray - startArray;

    cout << "Result of array: ";
    cout << Es << endl;

    ListSet Al = ListSet(A, poerOfSet);
    ListSet Bl = ListSet(B, poerOfSet);
    ListSet Cl = ListSet(C, poerOfSet);
    ListSet Dl = ListSet(D, poerOfSet);
    ListSet El;

    auto startLists = chrono::high_resolution_clock::now();

    El.getResult(Al, Bl, Cl, Dl);

    auto endLists = chrono::high_resolution_clock::now();
    chrono::duration<double> durationLists = endLists - startLists;

    cout << "Result of list: ";
    cout << El << endl;

    BitArray Ab = BitArray(A, poerOfSet);
    BitArray Bb = BitArray(B, poerOfSet);
    BitArray Cb = BitArray(C, poerOfSet);
    BitArray Db = BitArray(D, poerOfSet);
    BitArray Eb;

    auto startBool = chrono::high_resolution_clock::now();

    Eb.getResult(Ab, Bb, Cb, Db);
    auto endBool = chrono::high_resolution_clock::now();
    chrono::duration<double> durationBool = endBool - startBool;

    cout << "Result of bit array: ";
    cout << Eb << endl;

    WordSet Aw = WordSet(A, poerOfSet);
    WordSet Bw = WordSet(B, poerOfSet);
    WordSet Cw = WordSet(C, poerOfSet);
    WordSet Dw = WordSet(D, poerOfSet);
    WordSet Ew;

    auto startWord = chrono::high_resolution_clock::now();

    Ew.getResult(Aw, Bw, Cw, Dw);
    auto endWord = chrono::high_resolution_clock::now();
    chrono::duration<double> durationWord = endWord - startWord;

    cout << "Result of machine word: ";
    cout << Ew << endl;

    cout << endl;
    cout << endl;
    cout << "Runtime results of set views" << endl;

    cout << "Lead time array: " << durationArray.count() << " seconds\n";
    cout << "Lead time lists: " << durationLists.count() << " seconds\n";
    cout << "Lead time bit array: " << durationBool.count() << " seconds\n";
    cout << "Lead time machine word: " << durationWord.count() << " seconds\n";
	return 0;
}