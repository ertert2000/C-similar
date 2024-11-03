#include "ListSet.h"
#include <iostream>

const char ListSet::universe[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

ListSet::ListSet(const char input[], int powerOfSet) 
{
    head = nullptr;

    for (int i = 0; i < powerOfSet; i++)
    {
        if (i == 0)
            head = creatingASeparateNode(input[i]);
        else
            begin(head, input[i]);
    }

}

ListSet::ListSet() {}

ListSet::~ListSet() {}

ListSet::setS* ListSet::creatingASeparateNode(char data) 
{
    setS* node = new setS;
    node->value = data;
    node->next = nullptr;
    return node;
}

void ListSet::begin(setS*& pattern, char data) 
{
    setS* temp = creatingASeparateNode(data);
    if (pattern == nullptr) {
        pattern = temp;
        return;
    }
    setS* tmp = pattern;
    while (tmp->next != nullptr)
        tmp = tmp->next;
    tmp->next = temp;
}

void ListSet::front(setS*& pattern, char data) 
{
    setS* temp = creatingASeparateNode(data);
    temp->next = pattern;
    pattern = temp;
}

bool ListSet::isinlist(char n, setS* first) 
{
    for (setS* tamp = first; tamp != nullptr; tamp = tamp->next)
        if (n == tamp->value)
            return true;
    return false;
}

void ListSet::getResult(ListSet A, ListSet B, ListSet C, ListSet D)
{
    for (int elem = 0; elem < 16; elem++)
        if (((isinlist(universe[elem], A.head) || isinlist(universe[elem], C.head))) && (!(isinlist(universe[elem], B.head) || isinlist(universe[elem], D.head))))
        {
            if (head == nullptr)
                head = creatingASeparateNode(universe[elem]);
            else
                front(head, universe[elem]);
        }
}

std::ostream& operator<<(std::ostream& sys, const ListSet& listSet)
{
    ListSet::setS* current = listSet.head;
    while (current != nullptr) {
        sys << current->value;
        current = current->next;
    }
    return sys;
}