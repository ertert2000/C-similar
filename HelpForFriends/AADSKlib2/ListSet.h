#pragma once
#include <iostream>

class ListSet 
{
private:
    struct setS 
    {
        char value;
        setS* next;
    };
    setS* head;
    static const char universe[];

    setS* creatingASeparateNode(char data);
    void begin(setS*& pattern, char data);
    void front(setS*& pattern, char data);
    bool isinlist(char n, setS* first);

public:
    ListSet(const char input[], int powerOfSet);
    ListSet();
    ~ListSet();

    void getResult(ListSet A, ListSet B, ListSet C, ListSet D);

    friend std::ostream& operator<<(std::ostream& sys, const ListSet& listSet);
};

