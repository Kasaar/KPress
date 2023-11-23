/**
 * @file stb_wrapper.h
 * @author Owen Zeller (zelle105@umn.edu)
 * @brief Header file for stb_wrapper.c
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

enum allocation_type {
    NO_ALLOCATION, SELF_ALLOCATED, STB_ALLOCATED
};

typedef struct {
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation;
} Image;

void image_load(Image *img, const char *fname);
void image_create(Image *img, int width, int height, int channels, bool zeroed);
void image_save(const Image *img, const char *fname);
void image_free(Image *img);