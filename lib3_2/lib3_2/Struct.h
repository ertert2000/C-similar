#pragma once

#ifndef STRUCT_H
#define STRUCT_H

typedef struct PROCESSOR_STRUCT
{
    char* name;
    char* nameGenerations;
    int socket;
    int technologicalProcess;
    float frequency; //�������
    float frequencyInTurboBoost;
    int* cache;
    int* TMP;
    struct PROCESSOR_STRUCT* next;
} PROCESSOR_STRUCT;

typedef struct COPY_PROCESSOR_STRUCT
{
    char* name;
    char* nameGenerations;
    int socket;
    int technologicalProcess;
    float frequency; //�������
    float frequencyInTurboBoost;
    int* cache;
    int TMP;
    struct COPY_PROCESSOR_STRUCT* next;
} COPY_PROCESSOR_STRUCT;

#endif /* STRUCT_H */