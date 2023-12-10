import numpy as np
# from pysim import *
from pylog import *

@pylog(mode='debug')#(mode='pysim')
def target_matmul(a, b, c):
    # tiling by 8
    acc = np.empty((8,), pl_float)
    pragma("HLS ARRAY_PARTITION variable=a cyclic factor=8 dim=1")
    pragma("HLS ARRAY_PARTITION variable=b cyclic factor=8 dim=1")
    pragma("HLS ARRAY_PARTITION variable=c complete dim=1")
    pragma("HLS ARRAY_PARTITION variable=acc complete")
    
    for i in range (256):
        for j in range (32):
            for k in range (256).pipeline():
                tmp = a[i][k]
                for t in range(8).unroll(8):
                    if k==0 :
                        acc[t] = c[i][j*8+t]
                    acc[t] = acc[t] + tmp * b[k][j*8 + t]
            for t in range(8).unroll():
                c[i][j*8+t] = acc[t]
            
    

if __name__ == "__main__":
    a = np.random.uniform(size=(256, 256))
    b = np.random.uniform(size=(256, 256))
    c = np.random.uniform(size=(256, 256))
    print(a.shape, b.shape, c.shape)
    target_matmul(a, b, c)
    print(c)

