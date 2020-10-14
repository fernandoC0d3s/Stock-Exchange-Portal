#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512
bool JPGHeader(uint8_t buffer[]);


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    char* inputFile = argv[1];
    if(inputFile == NULL)
    {
       printf("Usage: ./recover image");
       return 1; 
    }
    FILE* inputPtr = fopen(inputFile, "r");
    if(inputPtr == NULL)
    {
        printf("Could not open file %s", inputFile);
        return 1;
        
    }
    char fileName[8];
    FILE* outputPtr = NULL;
    uint8_t buffer[BLOCKSIZE];
    int count = 0;
    
    while(fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputPtr)|| feof(inputPtr) == 0)
    {
        if(JPGHeader(buffer))
        {
            if(outputPtr == NULL)
            {
                fclose(outputPtr);
            }
            sprintf(fileName, "%03i.jpg", count);
            outputPtr = fopen(fileName, "w");
            count++;
        }
        if(outputPtr != NULL)
        {
            fwrite(buffer, sizeof(buffer),1, outputPtr);
        }
    }
    if(inputPtr == NULL)
    {
        fclose(inputPtr);
    }
    if(outputPtr == NULL)
    {
        fclose(outputPtr);
    }
    return 0;
}
bool JPGHeader(uint8_t buffer[])
{
    return buffer[0] == 0xff
    && buffer[1] == 0xd8
    && buffer[2] == 0xff
    && (buffer[3] & 0xf0) == 0xe0; 
}
