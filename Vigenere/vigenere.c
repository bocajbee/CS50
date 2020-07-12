#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// https://docs.cs50.net/2018/x/psets/2/vigenere/vigenere.html

// function prototypes
int cipher(string input_text, string cipher_key);
int convert_key(char index);

int main(int argc, string argv[])
{
    // prevent the user from not entering the correct number of command line arguments
    if (argc != 2)
    {
        printf("Invalid:\n ");
        return 1;
    }

    // iterate through characters in argv[1] to ensure they're letters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Please enter a valid command line argument");
            return 1;
        }
    }

    // Get plaintext from user:
    string input_text = "";
    do
    {
        printf("NOTE: Only uppercase and lowercase letters will be encoded\n");
        input_text = get_string("Please enter word to encrypt: ");
    }
    while (strlen(input_text) == 0);
    cipher(input_text, argv[1]);
}

int cipher(string input_text, string cipher_key)
{
    // declare int called cipher key then say it's EQUAL to the len of the input from cipher_key(argv[1])
    int klen = strlen(cipher_key);
    printf("ciphertext: ");

    // declare counting variables for plaintext and the key and loop through both
    for (int i = 0, j = 0; i < strlen(input_text); i++)
    {
        // verify input from argv[1] is alphabetical using isalpha function from C.
        if (isalpha(input_text[i]))
        {
            // please check your OneNote for more detail about this
            int finalKey = convert_key(cipher_key[j % klen]);

            // loop through plaintext and also declare counting variable for
            if (islower(input_text[i]))
            {
                printf("%c", (((input_text[i] - (int)('a')) + finalKey) % 26) + (int)('a'));
            }
            else if (isupper(input_text[i]))
            {
                printf("%c", (((input_text[i] - (int)('A')) + finalKey) % 26) + (int)('A'));
            }
            j++;
        }
        else
        {
            printf("%c", input_text[i]);
        }
    }
    printf("\n");
    return 0;
}

// check your onenote for how this function works
int convert_key(char index)
{
    if (islower(index))
    {
        return index - (int)('a');
    }
    else if (isupper(index))
    {
        return index - (int)('A');
    }
    else
    {
        return 1;
    }
}
