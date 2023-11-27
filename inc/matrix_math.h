#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_indices(int max, int num_indices, int *dest);
void vector_avg(uint8_t **data, int num_vectors, uint8_t *dest);
int distance(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2);