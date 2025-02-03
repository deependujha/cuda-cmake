void vectorAddCPU(const float *A, const float *B, float *C, int N) {
  for (int i = 0; i < N; i++) {
    C[i] = A[i] + B[i];
  }
}
