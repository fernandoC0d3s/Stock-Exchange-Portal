#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            float colorRed = image[row][column].rgbtRed;
            float colorGreen = image[row][column].rgbtGreen;
            float colorBlue = image[row][column].rgbtBlue;
            
            
            double average = (colorRed + colorGreen + colorBlue) / 3;
            int roundedValue = round(average);
            
            image[row][column].rgbtRed = roundedValue;
            image[row][column].rgbtGreen = roundedValue;
            image[row][column].rgbtBlue = roundedValue;
  
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float colorRed = image[row][column].rgbtRed;
            float colorGreen = image[row][column].rgbtGreen;
            float colorBlue = image[row][column].rgbtBlue;
            
            
            double testSepiaRed = .393 * colorRed + .769 * colorGreen + .189 * colorBlue;
            double testSepiaGreen = .349 * colorRed + .686 * colorGreen + .168 * colorBlue;
            double testSepiaBlue = .272 * colorRed + .534 * colorGreen + .131 * colorBlue;
          
            int sepiaRed = round(testSepiaRed);
            int sepiaGreen = round(testSepiaGreen);
            int sepiaBlue = round(testSepiaBlue);
            
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }
            
            image[row][column].rgbtRed = sepiaRed;
            image[row][column].rgbtGreen = sepiaGreen;
            image[row][column].rgbtBlue = sepiaBlue;
        }
    }    
    
    
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            int counter = 0;
            counter--;
            
            RGBTRIPLE first = image[row][column];  //FIRST PIXEL
            RGBTRIPLE temp = image[row][column];
            RGBTRIPLE last = image[row][width - counter]; // last pixel in array
            first = last; //make pixel first same to last one
            last = temp; // make last pixel first using temporary value
          
            
        }
    }    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
