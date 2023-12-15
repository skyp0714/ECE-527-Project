#include "multiply.h"

#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

void old_matmul(ap_fixed<256, 256> a[1024][64], ap_fixed<256, 256> b[1024][64], ap_fixed<256, 256> c[1024][64])
{
  ap_fixed<8, 8> bufferA[128][1024];
  #pragma HLS array_partition variable=bufferA cyclic factor=8 dim=2
  ap_fixed<8, 8> bufferB[256];
  #pragma HLS array_partition variable=bufferB factor=256 dim=1
  ap_fixed<8, 8> tmp[128][256];
  #pragma HLS array_partition variable=tmp factor=256 dim=2
  ap_fixed<256, 256> tmp_256;
  for (int i = 0; i < 1024; i += 128)
  {
    for (int ii = 0; ii < 128; ii += 1)
    {
      for (int k = 0; k < 1024; k += 8)
      {
        #pragma HLS pipeline
        tmp_256 = a[i + ii][k / 8];
        for (int kk = 0; kk < 8; kk += 1)
        {
          #pragma HLS unroll factor=8
          bufferA[ii][k + kk].range(15, 0) = tmp_256.range((kk * 8) + 15, kk * 8);
        }

      }

    }

    for (int j = 0; j < 1024; j += 256)
    {
      for (int ii = 0; ii < 128; ii += 1)
      {
        #pragma HLS pipeline
        for (int jj = 0; jj < 256; jj += 1)
        {
          #pragma HLS unroll factor=256
          tmp[ii][jj] = 0;
        }

      }

      for (int k = 0; k < 1024; k += 1)
      {
        for (int jj = 0; jj < 256; jj += 8)
        {
          #pragma HLS pipeline
          tmp_256 = b[k][(j + jj) / 8];
          for (int jjj = 0; jjj < 8; jjj += 1)
          {
            #pragma HLS unroll factor=8
            bufferB[jj + jjj].range(15, 0) = tmp_256.range((jjj * 8) + 15, jjj * 8);
          }

        }

        for (int ii = 0; ii < 128; ii += 1)
        {
          #pragma HLS pipeline
          for (int jj = 0; jj < 256; jj += 1)
          {
            #pragma HLS unroll factor=8
            tmp[ii][jj] += bufferA[ii][k] * bufferB[jj];
          }

        }

      }

      for (int ii = 0; ii < 128; ii += 1)
      {
        for (int jj = 0; jj < 256; jj += 8)
        {
          #pragma HLS pipeline
          for (int jjj = 0; jjj < 8; jjj += 1)
          {
            #pragma HLS unroll factor=8
            tmp_256.range((jjj * 8) + 15, jjj * 8) = tmp[ii][jj + jjj].range(15, 0);
          }

          c[i + ii][(j + jj) / 8] = tmp_256;
        }

      }

    }

  }

}

void mat_mul(ap_fixed<256, 256> a[1024][64], ap_fixed<256, 256> b[1024][64], ap_fixed<256, 256> c[1024][64])
{
  #pragma HLS INTERFACE m_axi port=a offset=slave bundle=data0
  #pragma HLS INTERFACE s_axilite register port=a bundle=ctrl
  #pragma HLS INTERFACE m_axi port=b offset=slave bundle=data1
  #pragma HLS INTERFACE s_axilite register port=b bundle=ctrl
  #pragma HLS INTERFACE m_axi port=c offset=slave bundle=data2
  #pragma HLS INTERFACE s_axilite register port=c bundle=ctrl
  #pragma HLS INTERFACE s_axilite register port=return bundle=ctrl
  old_matmul(a, b, c);
}

