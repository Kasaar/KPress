#pragma once

#include "stb_wrapper.h"
#include "matrix_math.h"
#include <time.h>

void init_means(Image *img, int k, uint8_t **means);
void kmeans(Image *img, int k, int epochs, int *indices, uint8_t **means);
void compress(Image *img, int *indices, uint8_t **means);
void free_means(int k, uint8_t **means);