/****
 * @author: William Bernal
 * @date: March 27, 2021
 * @email: bern0295@algonquinlive.com
 * @program: helpers.c
 **** */
 
 
#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    unsigned int x, y;
    double averageColor;

    // for each pixel in the original image
    // calculate the average red, green & blue
    // on the adyacent pixcels
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            //original color
            averageColor = round(((double) image[x][y].rgbtRed +
                                  (double) image[x][y].rgbtGreen +
                                  (double) image[x][y].rgbtBlue) / 3.0);

            if (averageColor > 255)
            {
                averageColor =  255;
            }

            image[x][y].rgbtRed = averageColor;
            image[x][y].rgbtGreen = averageColor;
            image[x][y].rgbtBlue = averageColor;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    unsigned int x, y;
    RGBTRIPLE temp;

    // switch each pixel from the most left to the most right
    // and so on.
    for (x = 0; x < height; x++)
    {
        for (y = 0; y <= (width - 1) / 2; y++)
        {
            // temporal pixel with three channel colors
            temp.rgbtRed = image[x][y].rgbtRed;
            temp.rgbtGreen = image[x][y].rgbtGreen;
            temp.rgbtBlue = image[x][y].rgbtBlue;

            // switch image pixel
            image[x][y].rgbtRed = image[x][width - 1 - y].rgbtRed;
            image[x][y].rgbtGreen = image[x][width - 1 - y].rgbtGreen;
            image[x][y].rgbtBlue = image[x][width - 1 - y].rgbtBlue;

            image[x][width - 1 - y].rgbtRed = temp.rgbtRed;
            image[x][width - 1 - y].rgbtGreen = temp.rgbtGreen;
            image[x][width - 1 - y].rgbtBlue = temp.rgbtBlue;
        }
    }

    return;
}

// function to calculate the average pixel using always A COPY OF the
// original image. the result pixel is retourned by the function
// to update the original image.
// For that reason we need a copy of the original one.
RGBTRIPLE getAverageColor(int height, int width,
                          RGBTRIPLE(*originalImage)[width], int x, int y)
{
    RGBTRIPLE pixelAvrg;
    double rgbtRed = 0.0, rgbtGreen = 0.0, rgbtBlue = 0.0;
    int numPixels = 0, initialX = x - 1;
    int finalX = x + 1, initialY = y - 1, finalY = y + 1;

    // calculate the initial index for x & y
    // This is to prevent errors when the current pixel
    // is located on the edges of the image
    if (x == 0)
    {
        initialX = 0;
    }

    if (x == height - 1)
    {
        finalX = height - 1;
    }

    if (y == 0)
    {
        initialY = 0;
    }

    if (y == width - 1)
    {
        finalY = width - 1;
    }

    // calculate the average using the Copy of the Original image
    for (int a = initialX; a <= finalX; a++)
    {
        for (int b = initialY; b <= finalY; b++)
        {
            rgbtRed += (double) originalImage[a][b].rgbtRed;
            rgbtGreen += (double) originalImage[a][b].rgbtGreen;
            rgbtBlue += (double) originalImage[a][b].rgbtBlue;
            numPixels++;
        }
    }
    // Calculate the average for each color channel
    pixelAvrg.rgbtRed = round(rgbtRed / numPixels);
    pixelAvrg.rgbtGreen = round(rgbtGreen / numPixels);
    pixelAvrg.rgbtBlue = round(rgbtBlue / numPixels);

    return pixelAvrg;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];


    // copy the image
    // to create a new workable image to get original pixel color
    // to calculate averages over original pixels
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            originalImage[x][y].rgbtRed = image[x][y].rgbtRed;
            originalImage[x][y].rgbtGreen = image[x][y].rgbtGreen;
            originalImage[x][y].rgbtBlue = image[x][y].rgbtBlue;
        }
    }



    // go through the original image
    // call the function getAverageColor(height, width, originalImage, x, y);
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {

            RGBTRIPLE newPixel = getAverageColor(height, width,
                                                 originalImage, x, y);
            image[x][y].rgbtRed = newPixel.rgbtRed;
            image[x][y].rgbtGreen = newPixel.rgbtGreen;
            image[x][y].rgbtBlue = newPixel.rgbtBlue;
        }
    }

    return;
}

