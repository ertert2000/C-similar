#include <iostream>
#include <bitset>
#include <limits>

//VARRRR 17 long and float





int main()
{
    long initialNumber;

    long mask1, mask2, supermask;

    long group1, group2, res;

    float initialNumberFloatB;

    uint32_t mask1Float, mask2Float, supermaskFloat;

    uint32_t group1Float, group2Float, resFloat;

    int mostSignificantChanged;
    int qantityBits;

    int mostSignificantChanged2;
    int qantityBits2;

    int choice;
    int betweenGroups;



    switch (choice)
    {
    case 1:
        std::cout << "Enter your numder: ";
        while (!(std::cin >> initialNumber))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::bitset<16> bit(initialNumber);

        std::cout << "Bit Representation: ";
        std::cout << bit << std::endl;


        std::cout << "Enter most significant changed: ";
        while (!(std::cin >> mostSignificantChanged) || (mostSignificantChanged < 0) || (mostSignificantChanged > 16))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter group size: ";
        while (!(std::cin >> qantityBits) || (qantityBits < 0))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter most significant changed: ";
        while (!(std::cin >> mostSignificantChanged2) || (mostSignificantChanged2 < 0) || (mostSignificantChanged2 > 16))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter group size: ";
        while (!(std::cin >> qantityBits2) || (qantityBits2 < 0))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }


        //x2 - (x1 + y1), ���  �2 - ������ ������� �����q ������, �1 - ������ ������� ������ ������, �1 - ���������� ��������� ������ ������.
        betweenGroups = mostSignificantChanged2 - (qantityBits + mostSignificantChanged);
        if (qantityBits2 > qantityBits)
        {
            mask1 = ((1 << qantityBits + betweenGroups) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2 = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
            supermask = mask1 | mask2;

            group1 = (initialNumber & mask1) >> mostSignificantChanged;
            group1 = ((group1 << betweenGroups) | (group1 >> (qantityBits))) & ((1 << qantityBits + betweenGroups) - 1);
            group1 = (group1 << (qantityBits + 1 + mostSignificantChanged));

            group2 = (initialNumber & mask2) >> mostSignificantChanged2;
            group2 = (group2 << mostSignificantChanged);

            res = (initialNumber & ~supermask) | group1;
            res = res | group2;
        }
        if (qantityBits2 < qantityBits)
        {
            mask1 = ((1 << qantityBits) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2 = ((1 << qantityBits2 + betweenGroups) - 1) << (mostSignificantChanged2 - betweenGroups);

            supermask = mask1 | mask2;

            group1 = (initialNumber & mask1) >> mostSignificantChanged;
            group1 = (group1 << (mostSignificantChanged2 - 1));

            group2 = (initialNumber & mask2) >> (mostSignificantChanged2 - betweenGroups);
            group2 = ((group2 >> betweenGroups) | (group2 << (qantityBits2))) & ((1 << qantityBits2 + betweenGroups) - 1);
            group2 = (group2 << (mostSignificantChanged));

            res = (initialNumber & ~supermask) | group1;
            res = res | group2;
        }
        else
        {
            mask1 = ((1 << qantityBits) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2 = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
            supermask = mask1 | mask2;

            group1 = (initialNumber & mask1) >> mostSignificantChanged;
            group1 = group1 << mostSignificantChanged2;

            group2 = (initialNumber & mask2) >> mostSignificantChanged2;
            group2 = group2 << mostSignificantChanged;

            res = (initialNumber & ~supermask) | group1;
            res = res | group2;

        }

        std::bitset<16> bit5(res);
        std::cout << bit5 << std::endl;

        std::cout << res << std::endl;
        break;
    case 2:
        std::cout << "Enter your numder: ";
        while (!(std::cin >> initialNumberFloatB))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }
        uint32_t initialNumberFloat = *reinterpret_cast<uint32_t*>(&initialNumberFloatB);

        std::bitset<16> bit(initialNumberFloat);

        std::cout << "Bit Representation: ";
        std::cout << bit << std::endl;


        std::cout << "Enter most significant changed: ";
        while (!(std::cin >> mostSignificantChanged) || (mostSignificantChanged < 0) || (mostSignificantChanged > 16))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter group size: ";
        while (!(std::cin >> qantityBits) || (qantityBits < 0))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter most significant changed: ";
        while (!(std::cin >> mostSignificantChanged2) || (mostSignificantChanged2 < 0) || (mostSignificantChanged2 > 16))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }

        std::cout << "Enter group size: ";
        while (!(std::cin >> qantityBits2) || (qantityBits2 < 0))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error" << std::endl;
        }


        //x2 - (x1 + y1), ���  �2 - ������ ������� �����q ������, �1 - ������ ������� ������ ������, �1 - ���������� ��������� ������ ������.
        betweenGroups = mostSignificantChanged2 - (qantityBits + mostSignificantChanged);
        if (qantityBits2 > qantityBits)
        {
            mask1Float = ((1 << qantityBits + betweenGroups) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2Float = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
            supermaskFloat = mask1Float | mask2Float;

            group1Float = (initialNumberFloat & mask1Float) >> mostSignificantChanged;
            group1Float = ((group1Float << betweenGroups) | (group1Float >> (qantityBits))) & ((1 << qantityBits + betweenGroups) - 1);
            group1Float = (group1Float << (qantityBits + 1 + mostSignificantChanged));

            group2Float = (initialNumberFloat & mask2Float) >> mostSignificantChanged2;
            group2Float = (group2Float << mostSignificantChanged);

            resFloat = (initialNumberFloat & ~supermaskFloat) | group1Float;
            resFloat = resFloat | group2Float;
        }
        if (qantityBits2 < qantityBits)
        {
            mask1Float = ((1 << qantityBits) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2Float = ((1 << qantityBits2 + betweenGroups) - 1) << (mostSignificantChanged2 - betweenGroups);

            supermaskFloat = mask1Float | mask2Float;

            group1Float = (initialNumberFloat & mask1Float) >> mostSignificantChanged;
            group1Float = (group1Float << (mostSignificantChanged2 - 1));

            group2Float = (initialNumberFloat & mask2Float) >> (mostSignificantChanged2 - betweenGroups);
            group2Float = ((group2Float >> betweenGroups) | (group2Float << (qantityBits2))) & ((1 << qantityBits2 + betweenGroups) - 1);
            group2Float = (group2Float << (mostSignificantChanged));

            resFloat = (initialNumberFloat & ~supermaskFloat) | group1Float;
            resFloat = resFloat | group2Float;
        }
        else
        {
            mask1Float = ((1 << qantityBits) - 1) << mostSignificantChanged; // ����� ������ ������
            mask2Float = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
            supermaskFloat = mask1Float | mask2Float;

            group1Float = (initialNumberFloat & mask1Float) >> mostSignificantChanged;
            group1Float = group1Float << mostSignificantChanged2;

            group2Float = (initialNumberFloat & mask2Float) >> mostSignificantChanged2;
            group2Float = group2Float << mostSignificantChanged;

            resFloat = (initialNumberFloat & ~supermaskFloat) | group1Float;
            resFloat = resFloat | group2Float;

        }

        std::bitset<16> bit5(resFloat);
        std::cout << bit5 << std::endl;

        std::cout << res << std::endl;
        break;
    case 3:
        return 0;
    }
}