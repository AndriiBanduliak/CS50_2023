#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Define the new color you want to use for black pixels
    BYTE newRed = 255;   // Maximum intensity for red
    BYTE newGreen = 0;   // No intensity for green
    BYTE newBlue = 0;    // No intensity for blue

    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black (all color channels are 0)
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Change the color of the pixel to the new color
                image[i][j].rgbtRed = newRed;
                image[i][j].rgbtGreen = newGreen;
                image[i][j].rgbtBlue = newBlue;
            }
        }
    }
}