// return a pixel with the new colors for edge
// calculate the edges based on the Convolutional Matrix nX & X
RGBTRIPLE getEdgePixel(int height, int width, RGBTRIPLE(*originalImage)[width],
                       int x, int y, int (*convMatrixX)[3],
                       int (*convMatrixY)[3])
{
    RGBTRIPLE convPixel;

    double rgbtRed = 0.0, rgbtGreen = 0.0, rgbtBlue = 0.0;
    double rgbtRedGx = 0.0, rgbtGreenGx = 0.0, rgbtBlueGx = 0.0;
    double rgbtRedGy = 0.0, rgbtGreenGy = 0.0, rgbtBlueGy = 0.0;
    int initialX = x - 1, finalX = x + 1, initialY = y - 1, finalY = y + 1;
    int gX = 0, gY = 0;

    if (x == 0)
    {
        initialX = 0;
        gX = 1;
    }

    if (x == height - 1)
    {
        finalX = height - 1;
    }

    if (y == 0)
    {
        initialY = 0;
    }


    if (y == width - 1)
    {
        finalY = width - 1;
    }


// calculate GX & GY
    for (int a = initialX; a <= finalX; a++)
    {
        gY = 0;
        if (y == 0)
        {
            gY = 1;
        }

        for (int b = initialY; b <= finalY; b++)
        {
            rgbtRedGx += (double) originalImage[a][b].rgbtRed *
                         convMatrixX[gX][gY];

            rgbtGreenGx += (double) originalImage[a][b].rgbtGreen *
                           convMatrixX[gX][gY];

            rgbtBlueGx += (double) originalImage[a][b].rgbtBlue *
                          convMatrixX[gX][gY];

            rgbtRedGy += (double) originalImage[a][b].rgbtRed *
                         convMatrixY[gX][gY];

            rgbtGreenGy += (double) originalImage[a][b].rgbtGreen *
                           convMatrixY[gX][gY];

            rgbtBlueGy += (double) originalImage[a][b].rgbtBlue *
                          convMatrixY[gX][gY];
            gY++;
        }
        gX++;
    }

    // calculate the Convolutional red, Green & Blue pixel results

    rgbtRed = round(sqrt(pow(rgbtRedGx, 2) + pow(rgbtRedGy, 2)));
    rgbtGreen = round(sqrt(pow(rgbtGreenGx, 2) + pow(rgbtGreenGy, 2)));
    rgbtBlue = round(sqrt(pow(rgbtBlueGx, 2) + pow(rgbtBlueGy, 2)));

    if (rgbtRed > 255)
    {
        rgbtRed = 255;
    }

    if (rgbtGreen > 255)
    {
        rgbtGreen = 255;
    }

    if (rgbtBlue > 255)
    {
        rgbtBlue = 255;
    }

    convPixel.rgbtRed = rgbtRed;
    convPixel.rgbtGreen = rgbtGreen;
    convPixel.rgbtBlue = rgbtBlue;

    return convPixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE originalImage[height][width];

    // copy the image
    // to create a new workable image to get original pixel color
    // to calculate Convolutionary matrix X & Y over original pixels
    // copy the image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            originalImage[x][y].rgbtRed = image[x][y].rgbtRed;
            originalImage[x][y].rgbtGreen = image[x][y].rgbtGreen;
            originalImage[x][y].rgbtBlue = image[x][y].rgbtBlue;
        }
    }

    // define the default convolutionary matrix X & Y
    int convMatrixX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int convMatrixY[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1 }
    };

    // calculate each new pixel-point color
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            RGBTRIPLE newPixel = getEdgePixel(height, width, originalImage,
                                              x, y, convMatrixX, convMatrixY);
            image[x][y].rgbtRed = newPixel.rgbtRed;
            image[x][y].rgbtGreen = newPixel.rgbtGreen;
            image[x][y].rgbtBlue = newPixel.rgbtBlue;
        }
    }

    return;
}
