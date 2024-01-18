#include "matrix_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Computes the partwise average of multiple 1x3 vectors.
 * 
 * @param data A 2d matrix holding the input vectors.
 * @param num_vectors The number of 1x3 vectors to average.
 * @param dest A 1x3 vector to hold the averaged output vector.
 */
void vector_avg(uint8_t **data, const int num_vectors, uint8_t *dest) {
    for (int i = 0; i < 3; i++) {
        int acc = 0;
        for (int j = 0; j < num_vectors; j++) {
            acc += data[j][i];
        }
        dest[i] = (uint8_t)(acc / num_vectors);
    }
}

int distance(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2) {
    int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
    return sqrt(dist);
}