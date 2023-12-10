import numpy as np
# from pysim import *
from pylog import *

@pylog(mode='cgen')#(mode='pysim')
def new_matmul(a, b, c):
    c = matmul(a, b)

if __name__ == "__main__":
    a = np.random.uniform(size=(256, 256))
    b = np.random.uniform(size=(256, 256))
    c = np.random.uniform(size=(256, 256))
    new_matmul(a, b, c)
    print(c)
