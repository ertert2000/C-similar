#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

int main() {
    CarHead* voiture = malloc(sizeof(CarHead));
    BrandHead* marque = malloc(sizeof(BrandHead));
    InitBrand(marque);
    InitCar(voiture);
    int n = 0;
    while (n != 6)
    {
        n = menu();
        traitement(&n, voiture, marque);
    }
    return 0;
}
