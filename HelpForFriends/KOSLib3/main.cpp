#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>

constexpr long long N = 10000000;
constexpr int BLOCK_SIZE = 10 * 331230;
constexpr int TOTAL_BLOCKS = N / BLOCK_SIZE;


CRITICAL_SECTION cs;
volatile int currentBlock = 0;
double pi = 0.0;

DWORD WINAPI CalculatePiBlock(LPVOID lpParam) {
    while (true) {
        int block;
        EnterCriticalSection(&cs);
        if (currentBlock >= TOTAL_BLOCKS) {
            LeaveCriticalSection(&cs);
            return 0;
        }
        block = currentBlock++;
        LeaveCriticalSection(&cs);

        long long start = block * BLOCK_SIZE;
        long long end = start + BLOCK_SIZE;
        double localSum = 0.0;

        for (long long i = start; i < end; ++i) {
            localSum += 4.0 * pow(-1, i) / (2 * i + 1);
        }

        EnterCriticalSection(&cs);
        pi += localSum;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int winTreads(int numThreads) {
    InitializeCriticalSection(&cs);
    std::vector<HANDLE> threads(numThreads);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = CreateThread(nullptr, 0, CalculatePiBlock, nullptr, CREATE_SUSPENDED, nullptr);
    }
    for (int i = 0; i < numThreads; ++i) {
        ResumeThread(threads[i]);
    }
    WaitForMultipleObjects(numThreads, threads.data(), TRUE, INFINITE);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout.precision(15);
    std::cout << "Pi ≈ " << pi << std::endl;
    std::cout << "Time: " << std::chrono::duration<double>(end - start).count() << " s" << std::endl;

    for (HANDLE h : threads) CloseHandle(h);
    DeleteCriticalSection(&cs);
    return 0;
}


int OMP(int numThreads) {
    double pi = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, BLOCK_SIZE) num_threads(numThreads) reduction(+:pi)
    for (long long i = 0; i < N; ++i) {
        pi += 4.0 * pow(-1, i) / (2 * i + 1);
    }
    double end = omp_get_wtime();

    std::cout.precision(15);
    std::cout << "Pi ≈ " << pi << std::endl;
    std::cout << "Time: " << (end - start) << " seconds" << std::endl;
    return 0;
}

int main() {
	std::cout << "Using WinThreads:" << std::endl;
    for (auto i : {1,2,4,8,12,16})
    {
        std::cout << "Thread" << i << std::endl;
        winTreads(i);
    }
	std::cout << "\nUsing OpenMP:" << std::endl;
    for (auto i : { 1,2,4,8,12,16 })
    {
        std::cout << "Thread" << i << std::endl;
        OMP(i);
    }
	return 0;
}