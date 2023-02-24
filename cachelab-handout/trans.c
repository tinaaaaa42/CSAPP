/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	if (M == 32) {         // blocking of 8*8
		for (int i = 0; i < M; i += 8) {
			for (int j = 0; j < N; j += 8) {
				for (int k = 0; k < 8; k++) {
					int t0 = A[i+k][j];
					int t1 = A[i+k][j+1];
					int t2 = A[i+k][j+2];
					int t3 = A[i+k][j+3];
					int t4 = A[i+k][j+4];
					int t5 = A[i+k][j+5];
					int t6 = A[i+k][j+6];
					int t7 = A[i+k][j+7];

					B[j][i+k] = t0;
					B[j+1][i+k] = t1;
					B[j+2][i+k] = t2;
					B[j+3][i+k] = t3;
  					B[j+4][i+k] = t4;
					B[j+5][i+k] = t5;
					B[j+6][i+k] = t6;
					B[j+7][i+k] = t7;
				}
			}
		}
	}
	
	if (M == 64) {
		for (int i = 0; i < M; i += 8) {
			for (int j = 0; j < N; j += 8) {
				/* The logic for 8*8 blocks in 64*64 matrix:
				 * Transpose the left-top and right-bottom 4*4 blocks as above.
				 * To deal with the right-top and left-bottom ones, use r-t one as a middleman.
				 * That is, first copy the corresponding block from A into r-t, then pass them to l-b.
				 * */


				// left-top and copy the transposed one to right-top
				for (int k = 0; k < 4; k++) {
					int t0 = A[i+k][j];
					int t1 = A[i+k][j+1];
					int t2 = A[i+k][j+2];
					int t3 = A[i+k][j+3];
					int t4 = A[i+k][j+4];
					int t5 = A[i+k][j+5];
					int t6 = A[i+k][j+6];
					int t7 = A[i+k][j+7];

					B[j][i+k] = t0;
					B[j+1][i+k] = t1;
					B[j+2][i+k] = t2;
					B[j+3][i+k] = t3;
					
					B[j][i+k+4] = t4;
					B[j+1][i+k+4] = t5;
					B[j+2][i+k+4] = t6;
					B[j+3][i+k+4] = t7;

				}

				// left-bottom and right-top ones of B
				for (int k = 0; k < 4; k++) {
					int x = i + 4;
	                int y = j;
    	            int t0=A[x][y+k];
        	        int t1=A[x+1][y+k];
            	    int t2=A[x+2][y+k];
            		int t3=A[x+3][y+k];

            	    x = j;
            	    y = i + 4;
            	    int t4=B[x+k][y];
            	    int t5=B[x+k][y+1];
            	    int t6=B[x+k][y+2];
            	    int t7=B[x+k][y+3];


            	    x = i + 4;
            	    y = j;
            	    B[y+k][x]=t0;
					B[y+k][x+1]=t1;
            	    B[y+k][x+2]=t2;
            	    B[y+k][x+3]=t3;

            	    x = j;
            	    y = i + 4;
            	    B[x+k+4][y-4]=t4;
            	    B[x+k+4][y-3]=t5;
        		    B[x+k+4][y-2]=t6;
            	    B[x+k+4][y-1]=t7;
				}

				// right-bottom one of B
				for (int k = 0; k < 4; k++) {
					int t0 = A[i+4+k][j+4];
					int t1 = A[i+4+k][j+5];
					int t2 = A[i+4+k][j+6];
					int t3 = A[i+4+k][j+7];

					B[j+4][i+4+k] = t0;
					B[j+5][i+4+k] = t1;
					B[j+6][i+4+k] = t2;
					B[j+7][i+4+k] = t3;
				}
			}
		}
	}

	if(M==61)
	{
	    for(int i=0;i<67;i+=32)
	    {
    	    for(int j=0;j<61;j+=8)
    	    {
        	    for(int k=0;k<32;k++)
        	    {
            	    for(int l=0;l<8;l++)
            	    {
                	    if(j+l>=61||i+k>=67)
                    	    continue;
                	    B[j+l][i+k]=A[i+k][j+l];
                }
            }
        }
    }
}

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

