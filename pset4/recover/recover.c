#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Define a 512 bytes
#define BLOCK_SIZE 512

bool verifyLastByte(unsigned char curVal);

int main(int argc, char *argv[])

{
    // initial output file
    char outfile[8];

    // file number increment
    int fileNumber = 0;

    //verify number of pictures found
    int flagImageFound = 0;

    // verify that the program should accept exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open the file %s.\n", argv[1]);
        return 1;
    }

    //define an initial output file with null;
    FILE *outptr = NULL;

    //creates the memmory buffer
    unsigned char blockMemory[BLOCK_SIZE];

    //walk trough the forensic image file

    while (fread(blockMemory, BLOCK_SIZE, 1, file) == 1)
    {
        // Verify from first byte to third byte, left to right
        // to determinate if they demarcate the start of a JPEG.
        if (blockMemory[0] == 0xff && blockMemory[1] == 0xd8 && blockMemory[2] == 0xff)
        {
            if (verifyLastByte(blockMemory[3]) == true)
            {
                if (flagImageFound == 1)
                {
                    // This flag shows that this is the SECOND time (or more) that we find a new jpg.
                    // so we have to close the current file and start a new one
                    fclose(outptr);
                }
                else
                {
                    // we found the beginning of the first image so we doesn't have to close the output file.
                    // instead we need to start writing the first one OUTPUT file.
                    // next time we found a new JPG, we are to close that file, and start a new one
                    flagImageFound = 1;
                }

                // it creates the file name. By incrementing the file number
                sprintf(outfile, "%03d.jpg", fileNumber);

                outptr = fopen(outfile, "a");
                fileNumber++;
            }
        }

        // after find the beginning of a JPG file, write bytes in the output file and doesn't close it
        // if there is not a new file.
        if (flagImageFound == 1)
        {
            // In the output file write a block of 512 bytes
            // this occurs when there is not a JPG file beginning
            fwrite(&blockMemory, BLOCK_SIZE, 1, outptr);
        }
    }

    if (outptr == NULL)
    {
        fclose(outptr);
    }
    if (file == NULL)
    {
        fclose(file);
    }
    return 0;
}

// verify if the last byte range between 0xe0 and 0xef
bool verifyLastByte(unsigned char curVal)
{
    if (curVal >= 0xe0 && curVal <= 0xef)
    {
        return true;
    }
    else
    {
        return false;
    }
}