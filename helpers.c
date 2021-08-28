#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of Blue, Green, Red pixel values and set new pixel values equal to average
            int pixel_average = round(((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = pixel_average;
            image[i][j].rgbtGreen = pixel_average;
            image[i][j].rgbtRed = pixel_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia color values
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Set color values to 255 if calculated color value is greater than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set original color values to newly calculated sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_blur[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of surrounding pixels for first row
            if (i == 0)
            {
                // First column
                if (j == 0)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i + 1][j + 1].rgbtRed) / 4);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i + 1][j + 1].rgbtGreen) / 4);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i + 1][j + 1].rgbtBlue) / 4);
                }
                // Last column
                else if (j == width - 1)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i + 1][j - 1].rgbtRed) / 4);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i + 1][j - 1].rgbtGreen) / 4);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i + 1][j - 1].rgbtBlue) / 4);
                }
                // Middle columns
                else
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i + 1][j - 1].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i + 1][j + 1].rgbtRed) / 6);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i + 1][j - 1].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i + 1][j + 1].rgbtGreen) / 6);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i + 1][j - 1].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i + 1][j + 1].rgbtBlue) / 6);
                }
            }
            // Calculate average of surrounding pixels for last row
            else if (i == height - 1)
            {
                // First column
                if (j == 0)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i - 1][j + 1].rgbtRed) / 4);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i - 1][j + 1].rgbtGreen) / 4);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i - 1][j + 1].rgbtBlue) / 4);
                }
                // Last column
                else if (j == width - 1)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i - 1][j - 1].rgbtRed) / 4);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i - 1][j - 1].rgbtGreen) / 4);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i - 1][j - 1].rgbtBlue) / 4);
                }
                // Middle columns
                else
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i - 1][j - 1].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i - 1][j + 1].rgbtRed) / 6);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i - 1][j - 1].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i - 1][j + 1].rgbtGreen) / 6);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i - 1][j - 1].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i - 1][j + 1].rgbtBlue) / 6);
                }
            }
            // Calculate average of surrounding pixels for middle rows
            else
            {
                // First column
                if (j == 0)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i - 1][j + 1].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i + 1][j + 1].rgbtRed) / 6);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i - 1][j + 1].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i + 1][j + 1].rgbtGreen) / 6);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i - 1][j + 1].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i + 1][j + 1].rgbtBlue) / 6);
                }
                // Last column
                else if (j == width - 1)
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i - 1][j - 1].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i + 1][j - 1].rgbtRed) / 6);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i - 1][j - 1].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i + 1][j - 1].rgbtGreen) / 6);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i - 1][j - 1].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i + 1][j - 1].rgbtBlue) / 6);
                }
                // Middle columns
                else
                {
                    image_blur[i][j].rgbtRed = round(((float) image[i][j].rgbtRed + (float) image[i - 1][j - 1].rgbtRed + (float) image[i - 1][j].rgbtRed + (float) image[i - 1][j + 1].rgbtRed + (float) image[i][j - 1].rgbtRed + (float) image[i][j + 1].rgbtRed + (float) image[i + 1][j - 1].rgbtRed + (float) image[i + 1][j].rgbtRed + (float) image[i + 1][j + 1].rgbtRed) / 9);
                    image_blur[i][j].rgbtGreen = round(((float) image[i][j].rgbtGreen + (float) image[i - 1][j - 1].rgbtGreen + (float) image[i - 1][j].rgbtGreen + (float) image[i - 1][j + 1].rgbtGreen + (float) image[i][j - 1].rgbtGreen + (float) image[i][j + 1].rgbtGreen + (float) image[i + 1][j - 1].rgbtGreen + (float) image[i + 1][j].rgbtGreen + (float) image[i + 1][j + 1].rgbtGreen) / 9);
                    image_blur[i][j].rgbtBlue = round(((float) image[i][j].rgbtBlue + (float) image[i - 1][j - 1].rgbtBlue + (float) image[i - 1][j].rgbtBlue + (float) image[i - 1][j + 1].rgbtBlue + (float) image[i][j - 1].rgbtBlue + (float) image[i][j + 1].rgbtBlue + (float) image[i + 1][j - 1].rgbtBlue + (float) image[i + 1][j].rgbtBlue + (float) image[i + 1][j + 1].rgbtBlue) / 9);
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blur[i][j];
        }
    }
    return;
}
