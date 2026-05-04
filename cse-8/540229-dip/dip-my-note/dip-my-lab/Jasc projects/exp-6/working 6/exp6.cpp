#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main() {
    FILE *in_file = fopen("disp1.pgm", "r");
    FILE *out_file = fopen("equalized.pgm", "w");
    int width, height, maxval, i, pixel;
    char buffer[100];

    if (!in_file || !out_file) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read and write header
    fgets(buffer, sizeof(buffer), in_file);
    fprintf(out_file, "%s", buffer);

    do {
        fgets(buffer, sizeof(buffer), in_file);
        fprintf(out_file, "%s", buffer);
    } while (buffer[0] == '#');

    sscanf(buffer, "%d %d", &width, &height);
    fscanf(in_file, "%d", &maxval);
    fprintf(out_file, "%d\n", maxval);

    int total_pixels = width * height;
    int *image = (int*) malloc(sizeof(int) * total_pixels);
    int histogram[MAX] = {0};
    float cdf[MAX] = {0.0};
    int mapping[MAX];

    // Read pixel values and build histogram
    for (i = 0; i < total_pixels; i++) {
        fscanf(in_file, "%d", &image[i]);
        histogram[image[i]]++;
    }

    // Compute CDF
    float sum = 0;
    for (i = 0; i < MAX; i++) {
        sum += (float)histogram[i] / total_pixels;
        cdf[i] = sum;
        mapping[i] = (int)(cdf[i] * 255 + 0.5);  // Equalized value
    }

    // Write equalized image
    for (i = 0; i < total_pixels; i++) {
        int new_pixel = mapping[image[i]];
        fprintf(out_file, "%d ", new_pixel);
        if ((i + 1) % width == 0) fprintf(out_file, "\n");
    }

    fclose(in_file);
    fclose(out_file);
    free(image);

    printf("Histogram Equalization completed. Output saved as 'equalized.pgm'.\n");
    return 0;
}
