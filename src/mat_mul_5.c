#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define ALIGNED_SIZE 8
#define BLOCK_SIZE 32

void matrix_multiply_recursive(int *A, int *B, int *C, int n) {
    if (n <= BLOCK_SIZE) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    } else {
        int n2 = n / 2;
        matrix_multiply_recursive(A, B, C, n2);
        matrix_multiply_recursive(A + n2 * n, B + n2 * n, C + n2 * n, n2);
        matrix_multiply_recursive(A, B + n2 * n, C + n2, n2);
        matrix_multiply_recursive(A + n2 * n, B, C, n2);

        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n; j++) {
                C[i * n + j + n2] += C[i * n + j];
                C[i * n + j] += C[(i + n2) * n + j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Use: ./program <number>\n");
        return 1;
    }

    int n = atoi(argv[1]);

    int *matrix_a = (int*)aligned_alloc(ALIGNED_SIZE, n * n * sizeof(int));
    int *matrix_b = (int*)aligned_alloc(ALIGNED_SIZE, n * n * sizeof(int));
    int *matrix_c = (int*)aligned_alloc(ALIGNED_SIZE, n * n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix_a[i * n + j] = rand() % 10;
            matrix_b[i * n + j] = rand() % 10;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    matrix_multiply_recursive(matrix_a, matrix_b, matrix_c, n);

    gettimeofday(&end, NULL);
    double seconds = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Total Time: %f seconds\n", seconds);

    free(matrix_a);
    free(matrix_b);
    free(matrix_c);

    return 0;
}