#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void pl_conv_for(float c[32][239][359], float w[32][16][3][3], float data[16][240][360])
{
  #pragma HLS INTERFACE m_axi port=c offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=c bundle=ctrl
  #pragma HLS INTERFACE m_axi port=w offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=w bundle=ctrl
  #pragma HLS INTERFACE m_axi port=data offset=slave bundle=data2
  #pragma HLS INTERFACE s_axilite register port=data bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  for (int i = 0; i < 32; i += 1)
  {
    for (int i_map_0 = 0; i_map_0 < 1; i_map_0 += 1)
    {
      for (int i_map_1 = 0; i_map_1 < 239; i_map_1 += 1)
      {
        for (int i_map_2 = 0; i_map_2 < 359; i_map_2 += 1)
        {
          float tmp_dot = 0;
          for (int i_dot_0 = 0; i_dot_0 < 16; i_dot_0 += 1)
          {
            for (int i_dot_1 = 0; i_dot_1 < 3; i_dot_1 += 1)
            {
              for (int i_dot_2 = 0; i_dot_2 < 3; i_dot_2 += 1)
              {
                tmp_dot += data[i_dot_0 + 0][(i_dot_1 + -1) + (i_map_1 + 1)][(i_dot_2 + -1) + (i_map_2 + 1)] * w[i][i_dot_1][i_dot_2][i_dot_3];
              }

            }

          }

          c[i][i_map_1][i_map_2] = tmp_dot;
        }

      }

    }

  }

}

