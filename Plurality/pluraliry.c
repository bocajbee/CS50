#include <cs50.h>
#include <stdio.h>
#include <string.h>

// https://cs50.harvard.edu/x/2020/psets/3/plurality/

// max number of candidates
#define MAX 9

// struct consisting of a candidates name and their # of votes
typedef struct
{
    string name;
    int votes;
}
candidate;

// 1d array of candidates
candidate candidates[MAX];

// number of candidates
int candidate_count;

// function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

     // populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // display winner of election
    print_winner();
}

// update vote totals given a new vote
bool vote(string name)
{
    // iterate through each of the candidates names in the array one by one
    for (int i = 0; i < candidate_count; i++)
    {
        // compare the strings "name" and candidate[i].name to see if they match
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// print winner of election
void print_winner(void)
{
    // int vairable to store the value of the highest amount of votes that will be collected
    int maxvote = 0;

    // loop through each of the candidates[]
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= maxvote)
        {
            maxvote = candidates[i].votes;
        }
    }

    // loop through each of the candidates[] (again)
    for (int i = 0; i < candidate_count; i++)
    {
        // if the "ith" candaidates vote count == the maxvote variable
        if (candidates[i].votes == maxvote)
        {
            printf("%s WINNER: ", candidates[i].name);
        }
    }
}
