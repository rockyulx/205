#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cblas.h>

#define MATRIX_SIZE 2048

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
}

void matrix_multiply(double *A, double *B, double *C) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
        MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, 1.0, A,
        MATRIX_SIZE, B, MATRIX_SIZE, 0.0, C, MATRIX_SIZE);
}

int main() {
    double *A, *B, *C;
    double start_time, end_time;
    int i, j;

    A = (double*) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
    B = (double*) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
    C = (double*) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            A[i * MATRIX_SIZE + j] = (double) rand() / RAND_MAX;
            B[i * MATRIX_SIZE + j] = (double) rand() / RAND_MAX;
        }
    }

    start_time = get_time();
    matrix_multiply(A, B, C);
    end_time = get_time();

    printf("Time taken for matrix multiplication: %f seconds\n",
        end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
