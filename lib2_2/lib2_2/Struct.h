#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    char* name;
    char* nameGenerations;
    int socket;
    int technologicalProcess;
    float frequency; //частота
    float frequencyInTurboBoost;
    int* cache;
    int TMP;
} PROCESSOR_STRUCT;

#endif /* STRUCT_H */
