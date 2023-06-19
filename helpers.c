#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int new_color = 0;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            new_color = round(((float) image[i][k].rgbtRed + image[i][k].rgbtGreen + image[i][k].rgbtBlue) / 3);
            image[i][k].rgbtRed = new_color;
            image[i][k].rgbtGreen = new_color;
            image[i][k].rgbtBlue = new_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //3D Array for storing new image
    //new_image[height][width][0] represents new sepia Red pixel
    //new_image[height][width][1] represents new sepia Green pixel
    //new_image[height][width][2] represents new sepia Blue pixel
    int new_image[height][width][3];
    //Iterating through each row
    for (int i = 0; i < height; i++)
    {
        //Iterating through each column
        for (int k = 0; k < width; k++)
        {
            //Generating sepia Red
            new_image[i][k][0] = round(.393 * image[i][k].rgbtRed + .769 * image[i][k].rgbtGreen + .189 * image[i][k].rgbtBlue);
            //Generating sepia Green
            new_image[i][k][1] = round(.349 * image[i][k].rgbtRed + .686 * image[i][k].rgbtGreen + .168 * image[i][k].rgbtBlue);
            //Generating sepia Blue
            new_image[i][k][2] = round(.272 * image[i][k].rgbtRed + .534 * image[i][k].rgbtGreen + .131 * image[i][k].rgbtBlue);
            //Capping new Red to 255
            if (new_image[i][k][0] > 255)
            {
                new_image[i][k][0] = 255;
            }
            //Capping new Green to 255
            if (new_image[i][k][1] > 255)
            {
                new_image[i][k][1] = 255;
            }
            //Capping new Blue to 255
            if (new_image[i][k][2] > 255)
            {
                new_image[i][k][2] = 255;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Assign the new color values to the original image
            image[i][k].rgbtRed = new_image[i][k][0];
            image[i][k].rgbtGreen = new_image[i][k][1];
            image[i][k].rgbtBlue = new_image[i][k][2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Array for storing new image
    RGBTRIPLE new_image[height][width];
    //Iterating through each row
    for (int i = 0; i < height; i++)
    {
        //Iterating through each column
        for (int k = 0; k < width; k++)
        {
            //Reflecting pixels and storing in array new_image
            new_image[i][k].rgbtRed = image[i][width - 1 - k].rgbtRed;
            new_image[i][k].rgbtGreen = image[i][width - 1 - k].rgbtGreen;
            new_image[i][k].rgbtBlue = image[i][width - 1 - k].rgbtBlue;
        }
    }
    //Copying pixels from array new_image to array image
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = new_image[i][k].rgbtRed;
            image[i][k].rgbtGreen = new_image[i][k].rgbtGreen;
            image[i][k].rgbtBlue = new_image[i][k].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //3D Array for storing new image
    //new_image[height][width][0] represents new sepia Red pixel
    //new_image[height][width][1] represets new sepia Green pixel
    //new_image[height][width][2] represents new sepia Blue pixel
    int new_image[height][width][3];
    //Iterating through each row
    for (int i = 0; i < height; i++)
    {
        //Iterating through each column
        for (int k = 0; k < width; k++)
        {
            new_image[i][k][0] = 0;
            new_image[i][k][1] = 0;
            new_image[i][k][2] = 0;
            //Handling exceptions first
            //Top left
            if (i == 0 && k == 0)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 4);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 4);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 4);
            }
            //Top right
            else if (i == 0 && k == width - 1)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 4);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 4);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 4);
            }
            //Bottom right
            else if (i == height - 1 && k == width - 1)
            {
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 4);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 4);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 4);
            }
            //Bottom left
            else if (i == height - 1 && k == 0)
            {
                for (int a = -1; a < 1; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 4);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 4);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 4);
            }
            //Top row
            else if (i == 0)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 6);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 6);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 6);
            }
            //Right column
            else if (k == width - 1)
            {
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 6);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 6);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 6);
            }
            //Bottom row
            else if (i == height - 1)
            {
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 6);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 6);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 6);
            }
            //Left column
            else if (k == 0)
            {
                for (int a = -1; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 6);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 6);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 6);
            }
            //Rest of the image
            else
            {
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        new_image[i][k][0] += image[i + a][k + b].rgbtRed;
                        new_image[i][k][1] += image[i + a][k + b].rgbtGreen;
                        new_image[i][k][2] += image[i + a][k + b].rgbtBlue;
                    }
                }
                new_image[i][k][0] = round((float) new_image[i][k][0] / 9);
                new_image[i][k][1] = round((float) new_image[i][k][1] / 9);
                new_image[i][k][2] = round((float) new_image[i][k][2] / 9);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Assign the new color values to the original image
            image[i][k].rgbtRed = new_image[i][k][0];
            image[i][k].rgbtGreen = new_image[i][k][1];
            image[i][k].rgbtBlue = new_image[i][k][2];
        }
    }
    return;
}