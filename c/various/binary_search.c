#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ELEMENTS 100

/* Function: populate
 * Populate the vector with random numbers
 * @param vector: vector to be populated
 * @return: void
 */
void populate (int *vector);

/* Function: sort
 * Sort the vector using bubble sort
 * @param vector: vector to be sorted
 * @return: void
 */
void sort (int *vector);

/* Function: print
 * Print the vector
 * @param vector: vector to be printed
 * @return: void
 */
void print (int *vector);

/* Function: bin_search
 * Execute the binary search
 * @param vector: vector to be searched
 * @return: void
 */
int bin_search (int *vector, int key);

int main (void) {
    
    // Declare the vector
    int *vector;

    // Allocate memory for the vector
    vector = (int *) malloc(ELEMENTS * sizeof(int));

    // Populate the vector
    // With random numbers
    populate(vector);

    // sort the vector
    // Using bubble sort
    sort(vector);

    // Print the vector
    print(vector);

    // Execute the binary search
    int key;
    scanf("%d", &key);
    printf("\nPosition: %d\n", bin_search(vector, key));

    return 0;
}

void populate (int *vector) {

    // Declare the local function
    bool check_unique (int *vector, int number);

    // Seed the random number generator
    srand(time(NULL));

    // Populate the vector with unique elements
    for (int i = 0; i < ELEMENTS; i++) {
        do {
            *(vector + i) = rand() % 1000;
        } while (check_unique(vector, *(vector + i)));
    }

    return;
}

/* Function: check_unique
 * Check if the number is unique in the vector
 * @param vector: vector to be checked
 * @param number: number to be checked
 * @return: true if the number is unique, false otherwise
 */
bool check_unique (int *vector, int number) {

    for (int i = 0; i < ELEMENTS; i++) {
        if (*(vector + i) == number) {
            return false;
        }
    }
    return true;
}

void sort (int *vector) {
    
    // Sort the vector
    for (int i = 0; i < ELEMENTS; i++) {
        for (int j = 0; j < ELEMENTS - 1; j++) {
            if (*(vector + j) > *(vector +j + 1)) {
                int aux = *(vector + j);
                *(vector + j) = *(vector + j + 1);
                *(vector +j + 1) = aux;
            }
        }
    }
    return;
}

void print (int *vector) {
 
    // Print the vector
    for (int i = 0; i < ELEMENTS; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
    return;
}

int bin_search (int *vector, int key) {

    int start = 0, end = ELEMENTS - 1, middle;

    while (start < end) {
        middle = (start + end) / 2;
        if (key == *(vector + middle)) {
            return middle;
        } else if (key < *(vector + middle)) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}
