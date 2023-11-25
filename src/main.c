#include "stb_wrapper.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc > 4 || argc < 2) {
        printf("Usage: %s <image_path> <clusters> <epochs>\n", argv[0]);
        return 1;
    }
    
    int k;
    int epochs;
    const char* image_path = argv[1];

    if (argc == 2) {
        k = 64;
        epochs = 10;
    } else if (argc == 3) {
        k = atoi(argv[2]);
        epochs = 10;
    } else if (argc == 4) {
        k = atoi(argv[2]);
        epochs = atoi(argv[3]);
    }

    Image img;
    image_load(&img, image_path);
    image_free(&img);

    return 0;
}