#include "Omp.h"  
#include <omp.h>  
#include <iostream>  
constexpr int N = 10000000;  
constexpr int STUDENT_ID = 331223;  
constexpr int BLOCK_SIZE = 10 * STUDENT_ID;  

int OMP(int thread_count)  
{  
   double pi = 0.0;  

   double start = omp_get_wtime();  

   #ifdef _OPENMP  
   #pragma omp parallel for num_threads(thread_count) schedule(static) reduction(+:pi)  
   for (int i = 0; i < N; ++i)  
       pi += (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);  
   #else  
   std::cerr << "OpenMP is not enabled. Please enable OpenMP in your compiler settings.\n";  
   return -1;  
   #endif  

   double end = omp_get_wtime();  

   std::cout.precision(15);  
   std::cout << "Computed PI = " << 4 * pi << "\n";  
   std::cout << "Time: " << (end - start) << " seconds\n";  

   #pragma omp parallel  
   {
       #pragma omp single  
       std::cout << "Used threads: " << omp_get_num_threads() << std::endl;  
   }  
   return 0;  
}