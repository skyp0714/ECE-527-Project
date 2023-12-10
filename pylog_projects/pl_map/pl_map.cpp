#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void pl_map(float w[3][3][16][32], float data[360][240][16])
{
  #pragma HLS INTERFACE m_axi port=w offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=w bundle=ctrl
  #pragma HLS INTERFACE m_axi port=data offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=data bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  float c[180][120][1];
  for (int i_map_0 = 0; i_map_0 < 180; i_map_0 += 1)
  {
    for (int i_map_1 = 0; i_map_1 < 120; i_map_1 += 1)
    {
      for (int i_map_2 = 0; i_map_2 < 1; i_map_2 += 1)
      {
        float tmp_dot = 0;
        for (int i_dot_0 = 0; i_dot_0 < 3; i_dot_0 += 1)
        {
          for (int i_dot_1 = 0; i_dot_1 < 3; i_dot_1 += 1)
          {
            for (int i_dot_2 = 0; i_dot_2 < 16; i_dot_2 += 1)
            {
              tmp_dot += data[(i_dot_0 + -1) + ((i_map_0 * 2) + 1)][(i_dot_1 + -1) + ((i_map_1 * 2) + 1)][i_dot_2 + 0] * w[i_dot_0][i_dot_1][i_dot_2][1];
            }

          }

        }

        c[i_map_0][i_map_1] = tmp_dot;
      }

    }

  }

}

