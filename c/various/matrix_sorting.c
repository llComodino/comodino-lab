#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 50
#define COLS 100

void populate (int matrix[][COLS]);
void print (int matrix[][COLS]);
void sort (int matrix[][COLS]);

int main (void) {

    int matrix[ROWS][COLS];

    populate(matrix);
    print(matrix);

    sort(matrix);

    print(matrix);

    return EXIT_SUCCESS;
}

void populate (int matrix[][COLS]) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            matrix[i][j] = 1 + rand() % 10;
        }
    }
    return;
}

void print (int matrix[][COLS]) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            printf("%2i", matrix[i][j]);
        }
        puts("");
    }
    puts("\n");
    return;
}

void sort (int matrix[][COLS]) {
    bool swap;

    do {
        swap = false;
        for (size_t i = 0; i < ROWS; i++) {
            for (size_t j = 0; i == ROWS - 1 ? j < COLS - 1 : j < COLS; j++) {

                int *current = &matrix[i][j];
                int *next = (j == COLS - 1 && i < ROWS - 2) ? &matrix[i+1][0] : &matrix[i][j + 1];

                if (*current > *next) {
                    swap = true;
                    int tmp;
                    tmp = *next;
                    *next = *current;
                    *current = tmp;
                }
            }
        }
    } while (swap == true);

    return;
}
