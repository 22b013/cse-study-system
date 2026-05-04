#include <stdio.h>
#include <stdlib.h>

#define MAX_GRAY 256

int main() {
    FILE *in_file, *out_file;
	int i;
    char buffer[100];
    int width, height, maxval;
    int histogram[MAX_GRAY] = {0};
    int cdf[MAX_GRAY] = {0};
    int equalized[MAX_GRAY];
    int pixel, total_pixels;

    // Open input and output files
    in_file = fopen("disp1.pgm", "r");
    out_file = fopen("Equalized.pgm", "w");

    if (!in_file || !out_file) {
        printf("Error: Cannot open input or output file.\n");
        return 1;
    }

    // Read header
    fgets(buffer, sizeof(buffer), in_file); // Magic number (P2)

    // Skip comments
    do {
        fgets(buffer, sizeof(buffer), in_file);
    } while (buffer[0] == '#');

    // Read image dimensions
    sscanf(buffer, "%d %d", &width, &height);
    total_pixels = width * height;

    // Read max gray value
    fscanf(in_file, "%d", &maxval);

    // Read pixel data and build histogram
    int *image_data = (int *)malloc(total_pixels * sizeof(int));
    for (i = 0; i < total_pixels; i++) {
        fscanf(in_file, "%d", &pixel);
        image_data[i] = pixel;
        histogram[pixel]++;
    }

    // Compute cumulative histogram (CDF)
    cdf[0] = histogram[0];
        for (i = 1; i < MAX_GRAY; i++) {
            cdf[i] = cdf[i - 1] + histogram[i];
    }

    // Find CDF minimum (excluding zeros)
    int cdf_min = 0;
    for ( i = 0; i < MAX_GRAY; i++) {
        if (cdf[i] != 0) {
            cdf_min = cdf[i];
            break;
        }
    }

    // Compute equalized values
    for ( i = 0; i < MAX_GRAY; i++) {
        equalized[i] = (int)(((double)(cdf[i] - cdf_min) / (total_pixels - cdf_min)) * (MAX_GRAY - 1) + 0.5);
    }

    // Write header to output
    fprintf(out_file, "P2\n%d %d\n255\n", width, height);

    // Write transformed pixel values
    for ( i = 0; i < total_pixels; i++) {
        fprintf(out_file, "%d ", equalized[image_data[i]]);
        if ((i + 1) % width == 0) fprintf(out_file, "\n");
    }

    // Clean up
    free(image_data);
    fclose(in_file);
    fclose(out_file);

    printf("Histogram Equalization completed successfully.\n");
    return 0;
}
