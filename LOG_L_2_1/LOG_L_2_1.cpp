#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Size_1 100
#define Size_2 200
#define Size_3 400
#define Size_4 500
#define Size_5 600
#define Size_6 800
#define Size_7 1000

void Matrix_mult(int size);

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = { Size_1, Size_2, Size_3, Size_4, Size_5, Size_6, Size_7 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf(" +-----------+------------------+\n");
    printf(" | Size      | Time (ms)        |\n");
    printf(" +-----------+------------------+\n");

    for (int i = 0; i < num_sizes; i++) {
        Matrix_mult(sizes[i]);
    }
    return 0;
}

void Matrix_mult(int size) {
    clock_t start_mult, end_mult;
    double time_spent;
    int i, j, r;
    int elem_c;

    int** A = (int**)malloc(size * sizeof(int*));
    int** B = (int**)malloc(size * sizeof(int*));
    int** C = (int**)malloc(size * sizeof(int*));

    for (i = 0; i < size; i++) {
        A[i] = (int*)malloc(size * sizeof(int));
        B[i] = (int*)malloc(size * sizeof(int));
        C[i] = (int*)malloc(size * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % 10 + 1;
            B[i][j] = rand() % 10 + 1;
        }
    }

    start_mult = clock(); // Начало умножения матриц
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            elem_c = 0;
            for (r = 0; r < size; r++) {
                elem_c += A[i][r] * B[r][j];
            }
            C[i][j] = elem_c;
        }
    }
    end_mult = clock(); // Конец умножения матриц

    time_spent = ((double)(end_mult - start_mult)) / CLOCKS_PER_SEC;
    printf(" | %-9d | %-16.2f |\n", size, time_spent * 1000);
    printf(" +-----------+------------------+\n");

    for (i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}