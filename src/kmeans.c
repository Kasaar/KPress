#include "stb_wrapper.h"
#include "matrix_math.h"

uint8_t **init_means(Image *img, int k) {
    // The output matrix composed of k 1x3 vectors representing the k cluster centroids.
    uint8_t **means = (uint8_t **)malloc(k * sizeof(uint8_t *));
    for (int i = 0; i < k; i++) {
        means[i] = (uint8_t *)malloc(3 * sizeof(uint8_t));
    }

    // Constants for randomly initializing centroids
    const int size = img->width * img->height;
    const int num_indices = 10;
    unsigned char *p = img->data;

    // A vector to hold num_indices indices
    int *temp_indices = (int *)malloc(num_indices * sizeof(int));

    // A matrix to hold num_indices pixels to average
    uint8_t **temp_pixels = (uint8_t **)malloc(num_indices * sizeof(uint8_t *));
        for (int i = 0; i < num_indices; i++) {
            temp_pixels[i] = (uint8_t *)malloc(3 * sizeof(uint8_t));
    }

    // Iterate through k times to initialize k centroids
    for (int i = 0; i < k; i++) {
        random_indices(size, num_indices, temp_indices);

        for (int j = 0; j < num_indices; j++) {
            const int offset = temp_indices[j] * img->channels;
            temp_pixels[j][1] = (uint8_t)(*p + offset);
            temp_pixels[j][2] = (uint8_t)(*(p + 1 + offset));
            temp_pixels[j][3] = (uint8_t)(*(p + 2 + offset));
        }
        vector_avg(temp_pixels, num_indices, means[i]);
    }

    // Free the temporary arrays
    free(temp_indices);
    for (int i = 0; i < num_indices; i++) {
        free(temp_pixels[i]);
    }
    free(temp_pixels);

    return means;
}