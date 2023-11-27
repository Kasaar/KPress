#include "stb_wrapper.h"
#include "matrix_math.h"
#include <math.h>

void init_means(Image *img, int k, uint8_t **means) {
    // The output matrix composed of k 1x3 vectors representing the k cluster centroids.
    means = (uint8_t **)malloc(k * sizeof(uint8_t *));
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
}

void free_means(int k, uint8_t **means) {
    for (int i = 0; i < k; i++) {
        free(means[i]);
    }
    free(means);
}

void kmeans(Image *img, int k, int epochs, int *indices, uint8_t **means) {
    const int size = img->width * img->height;

    // Index values that correspond to the clusters
    // to which each pixel belongs.
    indices = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        indices[i] = 0;
    }

    // Temp variables to store pixels
    uint8_t x1;
    uint8_t y1;
    uint8_t z1;
    uint8_t x2;
    uint8_t y2;
    uint8_t z2;

    unsigned char *p = img->data;

    while (epochs > 0) {
        for (int i = 0; i < size; i++) {
            // Init min_dist to large value
            int min_dist = INFINITY;
            int temp;

            // Update the distance between cluster and sample
            for (int j = 0; j < k; j++) {
                const int offset = i * img->channels;
                x1 = (uint8_t)(*p + offset);
                y1 = (uint8_t)(*(p + 1 + offset));
                z1 = (uint8_t)(*(p + 2 + offset));
                x2 = means[k][0];
                y2 = means[k][1];
                z2 = means[k][2];

                int dist = distance(x1, y1, z1, x2, y2, z2);

                if (dist <= min_dist) {
                    min_dist = dist;
                    temp = j;
                    indices[i] = j;
                }
            }
            for (int j = 0; j < k; j++) {
                // Compute the number of pixels belonging to cluster k
                int pixels_in_k = 0;
                for (int c = 0; c < size; c++) {
                    if (indices[c] == k) {
                        pixels_in_k += 1;
                    }
                }
                // Store the pixels belonging to cluster k
                uint8_t **cluster_pixels = (uint8_t **)malloc(pixels_in_k * sizeof(uint8_t *));
                for (int i = 0; i < pixels_in_k; i++) {
                    cluster_pixels[i] = (uint8_t *)malloc(3 * sizeof(uint8_t));
                }
                int counter = 0;
                for (int c = 0; c < size; c++) {
                    if (indices[c] == k) {
                        const int offset = c * img->channels;
                        cluster_pixels[counter][0] = (uint8_t)(*p + offset);
                        cluster_pixels[counter][1] = (uint8_t)(*(p + 1 + offset));
                        cluster_pixels[counter][2] = (uint8_t)(*(p + 2 + offset));
                        counter++;
                    }
                }
                // Average the pixels belonging to cluster k
                if (pixels_in_k > 0) {
                    vector_avg(cluster_pixels, pixels_in_k, means[j]);
                }
                // Free temp cluster pixels
                for (int c = 0; c < pixels_in_k; c++) {
                    free(cluster_pixels[c]);
                }
                free(cluster_pixels);
            }
            i--;
        }
    }
}

void compress(Image *img, int *indices, uint8_t **means) {
    
}