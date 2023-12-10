#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void pl_dot_map_matmul(float a[16][16], float b[16][16], float c[16][16])
{
  #pragma HLS INTERFACE m_axi port=a offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=a bundle=ctrl
  #pragma HLS INTERFACE m_axi port=b offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=b bundle=ctrl
  #pragma HLS INTERFACE m_axi port=c offset=slave bundle=data2
  #pragma HLS INTERFACE s_axilite register port=c bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  float tmp[16];
  for (int i_chaining_0 = 0; i_chaining_0 < 16; i_chaining_0 += 1)
  {
    tmp[i_chaining_0] = a[0 + 0] * b[0 + 0];
  }

}

