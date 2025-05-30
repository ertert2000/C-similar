#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>



int WinAPIThreads(int thread_count);


DWORD WINAPI PiWorker(LPVOID lpParam);