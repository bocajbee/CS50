#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

// https://cs50.harvard.edu/x/2020/psets/2/readability/
// https://cs50.stackexchange.com/questions/35010/pset2-readabilty-why-are-my-grade-levels-calculating-incorrectly

int main(void)
{
    string article = "";
    do
    {
        article = get_string("Please write an article: \n");
    }
    while (strlen(article) == 0);

    // counting variables
    float letter = 0;
    float word = 0;
    float sentence = 0;

    for (int i = 0, n = strlen(article); i < n; i++)
    {
        // count the number of letters in article
        if (isalnum(article[i]))
        {
            letter++;
        }

        // count the number of words in the article
        if (isspace(article[i]) || article[i - 1] == '\0' || article[i] == '\n')
        {
            word++;
        }

        // count the number of sentances in the article
        if ((article[i] == '!' || article[i] == '.' || article[i] == '?') && isalnum(article[i - 1]))
        {
            sentence++;
        }
    }

    // calculate Coleman-Liau index. This is: grade = 0.0588 * (Letters per 100 words) - 0.296 * (Sentences per 100 words) - 15.8
    float grade = 0.0588 * (100 * letter / word) - 0.296 * (100 * sentence / word) - 15.8;

    //  Print result: Your reading score is
    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade < 16)
    {
        printf("Grade %d\n", (int) round(grade));
    }
    else
    {
        printf("Grade 16+\n");
    }
}
