import sys
sys.path.extend(['/home/shuang91/pylog/'])

import numpy as np
from pylog import *

'''
The inputs to the PyLog function should be simply regular NumPy arrays. 
PyLog should be able to get the element data type and array dimensions 
from the input NumPy arrays. 
'''

@pylog
def pl_add(a, b):
    return a + b


if __name__ == "__main__":
    a = np.array([1, 3, 6, 7, 10])
    b = np.array([1, 3, 6, 7, 10])
    c = pl_add(a, b)
    print(c)