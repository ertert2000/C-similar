#pragma once
#define MAXCACHE 3
#include "Struct.h"

PROCESSOR_STRUCT* init(char* name,
	char* nameGenerations,
	int socket,
	int technologicalProcess,
	float frequency,
	float frequencyInTurboBoost,
	int* cache);

void addFront(PROCESSOR_STRUCT** processor,
	char* name,
	char* nameGenerations,
	int socket,
	int technologicalProcess,
	float frequency,
	float frequencyInTurboBoost,
	int* cache);

void* copyNodes(PROCESSOR_STRUCT* processor, int copyElements[], int qualityCopyElements);