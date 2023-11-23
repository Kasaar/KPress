/**
 * @file stb_wrapper.c
 * @author Owen Zeller (zelle105@umn.edu)
 * @brief A wrapper for the stb_image library. A useful abstraction for reading and writing images.
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stb_wrapper.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

/**
 * @brief A wrapper for loading an image using the stb_image library. Requires an Image
 * struct already containing information about the image.
 * 
 * @param img A pointer to the Image struct that will store the image information.
 * @param fname The name of the image file as a string.
 */
void image_load(Image *img, const char *fname) {
    img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0);
    ON_ERROR_EXIT((img->data == NULL), "Image data is NULL.");
    img->size = img->width * img->height * img->channels;
    img->allocation = STB_ALLOCATED;
}

/**
 * @brief Builds a new Image struct for a desired image size and allocates memory for its data.
 * 
 * @param img A pointer to the Image struct that will store the image information.
 * @param width The width of the desired image.
 * @param height The height of the desired image.
 * @param channels The number of channels of the desired image.
 * @param zeroed Whether the allocated memory should be zeroed.
 */
void image_create(Image *img, int width, int height, int channels, bool zeroed) {
    size_t size = width * height * channels;
    if(zeroed) {
        img->data = calloc(size, 1);
    } else {
        img->data = malloc(size);
    }

    ON_ERROR_EXIT((img->data == NULL), "Memory allocation failed.");

    img->width = width;
    img->height = height;
    img->size = size;
    img->channels = channels;
    img->allocation = SELF_ALLOCATED;
}

/**
 * @brief A wrapper for writing an image using the stb_image library. Checks for proper filetype.
 * 
 * @param img A pointer to the Image struct containing the image information.
 * @param fname The name of the image file as a string.
 */
void image_save(const Image *img, const char *fname) {
    if (str_ends_in(fname, ".jpg") || str_ends_in(fname, ".JPG") || str_ends_in(fname, ".jpeg") || str_ends_in(fname, ".JPEG")) {
        stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
    } else if (str_ends_in(fname, ".png") || str_ends_in(fname, ".PNG")) {
        stbi_write_png(fname, img->width, img->height, img->channels, img->data, img->width * img->channels);
    } else {
        ON_ERROR_EXIT(true, "Wrong filetype. Please write to a .jpg, .jpeg, or .png.");
    }
}

/**
 * @brief Frees the memory of an Image struct's data and resets all of its fields.
 * 
 * @param img The Image struct to be reset.
 */
void image_free(Image *img) {
    if (img->allocation != NO_ALLOCATION && img->data != NULL) {
        if (img->allocation == STB_ALLOCATED) {
            stbi_image_free(img->data);
        } else {
            free(img->data);
        }

        img->data = NULL;
        img->width = 0;
        img->height = 0;
        img->size = 0;
        img->allocation = NO_ALLOCATION;
    }
}