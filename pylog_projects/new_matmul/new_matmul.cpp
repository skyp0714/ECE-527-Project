#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void new_matmul(float a[256][256], float b[256][256], float c[256][256])
{
  #pragma HLS INTERFACE m_axi port=a offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=a bundle=ctrl
  #pragma HLS INTERFACE m_axi port=b offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=b bundle=ctrl
  #pragma HLS INTERFACE m_axi port=c offset=slave bundle=data2
  #pragma HLS INTERFACE s_axilite register port=c bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  float acc[32];
  #pragma HLS ARRAY_PARTITION variable=b cyclic factor=32 dim=2
  #pragma HLS ARRAY_PARTITION variable=c cyclic factor=32 dim=2
  #pragma HLS ARRAY_PARTITION variable=acc cyclic factor=32
  for (int i = 0; i < 256; i += 1)
  {
    for (int j = 0; j < 8.0; j += 1)
    {
      for (int k = 0; k < 256; k += 1)
      {
        float tmp = a[i][k];
        for (int t = 0; t < 32; t += 1)
        {
          #pragma HLS unroll factor=32
          #pragma HLS pipeline
          if (k == 0)
          {
            acc[t] = c[i][(j * 32) + t];
          }

          acc[t] += tmp * b[k][(j * 32) + t];
        }

      }

      for (int t = 0; t < 32; t += 1)
      {
        #pragma HLS unroll factor=32
        c[i][(j * 32) + t] = acc[t];
      }

    }

  }

}

