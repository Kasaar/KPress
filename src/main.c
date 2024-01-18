#include "stb_wrapper.h"
#include "kmeans.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 5 || argc < 3) {
        printf("Usage: %s <image_path> <save_name> <clusters> <epochs>\n", argv[0]);
        return 1;
    }
    
    int k;
    int epochs;
    char* image_path = argv[1];
    char* save_name = argv[2];

    if (argc == 3) {
        k = 64;
        epochs = 10;
    } else if (argc == 4) {
        k = atoi(argv[3]);
        epochs = 10;
    } else if (argc == 5) {
        k = atoi(argv[3]);
        epochs = atoi(argv[4]);
    }

    // Load image
    Image img;
    image_load(&img, image_path);

    // Allocate memory for means array
    uint8_t **means;
    means = (uint8_t **)malloc(k * sizeof(uint8_t *));
    for (int i = 0; i < k; i++) {
        means[i] = (uint8_t *)malloc(3 * sizeof(uint8_t));
    }

    // Allocate memory for indices array
    int *indices;
    const int size = (&img)->width * (&img)->height;
    indices = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        indices[i] = 0;
    }

    // Run the algorithm
    init_means(&img, k, means);
    kmeans(&img, k, epochs, indices, means);
    compress(&img, indices, means);

    // Save the image
    strcat(save_name, ".jpg");
    image_save(&img, save_name);

    // Free memory
    free_means(k, means);
    free(indices);
    image_free(&img);

    return 0;
}