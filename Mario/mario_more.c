#include <cs50.h>
#include <stdio.h>

// https://cs50.harvard.edu/x/2020/psets/1/mario/more/

// get_pyramid function prototype
int get_pyramid(string prompt);

int main(void)
{
    // use my get_pyramid function to get the desired pyramid height from the user
    int n = get_pyramid("Height: ");

    // declare counting varibales
    int i;
    int j;
    int k;
    int m;

    // nested forloop(s) needed in order to build the spaces before the pyramid + pyramid itself
    for (i = 1; i < n + 1; i++)
    {
        for (j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("  ");

        for (m = 0; m < i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// function to get user to input a valid int, then takes in a paramater of type string I've named "prompt", this takes in the "Height" the user entered as a string on line 12
int get_pyramid(string prompt)
{
    int n;

    do
    {
        n = get_int("%s", prompt);
    }
    while (n > 8 || n < 1);
    return n;
}
