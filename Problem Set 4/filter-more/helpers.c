#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
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
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = malloc(height * width * sizeof(RGBTRIPLE));

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Averaging 3x3 surrounding pixels
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newX = x + i;
                    int newY = y + j;

                    if (newX >= 0 && newX < height && newY >= 0 && newY < width)
                    {
                        totalRed += image[newX][newY].rgbtRed;
                        totalGreen += image[newX][newY].rgbtGreen;
                        totalBlue += image[newX][newY].rgbtBlue;
                        count++;
                    }
                }
            }

            copy[x][y].rgbtRed = round(totalRed / (float)count);
            copy[x][y].rgbtGreen = round(totalGreen / (float)count);
            copy[x][y].rgbtBlue = round(totalBlue / (float)count);
        }
    }

    // Copy blurred image back to the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    free(copy);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE(*copy)[width] = malloc(height * width * sizeof(RGBTRIPLE));

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            double sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            double sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newX = x + i;
                    int newY = y + j;

                    if (newX >= 0 && newX < height && newY >= 0 && newY < width)
                    {
                        RGBTRIPLE pixel = image[newX][newY];

                        // Apply Gx and Gy
                        sumRedX += pixel.rgbtRed * Gx[i + 1][j + 1];
                        sumGreenX += pixel.rgbtGreen * Gx[i + 1][j + 1];
                        sumBlueX += pixel.rgbtBlue * Gx[i + 1][j + 1];

                        sumRedY += pixel.rgbtRed * Gy[i + 1][j + 1];
                        sumGreenY += pixel.rgbtGreen * Gy[i + 1][j + 1];
                        sumBlueY += pixel.rgbtBlue * Gy[i + 1][j + 1];
                    }
                }
            }

            // Calculate the final magnitude for each color channel
            int finalRed = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int finalGreen = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int finalBlue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Cap at 255
            copy[x][y].rgbtRed = (finalRed > 255) ? 255 : finalRed;
            copy[x][y].rgbtGreen = (finalGreen > 255) ? 255 : finalGreen;
            copy[x][y].rgbtBlue = (finalBlue > 255) ? 255 : finalBlue;
        }
    }

    // Copy edge-detected image back to the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    free(copy);
}
