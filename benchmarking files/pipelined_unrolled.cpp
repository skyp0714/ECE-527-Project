#include <ap_int.h>

#define MATRIX_SIZE 256

typedef int matrix_t;

void mat_mul(const matrix_t A[MATRIX_SIZE][MATRIX_SIZE],
                     const matrix_t B[MATRIX_SIZE][MATRIX_SIZE],
                     matrix_t C[MATRIX_SIZE][MATRIX_SIZE]) {
#pragma HLS INTERFACE m_axi port=A depth=65536
#pragma HLS INTERFACE m_axi port=B depth=65536
#pragma HLS INTERFACE m_axi port=C depth=65536

// #pragma HLS ARRAY_PARTITION variable=A cyclic factor=8 dim=2
// #pragma HLS ARRAY_PARTITION variable=B cyclic factor=8 dim=1
// #pragma HLS ARRAY_PARTITION variable=C cyclic factor=8 dim=2

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
#pragma HLS PIPELINE II=1
      matrix_t tmp = 0;

      for (int k = 0; k < MATRIX_SIZE; k++) {
#pragma HLS UNROLL factor=8
        tmp += A[i][k] * B[k][j];
      }

      C[i][j] = tmp;
    }
  }
}
