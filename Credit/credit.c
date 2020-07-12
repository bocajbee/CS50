#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

// https://cs50.harvard.edu/x/2020/psets/1/credit/

// prototypes for my functions
int c2i(char c);
int add_digits(int n);
int LuhnsAlg(string CCnumber);

// main function
int main(void)
{
    string CCnumber;
    int CCNumberLengh;

    // get user input
    do
    {
        CCnumber = get_string("Please enter a CC number: ");
        CCNumberLengh = strlen(CCnumber);
    }
    while (CCNumberLengh == 0 || c2i(CCnumber[0]) >= 9);

    // if CCNumberLengh is less than 15 characters or greater than 16 characters
    if (CCNumberLengh < 15 || CCNumberLengh > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // check starting numbers of the credit card & return VISA, AMEX or MASTERCARD
    // verify CC is American Express. All AA cards start with 34 or 37
    if ((CCNumberLengh == 15) && c2i(CCnumber[0]) == 3 && (c2i(CCnumber[1]) == 4 || c2i(CCnumber[1]) == 7))
    {
        if (LuhnsAlg(CCnumber) == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // verify CC is Mastercard. All MC's start with a 51, 52, 53, 54 or 55
    else if ((CCNumberLengh == 16) && (c2i(CCnumber[0]) == 5 || c2i(CCnumber[0]) == 2) && c2i(CCnumber[1]) >= 1 && c2i(CCnumber[1]) <= 5)
    {
        if (LuhnsAlg(CCnumber) == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // verify CC is visa. All Visa's are 13 or 16 digits long and start with the string value of '4'
    else if ((CCNumberLengh == 13 || CCNumberLengh == 16) && CCnumber[0] == '4')
    {
        if (LuhnsAlg(CCnumber) == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// function to split a number like 15 and add it as literally 1 + 5
int add_digits(int n)
{
    // how this modulus works & why its needed for luhn's also is in your OneNote doc
    int d = 0;

    while (n > 0)
    {
        d = d + n % 10;
        n = n / 10;
    }
    return d;
}

// my function to convert a character to an integer value with the ascii table
int c2i(char c)
{
    // https://www.rapidtables.com/code/text/ascii-table.html. to convert char to int you need to subtract a 48 based offset on the ascii table. return this new value for char c into main()
    return c - (int)('0');
}

// function to execute Luhn's algorith on the credit card number to check it
int LuhnsAlg(string CCnumber)
{
    // notes on how this forloop works are in OneNote doc
    int i = 0;
    int s = 0;
    int t = 0;

    // count though "even" indexes of digits in CC array while i > 0, then move over and check every second CC index
    for (i = strlen(CCnumber) - 2; i >= 0; i -= 2)
    {
        t = c2i(CCnumber[i]);
        s = s + add_digits(t * 2);
    }
    // count though "odd" indexes of digits in CC array while i > 0, then move over and check every second CC index
    for (i = strlen(CCnumber) - 1; i >= 0; i -= 2)
    {
        t = c2i(CCnumber[i]);
        s = s + t;
    }

    // if total of the last digit of this card is 0, card is valid
    if (s % 10 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
