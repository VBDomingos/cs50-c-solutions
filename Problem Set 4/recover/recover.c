#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "rb");
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    int imgCount = 0;
    FILE *outptr = NULL;
    char filename[8];

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            sprintf(filename, "%03i.jpg", imgCount);
            outptr = fopen(filename, "wb");
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(raw_file);
                return 1;
            }

            imgCount++;
        }

        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(raw_file);

    return 0;
}
