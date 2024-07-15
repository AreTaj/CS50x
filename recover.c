#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Open the memory card
    char *file = argv[1];
    FILE *raw_file = fopen(file, "r");
    if (raw_file == NULL) 
    {
        printf("Could not open %s.\n", file);
        return 1;
    }

    bool jpg_found = false;
    int jpg_count = 0;          // count of found jpg
    uint8_t buffer[BLOCK_SIZE];  // buffer stores block of data from image
    char jpg_name[8];           // array stores filename of current jpg
    FILE *outptr = NULL;        // out pointer

    // While there's still data left to read from the memory card
    while (fread(buffer, BLOCK_SIZE, 1, raw_file) == 1)
    {
        // look for jpg markers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous jpg if any
            if (jpg_found)
            {
                fclose(outptr);
            }
            // otherwise, found
            else
            {
                jpg_found = true;
            }
        
            sprintf(jpg_name, "%03d.jpg", jpg_count);   // generate filename of new jpg file
            outptr = fopen(jpg_name, "w");              // open new file with filename
            if (outptr == NULL)
            {
                fclose(raw_file);
                printf("Could not create %s\n", jpg_name);
                return 3;
            }
            jpg_count++;
        }

        if (jpg_found)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }

    fclose(raw_file);
    if (jpg_found)
    {
        fclose(outptr);
    }
    return 0;
}
