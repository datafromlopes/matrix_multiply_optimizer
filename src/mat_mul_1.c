#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Use: ./program <number>\n");
        return 1;
    }

    int n = atoi(argv[1]);

    int **restrict matrix_a = malloc(n * sizeof(*matrix_a));
    int **restrict matrix_b = malloc(n * sizeof(*matrix_b));
    int **restrict matrix_c = malloc(n * sizeof(*matrix_c));

    
    for (int i = 0; i < n; i++) {
        matrix_a[i] = (int *)aligned_alloc(64, n * sizeof(*matrix_a));
        matrix_b[i] = (int *)aligned_alloc(64, n * sizeof(*matrix_b));
        matrix_c[i] = (int *)aligned_alloc(64, n * sizeof(*matrix_c));
    }
    
    srand(time(NULL));

    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            matrix_a[i][j] = rand() % 10;
            matrix_b[i][j] = rand() % 10;
        }
    }

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matrix_c[i][j] = 0;
            for (int k=0; k < n; k++){
                matrix_c[i][j] +=  matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    double seconds = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total Time: %f seconds\n", seconds);

    free(matrix_a);
    free(matrix_b);
    free(matrix_c);

    return 0;
}