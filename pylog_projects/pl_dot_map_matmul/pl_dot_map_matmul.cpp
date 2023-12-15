#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void pl_dot_map_matmul(float a[256][256], float b[256][256], float c[256][256])
{
  #pragma HLS INTERFACE m_axi port=a offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=a bundle=ctrl
  #pragma HLS INTERFACE m_axi port=b offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=b bundle=ctrl
  #pragma HLS INTERFACE m_axi port=c offset=slave bundle=data2
  #pragma HLS INTERFACE s_axilite register port=c bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  for (int i = 0; i < 256; i += 1)
  {
    #pragma HLS pipeline
    for (int j = 0; j < 256; j += 1)
    {
      #pragma HLS unroll
      float tmp_dot = 0;
      for (int i_dot_0 = 0; i_dot_0 < 256; i_dot_0 += 1)
      {
        tmp_dot += a[i][i_dot_1] * b[i_dot_0][j];
      }

      c[i][j] = tmp_dot;
    }

  }

}

