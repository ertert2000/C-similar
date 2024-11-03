#include <iostream>
#include <cmath>

long long mod_pow(int base, int exp, int mod) 
{
    long long result = 1;
    long long base_mod = base % mod;

    while (exp > 0) 
    {
        if (exp % 2 == 1) 
            result = (result * base_mod) % mod;

        base_mod = (base_mod * base_mod) % mod;
        exp /= 2;
    }
    return result;
}

int main() 
{
    for (int i = 1; i < 3; i++) 
        std::cout << "118^" << i << " = " << mod_pow(14, i, 47) << " (mod 46)" << std::endl;

    std::cout << mod_pow(108, pow(118, 43), 46);
    return 0;
}
