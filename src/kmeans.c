#include "stb_wrapper.h"
#include "matrix_math.h"
#include <math.h>
#include <time.h>

/**
 * @brief Initialize the k-means algorithm by randomly initializing the centroids.
 * @param img A pointer to an Image struct.
 * @param k The number of means to initialize.
 * @param means An allocated 2d matrix to hold the means.
 */
void init_means(Image *img, int k, uint8_t **means) {
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
    // Seed the RNG
    srand(time(NULL));
    // Iterate through k times to initialize k centroids
    for (int i = 0; i < k; i++) {
        for (int c = 0; c < num_indices; c++) {
            temp_indices[c] = rand() % (size + 1); // Generate a random index from 0 to max
        }

        for (int j = 0; j < num_indices; j++) {
            const int offset = temp_indices[j] * img->channels;
            temp_pixels[j][0] = (uint8_t)(*(p + offset));
            temp_pixels[j][1] = (uint8_t)(*(p + 1 + offset));
            temp_pixels[j][2] = (uint8_t)(*(p + 2 + offset));
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

/**
 * @brief The k-means algorithm. For each epoch, assigns each pixel to the closest cluster,
 * then updates the clusters by averaging the pixels that belong to each.
 * 
 * @param img A pointer to an Image struct.
 * @param k The number of clusters.
 * @param epochs The number of times to update the clusters.
 * @param indices A matrix to hold to which cluster each pixel belongs.
 * @param means An allocated 2d matrix to hold the means.
 */
void kmeans(Image *img, int k, int epochs, int *indices, uint8_t **means) {
    const int size = img->width * img->height;

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

            const int offset = i * img->channels;
            x1 = (uint8_t)(*(p + offset));
            y1 = (uint8_t)(*(p + 1 + offset));
            z1 = (uint8_t)(*(p + 2 + offset));

            // Update the distance between cluster and sample
            for (int j = 0; j < k; j++) {
                x2 = means[j][0];
                y2 = means[j][1];
                z2 = means[j][2];

                int dist = distance(x1, y1, z1, x2, y2, z2);

                if (dist <= min_dist) {
                    min_dist = dist;
                    temp = j;
                    indices[i] = j;
                }
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
                    cluster_pixels[counter][0] = (uint8_t)(*(p + offset));
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
        epochs--;
    }
}

/**
 * @brief Given the clusters and information about to which cluster
 * each pixel belongs, update the original image by reassigning
 * each piel in the image to its cluster value.
 * 
 * @param img A pointer to an Image struct.
 * @param indices A matrix to hold to which cluster each pixel belongs.
 * @param means An allocated 2d matrix to hold the means.
 */
void compress(Image *img, int *indices, uint8_t **means) {
    const int size = img->width * img->height;
    unsigned char *p = img->data;

    for (int i = 0; i < size; i++) {
        const int offset = i * img->channels;
        *(p + offset) = means[indices[i]][0];
        *(p + 1 + offset) = means[indices[i]][1];
        *(p + 2 + offset) = means[indices[i]][2];
    }
}

/**
 * @brief Free a 2d matrix with k elements.
 * 
 * @param k The number of elements contained by the outer matrix.
 * @param means The 2d matrix to free.
 */
void free_means(int k, uint8_t **means) {
    for (int i = 0; i < k; i++) {
        free(means[i]);
    }
    free(means);
}