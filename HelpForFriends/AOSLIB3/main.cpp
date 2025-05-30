#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>

const int N = 10000000;
const int STUDENT_ID = 331222;
const int BLOCK_SIZE = 10 * STUDENT_ID;

CRITICAL_SECTION cs;
volatile int current_block = 0;
volatile bool done = false;
double pi = 0.0;

DWORD WINAPI CalculatePiBlock(LPVOID) 
{
    while (true) 
    {
        int start;
        EnterCriticalSection(&cs);
        if (current_block >= N) 
        {
            LeaveCriticalSection(&cs);
            break;
        }
        start = current_block;
        current_block += BLOCK_SIZE;
        LeaveCriticalSection(&cs);

        double local_sum = 0.0;
        int end = min(start + BLOCK_SIZE, N);
        for (int i = start; i < end; ++i) {
            local_sum += pow(-1, i) / (2.0 * i + 1.0);
        }

        EnterCriticalSection(&cs);
        pi += local_sum;
        LeaveCriticalSection(&cs);
    }

    return 0;
}

int WinAPI() 
{
    InitializeCriticalSection(&cs);

    for (int threads_count : {1, 2, 4, 8, 12, 16}) 
    {
        pi = 0.0;
        current_block = 0;

        std::vector<HANDLE> threads(threads_count);
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < threads_count; ++i) {
            threads[i] = CreateThread(nullptr, 0, CalculatePiBlock, nullptr, 0, nullptr);
        }

        WaitForMultipleObjects(threads_count, threads.data(), TRUE, INFINITE);

        for (HANDLE t : threads) CloseHandle(t);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        std::cout.precision(15);
        std::cout << "Threads: " << threads_count << ", Pi ≈ " << (4.0 * pi) << ", Time: " << duration.count() << "s\n";
    }

    DeleteCriticalSection(&cs);
    return 0;
}


int OPMThreads()
{
    for (int threads_count : {1, 2, 4, 8, 12, 16}) {
        double pi = 0.0;
        auto start_time = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for schedule(dynamic, BLOCK_SIZE) num_threads(threads_count) reduction(+:pi)
        for (int i = 0; i < N; ++i) {
            pi += pow(-1, i) / (2.0 * i + 1.0);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        std::cout.precision(15);
        std::cout << "Threads: " << threads_count << ", Pi ≈ " << (4.0 * pi) << ", Time: " << duration.count() << "s\n";
    }

    return 0;
}

int main()
{
	std::cout << "Using WinAPI:\n";
	WinAPI();
	std::cout << "\nUsing OpenMP:\n";
	OPMThreads();
	return 0;
}