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
    int realWidth = width /2; // one less comaprison so it should run faster (hyptho)
     for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < realWidth; column++)
        {
            float colorRed = image[row][column].rgbtRed;
            float colorGreen = image[row][column].rgbtGreen;
            float colorBlue = image[row][column].rgbtBlue;

            image[row][column].rgbtRed =  image[row][width-column -1].rgbtRed;
            image[row][column].rgbtGreen = image[row][width-column -1].rgbtGreen;
            image[row][column].rgbtBlue = image[row][width-column -1].rgbtBlue;

            image[row][width-column -1].rgbtRed = colorRed;
            image[row][width-column -1].rgbtGreen = colorGreen;
            image[row][width-column -1].rgbtBlue = colorBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE tempImage[height][width];
    
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int count = 0;
            double sumRed = 0.00;
            double sumGreen = 0.00;
            double sumBlue = 0.00;
            //current box
            if(image[row][column].rgbtRed >= 0)
            {
                sumRed += image[row][column].rgbtRed;
                sumGreen += image[row][column].rgbtGreen;
                sumBlue += image[row][column].rgbtBlue;
                count++;
            }    
             if(image[row][column+1].rgbtRed >= 0)
            {
                sumRed += image[row][column+1].rgbtRed;
                sumGreen += image[row][column+1].rgbtGreen;
                sumBlue += image[row][column+1].rgbtBlue;
                count++;
            }    
             if(image[row][column-1].rgbtRed >= 0)
            {
                sumRed += image[row][column-1].rgbtRed;
                sumGreen += image[row][column-1].rgbtGreen;
                sumBlue += image[row][column-1].rgbtBlue;
                count++;
            }    
            
            //we start with row on top
            //directly on top
            if(image[row +1 ][column].rgbtRed >= 0)
            {
                sumRed += image[row +1][column].rgbtRed;
                sumGreen += image[row+1][column].rgbtGreen;
                sumBlue += image[row+1][column].rgbtBlue;
                count++;
            }
            //left top row
            if(image[row +1 ][column -1].rgbtRed >= 0)
            {
                sumRed += image[row +1][column-1].rgbtRed;
                sumGreen += image[row+1][column-1].rgbtGreen;
                sumBlue += image[row+1][column-1].rgbtBlue;
                count++;
            }
            if(image[row +1 ][column +1].rgbtRed >= 0)
            {
                sumRed += image[row +1][column+1].rgbtRed;
                sumGreen += image[row+1][column+1].rgbtGreen;
                sumBlue += image[row+1][column+1].rgbtBlue;
                count++;
            }
            if(image[row -1 ][column].rgbtRed >= 0)
            {
                sumRed += image[row -1][column].rgbtRed;
                sumGreen += image[row-1][column].rgbtGreen;
                sumBlue += image[row-1][column].rgbtBlue;
                count++;
            }
            if(image[row -1 ][column+1].rgbtRed >= 0)
            {
                sumRed += image[row -1][column+1].rgbtRed;
                sumGreen += image[row-1][column+1].rgbtGreen;
                sumBlue += image[row-1][column+1].rgbtBlue;
                count++;
            }
            if(image[row -1 ][column-1].rgbtRed >= 0 )
            {
                sumRed += image[row -1][column-1].rgbtRed;
                sumGreen += image[row-1][column-1].rgbtGreen;
                sumBlue += image[row-1][column-1].rgbtBlue;
                count++;
            }
            int averageRed = round(sumRed / count);
            int averageGreen = round(sumGreen / count);
            int averageBlue = round(sumBlue / count);
            tempImage[row][column].rgbtRed = averageRed ;
            tempImage[row][column].rgbtGreen = averageGreen;
            tempImage[row][column].rgbtBlue = averageBlue;
            
            
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed  = tempImage[row][column].rgbtRed;
            image[row][column].rgbtGreen  = tempImage[row][column].rgbtGreen;
            image[row][column].rgbtBlue = tempImage[row][column].rgbtBlue;
        }
    }    
    
    return;
}
