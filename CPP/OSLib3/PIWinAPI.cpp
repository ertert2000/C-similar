#include "PIWinAPI.h"

constexpr int N = 10000000;
constexpr int STUDENT_ID = 331223;
constexpr int BLOCK_SIZE = 10 * STUDENT_ID;

double pi = 0.0;
LONG current_index = 0;
int total_blocks = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
HANDLE hMutex;
int thread_count;

DWORD WINAPI PiWorker(LPVOID lpParam) 
{
    int thread_id = *(int*)lpParam;

    while (true) 
    {
        int block_index = InterlockedIncrement(&current_index) - 1;
        if (block_index >= total_blocks) break;

        int start = block_index * BLOCK_SIZE;
        int end = min(N, start + BLOCK_SIZE);
        double local_sum = 0.0;

        for (int i = start; i < end; ++i)
            local_sum += ((i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1));

        WaitForSingleObject(hMutex, INFINITE);
        pi += local_sum;
        ReleaseMutex(hMutex);
    }
    return 0;
}

int WinAPIThreads(int thread_count)
{
    std::vector<HANDLE> threads;
    std::vector<int> thread_ids;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < thread_count; ++i) 
    {
        thread_ids.push_back(i);
        HANDLE hThread = CreateThread(NULL, 0, PiWorker, &thread_ids[i], 0, NULL);
        threads.push_back(hThread);
    }

    WaitForMultipleObjects(thread_count, threads.data(), TRUE, INFINITE);

    for (auto h : threads) 
        CloseHandle(h);
    CloseHandle(hMutex);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout.precision(15);
    std::cout << "Computed PI = " << 4 * pi << std::endl;
    std::cout << "Time: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds" << std::endl;

    return 0;
}