#include <math.h>  
//variables to be scheduled
#define BATCH_ 16  // need to be 2^n 
//variables to be defined
#define SIZE_ 63
#define DTYPE_ int
//invariant variables
#define MAX_SIZE_ 1024


const static int BATCH = BATCH_;
const static int ITERATION = (SIZE_%BATCH_==0) ? SIZE_/BATCH_ : SIZE_/BATCH_+1;
const static int STAGE = log2(BATCH)-1; 

const static int SIZE = SIZE_;
const static int MAX_SIZE = MAX_SIZE_;


typedef DTYPE_ DTYPE;

void min(DTYPE A[SIZE] , DTYPE* min );
DTYPE min_unit(DTYPE a , DTYPE b);
