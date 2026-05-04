#include <stdio.h>
#include <stdlib.h>

int main() {
    int width=384, height=288; //width = 384, height = 288;
    int  m,n, sub, add;
    int pixel, pixel1;
    char buffer[100];

    FILE *in_file1, *in_file2, *out_file1, *out_file2;
    in_file1 = fopen("im1.pgm", "r");
    in_file2 = fopen("im0.pgm", "r");
    out_file1 = fopen("Addition_Image.pgm", "w");
    out_file2 = fopen("Subtracted_Image.pgm", "w");

    //Error message
    if (!in_file1 || !out_file1 || !in_file2 || !out_file2) {
        printf("Error opening files.\n");
        return 1;
    }

    // Skip P2 and comments from image 1
    fgets(buffer, sizeof(buffer), in_file1); // P2
    do {
        fgets(buffer, sizeof(buffer), in_file1);
    } while (buffer[0] == '#');

    // Skip P2 and comments from image 2
    fgets(buffer, sizeof(buffer), in_file2); // P2
    do {
        fgets(buffer, sizeof(buffer), in_file2);
    } while (buffer[0] == '#');

    // Write header for output image
    fprintf(out_file1, "P2\n%d %d\n255\n", width, height);
    fprintf(out_file2, "P2\n%d %d\n255\n", width, height);

//Exp-2
    for (n = 0; n < width; n++) {
        for (m = 0; m < height; m++) {
            fscanf(in_file1, "%d", &pixel);
            fscanf(in_file2, "%d", &pixel1);

            //Addition
            add = pixel + pixel1;
                if (add < 0) add = 0;
                if (add > 255) add = 255;
            fprintf(out_file1, "%d ", add);

            //Subtraction
            sub = pixel - pixel1;
                if (sub < 0) sub = 0;
                if (sub > 255) sub = 255;
            fprintf(out_file2, "%d ", sub);
        }
        fprintf(out_file1, "\n");
        fprintf(out_file2, "\n");
    }

    fclose(in_file1);
    fclose(in_file2);
    fclose(out_file1);
    fclose(out_file2);

    printf("Done! Image processed successfully!\n");
    return 0;
}


/*


#include <stdio.h>
#include <stdlib.h>

int main() {
    int width = 384, height = 288;
    int pixel, pixel1, sub;
    char buffer[100];

    FILE *in_file = fopen("i7.pgm", "r");
    FILE *in_file1 = fopen("i8.pgm", "r");
    FILE *out_file = fopen("Subtracted_Image.pgm", "w");

    if (!in_file || !in_file1 || !out_file) {
        perror("Error opening files");
        return 1;
    }

    // Skip P2 and comments from image 1
    fgets(buffer, sizeof(buffer), in_file); // P2
    do {
        fgets(buffer, sizeof(buffer), in_file);
    } while (buffer[0] == '#');

    // Skip P2 and comments from image 2
    fgets(buffer, sizeof(buffer), in_file1); // P2
    do {
        fgets(buffer, sizeof(buffer), in_file1);
    } while (buffer[0] == '#');

    // Write header for output image
    fprintf(out_file, "P2\n%d %d\n255\n", width, height);

    for (int i = 0; i < width * height; i++) {
        fscanf(in_file, "%d", &pixel);
        fscanf(in_file1, "%d", &pixel1);
        sub = pixel + pixel1;

        if (sub < 0) sub = 0;
        else if (sub > 255) sub = 255;

        fprintf(out_file, "%d ", sub);

        // Optional: add a newline every 'width' pixels for readability
        if ((i + 1) % width == 0)
            fprintf(out_file, "\n");
    }

    fclose(in_file);
    fclose(in_file1);
    fclose(out_file);

    printf("Done! Image processed successfully!\n");
    return 0;
}

*/

