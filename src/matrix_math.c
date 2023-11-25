#include "matrix_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Generates random numbers between 0 and max (inclusive).
 * 
 * @param max The maximum number to be generated.
 * @param num_indices The number of numbers to generate.
 * @return An array of 
 */
void random_indices(int max, const int num_indices, int *dest) {
    // Seed the RNG
    srand(time(NULL));

    int indices[num_indices];

    for (int i = 0; i < num_indices; i++) {
        indices[i] = rand() % (max + 1); // Generate a random index from 0 to max
    }
}

/**
 * @brief Computes the partwise average of multiple 1x3 vectors.
 * 
 * @param data A 2d matrix holding the input vectors.
 * @param num_vectors The number of 1x3 vectors to average.
 * @param dest A 1x3 vector to hold the averaged output vector.
 */
void vector_avg(uint8_t **data, const int num_vectors, uint8_t *dest) {
    for (int i = 0; i < 3; i++) {
        dest[i] = 0;
        for (int j = 0; j < num_vectors; j++) {
            dest[i] += data[j][i];
        }
        dest[i] /= num_vectors;
    }
}