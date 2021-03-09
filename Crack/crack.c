#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <crypt.h>

// https://docs.cs50.net/2017/ap/problems/crack/crack.html

/** https://cs50.stackexchange.com/questions/24856/pset2-crack-vs-pointers
   easy passwords for testing:
 
   aaaaa:50XcgR31jl/4M
   
   from problem set docs:
 
   Z = 50R.6FuTGui8U
   anushree:50xcIMJ0y.RXo = YES
   brian:50mjprEcqC/ts = CA
   bjbrown:50GApilQSG3E2 = UPenn (takes a while)
   lloyd:50n0AAUD.pL8g = lloyd (takes a while)
   malan:50CcfIk1QrPr6 = maybe (takes a while)
   maria:509nVI8B9VfuA = TF
   natmelo:50JIIyhDORqMU = nope
   rob:50JGnXUgaafgc = ROFL
   stelios:51u8F0dkeDSbY = NO
   zamyla:50cI2vYkF0YU2 = LOL **/

// declaring char *argv[] here is telling the function to expect a char type input & a its gonna be a pointer to an array of characters (remember how these work?)
int main(int argc, char *argv[])
{
    // prevent the user from not entering the correct number of command line arguments
    if (argc != 2)
    {
        printf("Invalid Hash Needed!:\n ");
        return 1;
    }
    // pointer called "user_input" thats expecting to be pointed to an array of chars inputted at arg1
    char *user_input = argv[1];

    // array of size 3 storing each of the two chars of the salt (user input at [0], user input at [1]) & the null terminator + an array of size FIVE that will store our guesses spat out (X to XXXX)
    char salt[3] = {user_input[0], user_input[1], '\0'};
    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char guess[5];

    // check your onenote for how these forloops work. This loops through 1 char (a-Z)
    for (int i = 0; i < strlen(alphabet); i++)
    {
        guess[0] = alphabet[i];
        guess[1] = '\0';

        // compare the plaintext guess + salt & the hash in argv[1] with strcmp() AFTER it's encrypted into a hash with crypt(). if they match...
        if (strcmp(crypt(guess, salt), argv[1]) == 0)
        {
            printf("Password: %s\n", guess);
            return 0;
        }
    }

    // check onenote for how these nested forloops work. This loops through 2 chars (a-ZZ)
    for (int i = 0; i < strlen(alphabet); i++)
    {
        guess[0] = alphabet[i];
        for (int j = 0; j < strlen(alphabet); j++)
        {
            guess[1] = alphabet[j];
            guess[2] = '\0';

            // compare the plaintext guess + salt & the hash in argv[1] with strcmp() AFTER it's encrypted into a hash with crypt(). if they match...
            if (strcmp(crypt(guess, salt), argv[1]) == 0)
            {
                printf("Password: %s\n", guess);
                return 0;
            }
        }
    }

    // check onenote for how thes enested forloops work. This loops through 3 chars (a-ZZZ)
    for (int i = 0; i < strlen(alphabet); i++)
    {
        guess[0] = alphabet[i];
        for (int j = 0; j < strlen(alphabet); j++)
        {
            guess[1] = alphabet[j];
            for (int k = 0; k < strlen(alphabet); k++)
            {
                guess[2] = alphabet[k];
                guess[3] = '\0';

                // compare the plaintext guess + salt & the hash in argv[1] with strcmp() AFTER it's encrypted into a hash with crypt(). if they match..
                if (strcmp(crypt(guess, salt), argv[1]) == 0)
                {
                    printf("Password: %s\n", guess);
                    return 0;
                }
            }
        }
    }

    // check onenote for how these nested forloops work. This loops through 4 chars (a-ZZZZ)
    for (int i = 0; i < strlen(alphabet); i++)
    {
        guess[0] = alphabet[i];
        for (int j = 0; j < strlen(alphabet); j++)
        {
            guess[1] = alphabet[j];
            for (int k = 0; k < strlen(alphabet); k++)
            {
                guess[2] = alphabet[k];
                for (int l = 0; l < strlen(alphabet); l++)
                {
                    guess[3] = alphabet[l];
                    guess[4] = '\0';

                    // compare the plaintext guess + salt & the hash in argv[1] with strcmp() AFTER it's encrypted into a hash with crypt(). if they match..
                    if (strcmp(crypt(guess, salt), argv[1]) == 0)
                    {
                        printf("Password: %s\n", guess);
                        return 0;
                    }
                }
            }
        }
    }
    printf("\n");
}
