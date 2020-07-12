#include "helpers.h"
#include <math.h>

// https://cs50.harvard.edu/x/2020/psets/4/filter/less/

// function prototype
double square(double tempcolour);

// convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // outer forloop to loop through the rows of the 2d array for the image
    for (int i = 0; i < height; i++)
    {
        // inner forloop to loop through the columns of the 2d array for the image
        for (int j = 0; j < width; j++)
        {
            // create a float called "average" and round it to the nearest integer for the average of red, gteen and blue in the current index for the pixel at [i][j]
            float average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            image[i][j].rgbtBlue = average; // take this average rgb value & assign it to the current blue value for the pixel at [i][j]
            image[i][j].rgbtGreen = average;  // take this average rgb value & assign it to the current green value for the pixel at [i][j]
            image[i][j].rgbtRed = average;  // take this average rgb value & assign it to the current red value for the pixel at [i][j]
        }
    }
    return;
}

// convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // algorithm to adjust red, green and blue to a sepia filter
            int Red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int Green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int Blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // if after this algorithm is run, the red value is over 255, change red to == 255
            if (Red > 255)
            {
                Red = 255;
            }

            // if after this algorithm is run, the green value is over 255, change green to == 255
            if (Green > 255)
            {
                Green = 255;
            }

            // if after this algorithm is run, the blue value is over 255, change blue to == 255
            if (Blue > 255)
            {
                Blue = 255;
            }

            // update the red, green and blue values for the pixel at [i][j] to the new rgb values
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtBlue = Blue;
            image[i][j].rgbtGreen = Green;
        }
    }
    return;
}

// reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     // outter nested forloop to loop through the "rows" of pixels in this 2d array
    for (int i = 0; i < height; i++)
    {
        // inner nested forloop to loop through the "columns" of each "row" of pixels in this 2d array, but only up until the "halfway point"
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];  // take the current pixel that exists at the current index of image[i][j] && store it in temp
            image[i][j] = image[i][width - 1 - j];  // take the current pixel at image[i][the amount of the width of pixels across the image - 1 (to be in bounds of the array) - the current value of "j" to properly ensure the pixels we are swapping are perfecatly "centered" across from each other
            image[i][width - 1 - j] = temp;  // take this pixel orignally in temp, and move it into image[i][width - 1 - j]
        }
    }
}

// blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // new array to store tempoary "blurred" pixel data
    RGBTRIPLE blurred[height][width];
    // first nested forloop to loop through the entire bitmap pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // tempoary variables
            int counter = 0;
            float temp_red = 0;
            float temp_green = 0;
            float temp_blue = 0;

            // second nested loop to check the 3x3 grid - explanation: https://i.imgur.com/Sc8PMY2.png
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // edge detection condition, to check if the index of the pixels being checked is within the range of the whole bitmap grid
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        // store the value in the temp color int and increase the counter
                        temp_red += image[k][l].rgbtRed;
                        temp_green += image[k][l].rgbtGreen;
                        temp_blue += image[k][l].rgbtBlue;
                        counter++;
                    }
                }
            }
            // average color value of neighbour pixels and assign it to image
            blurred[i][j].rgbtRed = round(temp_red / counter);
            blurred[i][j].rgbtGreen = round(temp_green / counter);
            blurred[i][j].rgbtBlue = round(temp_blue / counter);
        }
    }
    // third nested forloop to go back over image[i][j] again and assign the blurred[i][j] values to each pixel
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = blurred[m][n];
        }
    }
}

// detect & highligh edges in an image
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create new array to store the tempoary "gx" values for each pixel
    // create new array to store the tempoary "gy" values for each pixel
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // create a new array to store the "edges" values of each pixel in the bitmap
    RGBTRIPLE edges[height][width];

    // outer nested loop to go through bitmap image[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // temp variables for red, green and blue values for "gx" and "gy"
            double temp_redx = 0.0;
            double temp_greenx = 0.0;
            double temp_bluex = 0.0;
            double temp_redy = 0.0;
            double temp_greeny = 0.0;
            double temp_bluey = 0.0;

            // inner nested loop to go through the 3x3 grid for the kernel. in this example, both "i" and "j" will both always be set to index "22" of the image[22][22] bitmap
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // edge detection condition, to check if the index of the pixels being checked is within the range of the whole bitmap grid
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        int x = k - i + 1;  // x becomes value of "k" (21) - value of "i" (22), this == -1. We want the index of our gx array to always start at 0, so we +1 to make x == 0. when k and l are incremented, x gets reset here. because they're declared inside the inner loop, they only exist during an iteration in that loop.
                        int y = l - j + 1;  // y becomes value of "l" (21) - value of "j" (22), this == -1. We want the index of our gx array to always start at 0, so we +1 to make x == 0. when k and l are incremented, y gets reset here. because they're declared inside the inner loop, they only exist during an iteration in that loop.

                        // calcuate Gx for each color
                        temp_redx += image[k][l].rgbtRed * Gx[x][y];
                        temp_greenx += image[k][l].rgbtGreen * Gx[x][y];
                        temp_bluex += image[k][l].rgbtBlue * Gx[x][y];

                        // calcuate Gy for each color
                        temp_redy += image[k][l].rgbtRed * Gy[x][y];
                        temp_greeny += image[k][l].rgbtGreen * Gy[x][y];
                        temp_bluey += image[k][l].rgbtBlue * Gy[x][y];
                    }
                }
            }
            // square the result of Gx squared && Gy squared and add these together, store them in tempoary floats "r" "b" "g"
            double r = square(temp_redx) + square(temp_redy);
            double g = square(temp_greenx) + square(temp_greeny);
            double b = square(temp_bluex) + square(temp_bluey);

            // find the square root of "r" "g" * "b"
            double sqrt_r = sqrt(r);
            double sqrt_g = sqrt(g);
            double sqrt_b = sqrt(b);

            // round "r" "b" & "g" to nearest integer value, and cap that value at a value no greater than 255
            int round_r = round(sqrt_r);
            int round_g = round(sqrt_g);
            int round_b = round(sqrt_b);

            if (round_r > 255)
            {
               round_r = 255;
            }

            if (round_g > 255)
            {
               round_g = 255;
            }

            if (round_b > 255)
            {
               round_b = 255;
            }
            // set edges[i][j] for red, green & blue to these round values
            edges[i][j].rgbtRed = round_r;
            edges[i][j].rgbtGreen = round_g;
            edges[i][j].rgbtBlue = round_b;
        }
    }
    // third nested forloop to go back over image[i][j] again and assign our new channel value we got above at [i][j] to each pixel
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n ++)
        {
            image[m][n] = edges[m][n];
        }
    }
}

// funtion to return whatever int it takes in squared
double square(double tempcolour)
{
    double final;
    final = tempcolour * tempcolour;
    return(final);
}
