#pragma once

#include "stb_wrapper.h"
#include "matrix_math.h"

void init_means(Image *img, int k, uint8_t **means);
void kmeans(Image *img, int k, int epochs, int *indices, uint8_t **means);