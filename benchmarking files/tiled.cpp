#include "multiply.h"

#include <ap_int.h>

#define N 256
#define M 256
#define K 256
#define T 32

void mat_mul(const double A[N][K],
                     const double B[K][M],
                     double C[N][M]) {
#pragma HLS INTERFACE m_axi port=A depth=65536
#pragma HLS INTERFACE m_axi port=B depth=65536
#pragma HLS INTERFACE m_axi port=C depth=65536

#pragma HLS ARRAY_PARTITION variable=A cyclic factor=8 dim=2
#pragma HLS ARRAY_PARTITION variable=B cyclic factor=8 dim=2
#pragma HLS ARRAY_PARTITION variable=C cyclic factor=8 dim=2

double acc[T];
#pragma HLS ARRAY_PARTITION variable=acc cyclic factor=8

  for (int n = 0; n < N; ++n)
    for (int m = 0; m < M/T; ++m) {

      for (int k = 0; k < K; ++k) {
        double a = A[n][k];
#pragma HLS PIPELINE
        for (int t = 0; t < T; ++t) {
#pragma HLS UNROLL factor=8
          if(k == 0) acc[t] = C[n][m*T+t];
          acc[t] = acc[t] + a * B[k][m*T+t];
        }
      }

      for (int t = 0; t < T; ++t)
#pragma HLS UNROLL factor=8
        C[n][m*T+t] = acc[t];

    }
}
