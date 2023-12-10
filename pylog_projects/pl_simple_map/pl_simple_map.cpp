#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void pl_simple_map(float a[4][5][6], float b[4][5][6])
{
  #pragma HLS INTERFACE m_axi port=a offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=a bundle=ctrl
  #pragma HLS INTERFACE m_axi port=b offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=b bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  float tmp_dot = 0;
  for (int i_dot_0 = 0; i_dot_0 < 4; i_dot_0 += 1)
  {
    for (int i_dot_1 = 0; i_dot_1 < 5; i_dot_1 += 1)
    {
      for (int i_dot_2 = 0; i_dot_2 < 6; i_dot_2 += 1)
      {
        tmp_dot += a[i_dot_0][i_dot_1][i_dot_2] * b[i_dot_0][i_dot_1][i_dot_2];
      }

    }

  }

  c = tmp_dot;
}

