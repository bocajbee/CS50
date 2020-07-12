#include <cs50.h>
#include <stdio.h>
#include <string.h>

// https://cs50.harvard.edu/x/2020/psets/3/runoff/

// max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// declare a 2d array preferences[i][]. The first array, preferences[i] will represent all of the preferences for the [i]th voter
// the second array, preferences[][j] will store the index of the candidate who is the [j]th preference for the [i]th voter.
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// struct called "candidate". Every candidate has a string field for their "name", an int representing the number of "votes" they currently have, and a bool value called "eliminated"
// this "eliminated" component indicates whether the candidate has been eliminated from the election. The array candidates[] will keep track of all of the candidates in the election.
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candstruct;

// 1d aray storing every candidate with our custom candstruct datatype associated with it
candstruct candidates[MAX_CANDIDATES];

// the program also has two global variables which are ints to keep track of the Numbers of "voter_count" and "candidate_count"
int voter_count;
int candidate_count;

// function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // populate array of candidates minus the program name itself (./runoff)
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // forloop to loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];  // take user input for their desired "candidate" in argv (+1 to exclude ".\runoff") + store it in the candidate[] array, with the ".name" part of the "candstruct" datatype/struct.
        candidates[i].votes = 0;  // initalize the .votes part of this "candidate" now existing in the candidate[] array to 0. (Indicate this current candiadtae has 0 votes)
        candidates[i].eliminated = false;  // initalize the .votes part of this "candidate" now existing in the candidate[] array to "false". (Indicate this current candiadtae so far has not been eliminated)
    }

    // prompt the user for how many voters there will be in this election and store this collected int value into "voter_count"
    voter_count = get_int("Number of voters: ");

    // if the voter_count entered exceeds the max amount of voters
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
    // after determining the number of candidates and the number of voters, the main voting loop begins. this loops through every voter stored in "voter_count &" gives every voter a chance to vote.
    // loop through "voter_count" &* Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // loop through every "candidate" for the current "voter". You need the inner loop so each voter can give their full list of preferences. Otherwise each person will only be able to put 1 name in
        for (int j = 0; j < candidate_count; j++)
        {
            // J + 1 is so it starts with "rank 1:" instead of "rank 0:"
            string name = get_string("Rank %i: ", j + 1);

            // record vote, unless it's invalid. As the voter enters their preferences, the vote function is called to keep track of all of the preferences.
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }
    // once all of the votes are in, this while loop begins: this keeps going to keep looping through the runoff process of checking for a winner & eliminating the last place candidate until there is a winner.
    while (true)
    {
        // calculate votes given remaining candidates
        tabulate();
        // use print_winner function to check if election has been won, then store this into a cool "won" (true or false)
        bool won = print_winner();
        // if the election has been won, break this while loop.
        if (won)
        {
            break;
        }

        // eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // if tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // eliminate anyone with minimum number of votes
        eliminate(min);

        // reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// function to record preference if vote is valid, function has 3 parameters
bool vote(int voter, int rank, string name)
{
    // loop through every voter at index [i] (voter[0], voter[1], voter[2]...)
    for (int i = 0; i < candidate_count; i++)
    {
        // using strcmp function to compare candidates.name at [i]th index to the parameter "string". if these match...
        if (strcmp(candidates[i].name, name) == 0)
        {
            // update the preferences[voter][rank] index of the 2d arary, with the value at i,  placing this candidate as a rnaked preference
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // loop through the current amount of voters in this election
    for (int i = 0; i < voter_count; i++)
    {
        // loop through the current amount of candidates in this election
        for (int j = 0; j < candidate_count; j++)
        {
            // if the current candidate being checked for the current [voter] && their [preference rank] is not eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;  // update the count for the [i]th candidate by +1, for the candidate currently being checked in [preferences[voter][rank]
                break;
            }
        }
    }
}

// print the winner of the election, if there is one
bool print_winner(void)
{
    // forloop to loop through every candidate at index [i] (candidate[0], candidate[1], candidate[2]...
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate being checked vote total is greater than the total number of voters divided by 2 (50%)
        if (candidates[i].votes > voter_count/2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // create an int called minvote and set it equal to the amount of voters in the election
    int minvote = voter_count;

    // forloop to go through the candidates names in this election one by one
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate being checked is not eliminated AND their total of votes is < than the minvote total
        if (candidates[i].eliminated == false && candidates[i].votes < minvote)
        {
            minvote = candidates[i].votes; // minvote total to now equal this candidate being checked total number of votes
        }
    }
    return minvote;
}

// return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // create custom bool called "yeet" and logically assume it's already set to true.
    bool yeet = true;

    // forloop to go through the candidates names in this election one by one
    for (int i = 0; i < candidate_count; i++)
    {
        // check IF the current candidate at [i] is not eliminated AND the candidate at [i]'s votes DO NOT EQUAL min'
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            yeet = false;
        }
    }
    return yeet;
}

// eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // forloop to go through the candidates names in this election one by one
    for (int i = 0; i < candidate_count; i++)
    {
        // check IF the current candidate at [i] is not eliminated AND the candidate at [i]'s votes DO EQUAL min
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
