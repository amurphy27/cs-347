
/*
 Name: Andrew Murphy
 =====

 Write a program to multiply two matrices using pthreads.
 Matrix Multiplication: Matrix C of size (x by z)  =  Matrix A of size (x by y) times Matrix B of size (y by z).

 * Example: Matrix A of size 2 rows by 3 columns, Matrix B of size 3 by 2
              A = 1     1     5
                  2     4     2
              B = 0     2
                  5     1
                  0     5
 Then C = A * B = 5     28
                  20    18

 *It will generate random values for the elements of matrix A of size x by y and matrix B of size y by z. These values range from 0 to 20000.
 *It will compute matrix C that is the result of multiplying matrix A by matrix B by using pthreads.
 *It will print the original matrices and the result matrix and show elapsed time.
 */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <ctype.h>

/* Matrices dimensions */
#define  Dim_X  2
#define  Dim_Y  3
#define  Dim_Z  2

pthread_barrier_t barrier; //to sync

struct mm_thread_data {
  int start;
  int work;
  double *A;
  double *B;
  double *C;
};

/*
The thread_fn function shall compute the data, i.e., dot product rows and columns. The computed data shall be stored in matrix C. Matrices A and B are not to be modified
 */
void * thread_fn ( void *arg )
{
	struct mm_thread_data *args = (struct mm_thread_data*) arg;
	for (int i = args->start; i < args->start + args->work; i++){
		int C_row = i / Dim_X;
		int C_col = i % Dim_X;
		int result = 0;
		for (int j = 0; j < Dim_X; j++){
			result += args->A[C_row] * args->B[C_col];
			C_row++;
			C_col += Dim_X;
		}
		args->C[i] = result;
	}
	pthread_barrier_wait(&barrier);
	return NULL;
}

/* Create Num_of_Threads threads to multiply the matrices A and B.
 Compute start and size of work done by the thread. Each thread shall process equal (or almost equal) part  of the matrix multiplication.
 */
void multiply_matrices (double *A, double *B, double *C, int Num_of_Threads)
{
	struct timeval start_time;
	gettimeofday(&start_time, NULL);
	pthread_t threads[Num_of_Threads];
	pthread_barrier_init(&barrier, NULL, Num_of_Threads);
	for (int i = 0; i < Num_of_Threads; i++){
		int start = (Dim_X/Num_of_Threads) * Dim_X * i;
		int work = Dim_X / Num_of_Threads * Dim_X;
		if (i == Num_of_Threads - 1){
			work = (Dim_X * Dim_X)-start;
		}
		struct mm_thread_data arg = {start, work, A, B, C};
		pthread_create(&threads[i], NULL, thread_fn, (void *) &arg);
	}
	for (int i = 0; i < Num_of_Threads; i++){
		pthread_join(threads[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	double elapsedTime = (((double) end_time.tv_usec) - ((double) start_time.tv_usec));
	printf("Elapsed Time was: %f\n", elapsedTime);
}

/* Print a matrix of size x by y in the following format: Row i: one row per line with a tab space between each number. (Example output of printing a matrix of size 2 by 2)
 Row 0:           1          1
 Row 1:           5          2
 */
void print_matrix (double *A, int x, int y)
{
	for (int i = 0; i < x; i++){
		printf("Row %i:", i);
		for (int j = 0; j < y; j++){
			printf("\t%i", (int) *A);
			A++;
		}
		printf("\n");
	}
}


/* Generate random data for a matrix of size x rows by y columns
 You can use the rand function to grnerate numbers in the range of 0 to 20000.
 */
void generate_matrix (double *A, int x, int y)
{
	for (int i = 0; i < (x*y); i++){
		A[i] = (rand() % (20000 - 0 + 1));
	}
}

/*The driver of the program.
 * Generate matrix A and matrix B using generate_matrix.
 * Multiply matrix A by matrix B using multiply_matrices.
 * Print matrix A, matrix B, and matrix C using print_matrix.
 * Print the elapsed time in .3 precision.
 */
int main (int argc, char * argv[])
{
	int num_threads = sysconf(_SC_NPROCESSORS_CONF);
	if (argc > 2){
		printf("Usage:\n./final [n]\n");
		return -1;
	}
	else if (argc == 2){
		num_threads = atoi(argv[1]);
		if (num_threads == 0){
			printf("Invalid number of strings\n");
			return -1;
		}
	}
	printf("%i Processors\n", num_threads);
	double A[(Dim_X * Dim_Y)];
	double B[(Dim_Y * Dim_X)];
	double C[(Dim_X * Dim_X)];
	srand(time(0));
	generate_matrix(A, Dim_X, Dim_Y);
	generate_matrix(B, Dim_Y, Dim_X);
	printf ("-------------- orignal A matrix ------------------\n");
	print_matrix(A, Dim_X, Dim_Y);
	printf ("-------------- orignal B matrix ------------------\n");
	print_matrix(B, Dim_Y, Dim_X);
	multiply_matrices(A, B, C, num_threads);
	printf ("--------------  result C matrix ------------------\n");
	print_matrix(C, Dim_X, Dim_X);
	return 0;
}
