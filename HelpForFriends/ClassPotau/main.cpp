#include <iostream>

class IntSet
{
private:
    static const int MAX_SIZE = 1000;
    int elements[MAX_SIZE];
    int size;

public:
    IntSet() : size(0) {}

    void add(int num)
    {
        if (!contains(num) && size < MAX_SIZE)
            elements[size++] = num;
    }

    void remove(int num)
    {
        for (int i = 0; i < size; ++i)
            if (elements[i] == num)
            {
                for (int j = i; j < size - 1; ++j)
                    elements[j] = elements[j + 1];
                size--;
                break;
            }
    }

    bool contains(int num) const
    {
        for (int i = 0; i < size; ++i)
            if (elements[i] == num)
                return true;
        return false;
    }

    void print() const
    {
        std::cout << "{";
        for (int i = 0; i < size; i++)
        {
            if (i == (size - 1))
            {
                std::cout << elements[i];
                break;
            }

            std::cout << elements[i] << ", ";

        }
        std::cout << "}" << std::endl;
    }
};

int main()
{
    IntSet set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(3);
    set.add(2);
    set.add(1);

    set.print();

    return 0;
}