#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// https://cs50.harvard.edu/x/2020/psets/2/caesar/

// function prototype
int cipher(string c, int k);

int main(int argc, string argv[])
{
    // declare the cipherkey value int
    int cipherkeyvalue;

    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Invalid input, please enter ./caesar key lengh:\n");
        return 1;
    }
    // get ceasar KEY value typed at command line & convert into a int
    cipherkeyvalue = atoi(argv[1]);

    // get plaintext from the user + pass in input + cipherkey into cipher()
    string input = "";
    do
    {
        input = get_string("Please enter word to encrypt: ");
    }
    while (strlen(input) == 0);
    cipher(input, cipherkeyvalue);
}

// int c = "input" from main = string the user entered to encrypt, int k = keylen
int cipher(string c, int k)
{
    int n = strlen(c);
    // print out cipher
    printf("ciphertext: ");
    // iterate through plain text letter by letter in forloop
    for (int i = 0; i < n; i++)
    {
        /**
        * https://www.rapidtables.com/code/text/ascii-table.html.
        * verify range of chars is between 'a' (97) and 'z' (122)
        * ensures on the [i]th iteration of (c) in the loop that the char 'a' value of 97 is subtracted
        * key value (k) is added. modulo original ascii value + k by 26 (alphabet len). add remainder. then add 97 to equalize ascii offset
        * this is all explained in your OneNote docco why
        */
        if (c[i] >= 'a' && c[i] <= 'z')
        {
            printf("%c", (((c[i] - 97) + k) % 26) + 97);
        }
        // same deal as above, just for caps but offset 'A' (65)
        else if (c[i] >= 'A' && c[i] <= 'Z')
        {
            printf("%c", (((c[i] - 65) + k) % 26) + 65);
        }
        else
        {
            printf("%c", c[i]);
        }
    }
    printf("\n");
    return 0;
}
