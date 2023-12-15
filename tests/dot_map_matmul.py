import numpy as np
from pylog import *

@pylog(mode='cgen')
def pl_dot_map_matmul(a, b, c):
    for i in range(256).pipeline():
        for j in range(256).unroll():
            c[i,j] = dot( a[i,:], b[:,j])


if __name__ == "__main__":
    length = 256
    a = np.random.rand(length, length)
    b = np.random.rand(length, length)
    c = np.random.rand(length, length)
    pl_dot_map_matmul(a, b, c)