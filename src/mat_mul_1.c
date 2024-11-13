#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
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

    matrix_a = aligned_alloc(8, n * n * sizeof(*matrix_a));
    matrix_b = aligned_alloc(8, n * n * sizeof(*matrix_b));
    matrix_c = aligned_alloc(8, n * n * sizeof(*matrix_c));

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
    int i, j, k;

    clock_t start = clock();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C(i, j) +=  A(i, k)*B(k, j);
            }
        }
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Total Time: %.5f seconds\n", time_taken);

    #undef A
    #undef B
    #undef C

    free(matrix_a);
    free(matrix_b);
    free(matrix_b);

    return 0;
}