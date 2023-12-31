#ifndef __SPMV_H__
#define __SPMV_H__

#define NNZ_ 9  
//variables to be defined
#define SIZE_ 4
#define NUM_ROWS_ 4
#define DTYPE_ float
//invariant variables
//#define MAX_SIZE_ 1024

const static int SIZE = SIZE_; // SIZE of square matrix
const static int NNZ = NNZ_; //Number of non-zero elements
const static int NUM_ROWS = NUM_ROWS_;// SIZE;
typedef DTYPE_ DTYPE;


void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
		  DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE]);

#endif // __MATRIXMUL_H__ not defined



