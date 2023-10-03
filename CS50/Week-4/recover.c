#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Create a buffer to read the signatures
    uint8_t buffer[512];
    int imageCount = 0;
    FILE *output = NULL;
    bool foundjpeg = false;

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check file contents
    if (file == NULL)
    {
        printf("File could not be opened\n");
        return 2;
    }

    // Read the raw file
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Check for the first 4 signatures of the jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if a jpeg has already been found
            if (foundjpeg)
            {
                // Close the previous output file
                fclose(output);
            }

            // Create a new output file 
            char filename[8];
            sprintf(filename, "%03i.jpg", imageCount);
            output = fopen(filename, "w");

            // Check if the file can be opened
            if (output == NULL)
            {
                printf("Could not create file\n");
                fclose(file);
                return 3;
            }

            imageCount++;

            // Write into the output file
            fwrite(buffer, 512, 1, output);

            // Set foundjpeg to true
            foundjpeg = true;

        }

        // Proceed to write if the jpeg has already been found
        else if (foundjpeg)
        {
            // Write into the output file
            fwrite(buffer, 512, 1, output);
        }
    }

    // Close the output file
    fclose(output);

    // Close the input file
    fclose(file);

    return 0;
}
