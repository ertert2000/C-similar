#pragma once
#ifndef CGI_FUNCTION_h
#define CGI_FUNCTION_h

/*Structutre representing an element of the list of brands */
typedef struct Brand {
    char* name;
    struct Brand* prev;
    struct Brand* next;
} Brand;

/*Structure of acces to the element of the list of brands*/
typedef struct brand_head {
    struct Brand* first;
    struct Brand* last;
}BrandHead;

/*Structure representing an element of the list of cars*/
typedef struct Car {
    char* name;
    Brand* manufacturer;
    int year;
    float weigth;
    int mileage;
    float engineSize;
    float price[2];
    struct Car* next;
    struct Car* prev;
} Car;

/*Structure of acces to the element of the list of cars*/
typedef struct car_head {
    struct Car* first;
    struct Car* last;
} CarHead;

#ifdef __cplusplus
extern "C" {
#endif
    char* mystrtok(char* str, const char* delim);
    void InitCar(CarHead* my_carHead);
    void InitBrand(BrandHead* my_brandHead);
    void PushBack_Car(CarHead* my_carHead, char* string, Brand* marque);
    Brand* PushBack_Brand(BrandHead* my_brandHead, char* brand);
    void ReadFromFile(CarHead* mycarHead, BrandHead* my_brandHead);
    void ReadFromConsole(CarHead* mycarHead, BrandHead* my_brandHead);
    void PrintBrand(BrandHead* my_brandHead);
    void PrintCar(CarHead* mycarHead);
    void PopElem(CarHead* mycarHead);
    void ClearCar(CarHead* mycarHead);
    void clearBrand(BrandHead* mybrandhead);
    int menu(void);
    void traitement(int* option, CarHead* mycarHead, BrandHead* mybrandHead);



#ifdef __cplusplus
}
#endif

#endif