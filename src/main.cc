/* src/main.cc */
#include <iostream>
#ifdef CUDA_AVAILABLE
#include "../cuda/kernel.cuh"
#else
#include "../cpu/cpu.h"
#endif

void printAll(float *x, int N) {
  // Print results
  for (int i = 0; i < N; i++) {
    std::cout << x[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  int N = 10;
  float A[N], B[N], C[N];

  // Initialize input arrays
  for (int i = 0; i < N; i++) {
    A[i] = i * 1.0f;
    B[i] = i * 2.0f;
  }

  // Call the appropriate vector add function
#ifdef CUDA_AVAILABLE
  vectorAddCUDA(A, B, C, N);
  std::cout << "CUDA Vector addition successful." << std::endl;
#else
  vectorAddCPU(A, B, C, N);
  std::cout << "CPU Vector addition successful." << std::endl;
#endif

  std::cout << "A: ";
  printAll(A, N);
  std::cout << "B: ";
  printAll(B, N);
  std::cout << "C: ";
  printAll(C, N);

  return 0;
}
