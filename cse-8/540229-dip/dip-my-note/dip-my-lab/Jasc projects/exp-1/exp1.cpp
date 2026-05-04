#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // For exit()

int main() {
    int  m,n,pixel;
	int width, height;
	char buffer[50];

    FILE *in_file, *out_file;
    in_file = fopen("exp1.pgm", "r");
    out_file = fopen("out1.pgm", "w");

    //Error message
    if (!in_file || !out_file) {
        printf("Error opening files.\n");
        return 1;
    }

    //Read & write header
    fgets(buffer, sizeof(buffer), in_file); // P2
    fputs(buffer, out_file);
    do {
        fgets(buffer, sizeof(buffer), in_file);
    } while (buffer[0] == '#');

    // Read width and height
    sscanf(buffer, "%d %d", &width, &height);
    fgets(buffer, sizeof(buffer), in_file);
    // Write header to output file
    fprintf(out_file,"%d %d\n255\n",width, height);

//Exp-1
    // Process and write pixel data
    // Loop through image pixels
    for (n = 0; n < width; n++) {           // NOTE: outer loop is rows
        for (m = 0; m < height; m++) {       // inner loop is columns
            fscanf(in_file, "%d", &pixel);
                if (pixel < 0) pixel = 0;
                if (pixel > 255) pixel = 255;
            fprintf(out_file,"%d ", pixel); //grayscale image | 255=white | 0=black
        }
        fprintf(out_file, "\n"); // Newline for each row (good practice for PGM)
    }

    fclose(in_file);
    fclose(out_file);

    printf("Done! Image processed successfully.\n");
    return 0;
}



/*

#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // For exit()

int main() {
    int  m,n,pixel;
	int width, height;
	char buffer[50];

    FILE *in_file, *out_file;
    in_file = fopen("exp1.pgm", "r");
    out_file = fopen("out1.pgm", "w");

    //Error message
    if (!in_file || !out_file) {
        printf("Error opening files.\n");
        return 1;
    }

    //Read & write header
    // //Skip PGM headers and comment lines for l.pgm
    fgets(buffer, sizeof(buffer), in_file); // P2
    fputs(buffer, out_file);
    // Or // Read header
    //fgets(buffer, 50, in_file); // P2
    //fprintf(out_file, "%s", buffer);
    do {
        fgets(buffer, sizeof(buffer), in_file);
    } while (buffer[0] == '#');
    // This should now be the size line, so skip one more line for max gray value

    // Read width and height
    sscanf(buffer, "%d %d", &width, &height);
    fgets(buffer, sizeof(buffer), in_file);
    // Write header to output file
    fprintf(out_file,"%d %d\n255\n",width, height);
    //fprintf(out_file,"P2\n%d %d\n255\n",width, height);

    // Read and write max grayscale value
    //fscanf(in_file, "%d", &maxval);
   // fprintf(out_file, "%d\n", maxval);
   //Or
   // Read max value
   //int max_val;
    //fgets(buffer, 50, in_file);
    //sscanf(buffer, "%d", &max_val);
    //fprintf(out_file, "%d\n", max_val);

//Exp-1
    // Process and write pixel data
    // Loop through image pixels
    for (n = 0; n < width; n++) {           // NOTE: outer loop is rows
        for (m = 0; m < height; m++) {       // inner loop is columns
            fscanf(in_file, "%d", &pixel);
                if (pixel < 0) pixel = 0;
                if (pixel > 255) pixel = 255;
            // fprintf(out_file, "%d ", maxval - pixel); // Negative
            //fprintf(out_file,"%d ", pixel); //grayscale image | 255=white | 0=black
            fprintf(out_file,"%d ", 255-pixel); //negative image | 255=white | 0=black
        }
        fprintf(out_file, "\n"); // Newline for each row (good practice for PGM)
    }

    fclose(in_file);
    fclose(out_file);

    printf("Done! Image processed successfully.\n");
    return 0;
}


*/

