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
            int colorRed = round(image[row][column].rgbtRed);
            int colorGreen = round(image[row][column].rgbtGreen);
            int colorBlue = round(image[row][column].rgbtBlue);
            
            
            double average = (colorRed + colorGreen + colorBlue) / 3;
            int roundedValue = round(average);
            
            image[row][column].rgbtRed = roundedValue;
            image[row][column].rgbtGreen = roundedValue;
            image[row][column].rgbtBlue = roundedValue;
            
           
            
            
            
  
        }
    }
    return ;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
