import numpy as np
from pylog import *

@pylog(mode='debug')
def pl_dot_map_matmul(a, b, c):
    tmp = a[:,0]*b[:,0];
    c = plmap(lambda x, y: dot( x[0,0:15], y[0:15,0]), a, b)


if __name__ == "__main__":
    length = 16
    a = np.random.rand(length, length)
    b = np.random.rand(length, length)
    c = np.random.rand(length, length)
    pl_dot_map_matmul(a, b, c)