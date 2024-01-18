#pragma once

#include <stdio.h>
#include <stdlib.h>

void vector_avg(uint8_t **data, int num_vectors, uint8_t *dest);
int distance(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2);