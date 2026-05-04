#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 960

int main() {
    int pixel;
    char buffer[50];
    int thresholdValue = 128; // Set the threshold value (you can change this)
    FILE *in_file, *out_file;

    // Open the input and output files
    in_file = fopen("i11.pgm", "r");
    if (in_file == NULL) {
        fprintf(stderr, "Error: Could not open input file.\n");
        return 1;
    }

    out_file = fopen("Binary_image.pgm", "w");
    if (out_file == NULL) {
        fprintf(stderr, "Error: Could not open output file.\n");
        fclose(in_file);
        return 1;
    }

    // Read the header of the PGM file
    fgets(buffer, 50, in_file); // Read the PGM format
    do {
        fgets(buffer, 50, in_file); // Skip comments
    } while (buffer[0] == '#');

    // Write header for the binary image with fixed dimensions
    fprintf(out_file, "P2\n%d %d\n255\n", WIDTH, HEIGHT);

    // Read pixel values, apply thresholding, and write to output
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            fscanf(in_file, "%d", &pixel);
            // Apply thresholding
            if (pixel > thresholdValue) {
                fprintf(out_file, "255 ");
            } else {
                fprintf(out_file, "0 ");
            }
        }
        fprintf(out_file, "\n"); // New line after each row
    }

    // Close the files
    fclose(in_file);
    fclose(out_file);

    printf("Thresholding completed. Output saved to Binary_image.pgm\n");
    return 0;
}
