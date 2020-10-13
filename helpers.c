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
            float count = 0.00;
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            
            //assumption from repetitive motion we could start from bottom to top 
            for (int movimientoLateral = -1; movimientoLateral < 2; movimientoLateral++)
            {
                for (int movimientoHorizontal = -1; movimientoHorizontal < 2; movimientoHorizontal++)
                {
                    if(movimientoLateral + row < 0 || row + movimientoLateral > height - 1 || movimientoHorizontal + column > width -1 || column + movimientoHorizontal > width -1)
                    {
                        continue;
                    }
                    sumRed += image[row + movimientoLateral][column + movimientoHorizontal].rgbtRed;
                    sumGreen+= image[row + movimientoLateral][column + movimientoHorizontal].rgbtGreen;
                    sumBlue += image[row + movimientoLateral][column + movimientoHorizontal].rgbtBlue;
                    count++;
                }
            }
            
            int averageRed = round(sumRed/count);
            int averageGreen = round(sumGreen/count);
            int averageBlue = round(sumBlue/ count);
            tempImage[row][column].rgbtBlue = averageBlue ;
            tempImage[row][column].rgbtRed =averageRed ;
            tempImage[row][column].rgbtGreen =averageGreen ; 
            
        }
    }    
        
    
    for (int row = 0; row < height; row++)
    {
       for (int column = 0; column < width; column++)
       {
              image[row][column] = tempImage[row][column] ;
       }
    }
  
        
    
    return; 
}

