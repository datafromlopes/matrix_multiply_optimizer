#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Use: ./program <number>\n");
        return 1;
    }

    int *restrict matrix_a;
    int *restrict matrix_b;
    int *restrict matrix_c;

    int n = atoi(argv[1]);

    matrix_a = malloc(n * n * sizeof(*matrix_a));
    matrix_b = malloc(n * n * sizeof(*matrix_b));
    matrix_c = malloc(n * n * sizeof(*matrix_c));

    srand(time(NULL));

    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            matrix_a[i * n + j] = rand() % 10;
            matrix_b[i * n + j] = rand() % 10;
        }
    }

    #define A(i, j) matrix_a[n*(i) + (j)]
    #define B(i, j) matrix_b[n*(i) + (j)]
    #define C(i, j) matrix_c[n*(i) + (j)]

    struct timeval start, end;

    int blockSize = 128;

    gettimeofday(&start, NULL);

    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < n; kk += blockSize) {
                
                for (int i = ii; i < ((ii + blockSize) < n ? (ii + blockSize) : n); i++) {
                    for (int k = kk; k < ((kk + blockSize) < n ? (kk + blockSize) : n); k++) {
                        for (int j = jj; j < ((jj + blockSize) < n ? (jj + blockSize) : n); j++) {
                            C(i, j) += A(i, k) * B(k, j);
                        }
                    }
                }
            }
        }
    }

    gettimeofday(&end, NULL);
    double seconds = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total Time: %f seconds\n", seconds);

    #undef A
    #undef B
    #undef C

    free(matrix_a);
    free(matrix_b);
    free(matrix_c);

    return 0;
}