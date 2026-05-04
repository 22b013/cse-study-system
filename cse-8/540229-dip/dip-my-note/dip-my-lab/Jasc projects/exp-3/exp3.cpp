#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define WIDTH 960
//#define HEIGHT 640

// Function to display images (placeholder)
void displayImage(const char* filename) {
printf("Displaying image: %s\n", filename);
// You can implement a command to display images using an external viewer if desired
}

int main() {
    int  m,n,pixel;
    int width, height;
    char buffer[50];

    srand(time(NULL));  // Seed random number generator RNG

    FILE *in_file, *out_file;
    in_file = fopen("im0.pgm", "r");
    out_file = fopen("Noisy_Image.pgm", "w");

    if (!in_file || !out_file) {
        printf("Error opening files.\n");
        return 1;
    }



     // Read magic number (e.g., "P2")
    fgets(buffer, sizeof(buffer), in_file);
    fprintf(out_file, "%s", buffer);

    // Copy comment lines if any
    do {
        fgets(buffer, sizeof(buffer), in_file);
        fprintf(out_file, "%s", buffer);
    } while (buffer[0] == '#');

    // Read width and height
    sscanf(buffer, "%d %d", &width, &height);

    // Read and copy max value (e.g., 255)
    fgets(buffer, sizeof(buffer), in_file);
    fprintf(out_file, "%s", buffer);



//Exp-3
    // Add noise and write new pixels
    for (int n = 0; n < height; n++) {
        for (int m = 0; m < width; m++) {
            fscanf(in_file, "%d", &pixel);
            int noise = (rand() % 61) - 30;
            pixel += noise;
            if (pixel < 0) pixel = 0;
            if (pixel > 255) pixel = 255;
            fprintf(out_file, "%d ", pixel);
        }
        fprintf(out_file, "\n");
    }

    fclose(in_file);
    fclose(out_file);
    displayImage("im0.pgm");
    displayImage("Noisy_Image.pgm");

    printf("\nDone! Image processed successfully!\n");
    return 0;
}
