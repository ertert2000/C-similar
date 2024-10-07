#include <iostream>
#include <bitset>
#include <limits>

int main()
{
    long initialNumber;

    long mask1, mask2, supermask;
    long group1, group2, res;

    float initialNumberFloatB, rfloat;

    uint32_t mask1Float, mask2Float, supermaskFloat;
    uint32_t group1Float, group2Float, resFloat;

    uint32_t initialNumberFloat;
    uint32_t* initialNumberFloatS;

    int mostSignificantChanged;
    int qantityBits;

    int mostSignificantChanged2;
    int qantityBits2;

    int choice = 0;
    int firstFlag = 0;
    int betweenGroups;

    bool interfaceFlag = true;




    while (interfaceFlag)
    {
        std::cout << "#=======Choice Mode======#" << std::endl;
        std::cout << "1 - long mode" << std::endl;
        std::cout << "2 - float mode" << std::endl;
        std::cout << "3 - exit" << std::endl;
        std::cout << "#========================#" << std::endl;

        if (firstFlag)
        {
            std::cin.clear();
            while (std::cin.get() != '\n');
            firstFlag++;
        }
        std::cin >> choice;
        std::bitset<32> bitres;
        std::bitset<32> bitInit;

        system("cls");
        switch (choice)
        {
        case 1:
            std::cout << "Enter initial numder: ";
            while (!(std::cin >> initialNumber))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            bitInit = std::bitset<32>(initialNumber);

            std::cout << "Bit Representation: ";
            std::cout << bitInit << std::endl;

            std::cout << "Enter most first significant changed: ";
            while (!(std::cin >> mostSignificantChanged) || (mostSignificantChanged < 0) || (mostSignificantChanged > 32))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter the size of the first group: ";
            while (!(std::cin >> qantityBits) || (qantityBits < 0))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter most second significant changed: ";
            while (!(std::cin >> mostSignificantChanged2) || (mostSignificantChanged2 < 0) || (mostSignificantChanged2 > 32))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter the size of the second group: ";
            while (!(std::cin >> qantityBits2) || (qantityBits2 < 0))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            betweenGroups = mostSignificantChanged2 - (qantityBits + mostSignificantChanged);
            if (betweenGroups < 0)
            {
                std::cout << "The groups overlap, try again" << std::endl;
                system("pause");
                system("cls");
                break;
            }
            if (qantityBits2 > qantityBits)
            {
                mask1 = ((1 << qantityBits + betweenGroups) - 1) << mostSignificantChanged;
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
                mask1 = ((1 << qantityBits) - 1) << mostSignificantChanged;
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
                mask1 = ((1 << qantityBits) - 1) << mostSignificantChanged;
                mask2 = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
                supermask = mask1 | mask2;

                group1 = (initialNumber & mask1) >> mostSignificantChanged;
                group1 = group1 << mostSignificantChanged2;

                group2 = (initialNumber & mask2) >> mostSignificantChanged2;
                group2 = group2 << mostSignificantChanged;

                res = (initialNumber & ~supermask) | group1;
                res = res | group2;

            }

            std::cout << "Bit representation of the result: ";
            bitres = std::bitset<32>(res);
            std::cout << bitres << std::endl;

            std::cout << "Result in binary: ";
            std::cout << res << std::endl;


            system("pause");
            system("cls");
            break;
        case 2:
            std::cout << "Enter your initial numder: ";
            while (!(std::cin >> initialNumberFloatB))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }
            initialNumberFloatS = reinterpret_cast<uint32_t*>(&initialNumberFloatB);
            initialNumberFloat = *initialNumberFloatS;

            bitInit = std::bitset<32>(initialNumberFloat);

            std::cout << "Bit Representation: ";
            std::cout << bitInit << std::endl;


            std::cout << "Enter most first significant changed: ";
            while (!(std::cin >> mostSignificantChanged) || (mostSignificantChanged < 0) || (mostSignificantChanged > 32))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter the size of the first group: ";
            while (!(std::cin >> qantityBits) || (qantityBits < 0))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter most second significant changed: ";
            while (!(std::cin >> mostSignificantChanged2) || (mostSignificantChanged2 < 0) || (mostSignificantChanged2 > 32))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }

            std::cout << "Enter the size of the second group: ";
            while (!(std::cin >> qantityBits2) || (qantityBits2 < 0))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error" << std::endl;
            }



            betweenGroups = mostSignificantChanged2 - (qantityBits + mostSignificantChanged);
            if (betweenGroups < 0)
            {
                std::cout << "The groups overlap, try again" << std::endl;
                system("pause");
                system("cls");
                break;
            }
            if (qantityBits2 > qantityBits)
            {
                mask1Float = ((1 << qantityBits + betweenGroups) - 1) << mostSignificantChanged;
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
                mask1Float = ((1 << qantityBits) - 1) << mostSignificantChanged;
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
                mask1Float = ((1 << qantityBits) - 1) << mostSignificantChanged;
                mask2Float = ((1 << qantityBits2) - 1) << mostSignificantChanged2;
                supermaskFloat = mask1Float | mask2Float;

                group1Float = (initialNumberFloat & mask1Float) >> mostSignificantChanged;
                group1Float = group1Float << mostSignificantChanged2;

                group2Float = (initialNumberFloat & mask2Float) >> mostSignificantChanged2;
                group2Float = group2Float << mostSignificantChanged;

                resFloat = (initialNumberFloat & ~supermaskFloat) | group1Float;
                resFloat = resFloat | group2Float;

            }

            memcpy(&rfloat, &resFloat, sizeof(rfloat));
            std::cout << "Bit representation of the result: ";
            bitres = std::bitset<32>(resFloat);
            std::cout << bitres << std::endl;

            std::cout << "Result in binary: ";
            std::cout << rfloat << std::endl;


            system("pause");
            system("cls");
            break;
        case 3:
            interfaceFlag = false;
            break;
        default:
            std::cout << "Input error" << std::endl;

            std::cin.clear();
            system("pause");
            system("cls");
            break;
        }

    }
    return 0;
}