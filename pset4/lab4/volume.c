// Modifies the volume of an audio file
// WILLIAM BERNAL
// LAB4

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    uint8_t hdr[HEADER_SIZE];
    int16_t sample;

    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    fread(hdr, HEADER_SIZE, 1, input);
    fwrite(hdr, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample = sample * factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}






