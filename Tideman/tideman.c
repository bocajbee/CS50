#include <cs50.h>
#include <stdio.h>
#include <string.h>

// https://cs50.harvard.edu/x/2020/psets/3/tideman/

// max number of candidates that can be in the election. 9
#define MAX 9

// preferences[i][j] is a 2d array to represent the number of voters who prefer candiate[i] over candidate[j], using an adjacency matrix
int preferences[MAX][MAX];

// 2d boolean array, used to keep track of the candidate graph. if locked[i][j] == TRUE, we've locked in the edge pointing from candidate "i" to candidate "j"
bool locked[MAX][MAX];

// struct used to declare each pair, which has a winner & loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// array of strings, for the candidates names, candidate[0] is the 1st candidate. candidate[1] is the 2nd candidate etc...
string candidates[MAX];
// array of the MAX amount of candidates * (MAX amount of candidates - argc) / 2, so we can fit all of the pair structs in each index of pairs[]
pair pairs[MAX * (MAX - 1) / 2];

// global variables: pair_count & candidate_count, representing the number of "pairs" & number of "candidates" in the arrays: pairs[] & candidates[]
int pair_count;
int candidate_count;

// function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // loop through & populate the candidates[] array
    for (int i = 0; i < candidate_count; i++)
    {
        // take user input for their "candidate" in argv (+1 to exclude ".\tideman") + store it in the candidate[] array
        candidates[i] = argv[i + 1];
    }

    // outer nested forloop, to go through 1 row (i) of locked[][] at a time
    for (int i = 0; i < candidate_count; i++)
    {
        // inner nested loop, to go through every column (j) of locked[][] before the outer loop executes again, to check the next row
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // set pairs_count at the start of main() to equal 0.
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    printf("\n");

    for (int i = 0; i < voter_count; i++)
    {
        // creates a seperate array of ranks[] for the voter at "i", with as many elements equal to "candidate_count". ranks[i] is this voter's ith preference
        int ranks[candidate_count];

        // inner loop to query for the current voters prefered candidates, until this matches the candidate_count. it will then store these in this voters ranks[] preferences
        for (int j = 0; j < candidate_count; j++)
        {
            // record the candidate rank for the current "voter" at "j" (+1 to make it count from voter 1 insteaf of voter 0).
            string name = get_string("Candiate prefered rank %i: ", j + 1);

            // the current value of "j" here represents the current voter being checked, the candidate "name" they picked & the current "ranks[]" 1d array for this voter. This is passed into vote()
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("Current ranks array %d %d %d:", ranks[0], ranks[1], ranks[2]);
        printf("\n");
        record_preferences(ranks);

    }
    printf("\n");
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// update ranks given a new vote. this function takes in the arguments "rank", "name", and "ranks[]"" as mentioned on line 79
bool vote(int rank, string name, int ranks[])
{
    // loop through against every potential candidate in the election
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the user's inputted "name" inpuuted on line 78 matches the current candidate in the candidates[] array looped through above. if TRUE (== 0)
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // "i" represents the index of current candidate in the candidates[] array. update the ranks[] array with the [i]th candidate index, recording this voter's current candidate preference
            return true;  // return TRUE after grabbing this ith candidate + storing it in the correct index of the ranks[] array (first candidate voter picked into ranks[0], second into ranks[1] etc)
        }
    }
    // return FALSE if the above is not met, so this vote() function is looped through again in main()
    return false;
}

// record each voter's preferences[][] by referencing their previous ranks[]
void record_preferences(int ranks[])
{
    printf("\n");
    // outer forloop to increment "i" (for the row candidate) from 0, representing the current index of the candidate rank[] we want to reference in the 2d preferences[HERE][] array accurately
    for (int i = 0; i < candidate_count; i++)
    {
        // inner forloop to increment a j counting variable (for the column candidate) from 0 to represent the current index of the candidate rank[] we want to reference in the 2d preferences[][HERE] array accurately
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                // add +1 tally mark to prefrences[i][j] in accordance to the current value of the counting variables i and j in the nested forloops, in context to the candidates in the 1d ranks[] array
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
}

// record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // outer forloop to increment a i counting variable (for the row candidate) from 0 to represent the current index of the candidate in the rows of preferences[HERE][]
    for (int i = 0; i < candidate_count; i++)
    {
        // inner forloop to increment a j counting variable (for the column candidate) from 0 to represent the current index of the candidate in the columns of preferences[][HERE]
        for (int j = 0; j < candidate_count; j++)
        {
            // if whatever is in preferences[i][j] has a greater value than in preferences[j][i] (that the candidate in preferences[i](Row) has more tally marks than the candidate in preference [j](Column)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;  // update [current index] of the pairs[] array & set the value taken from preferences[i] (column) to be the winner
                pairs[pair_count].loser = j;  // update [current index] of the pairs[] array & set the value taken from preferences[j] (row) to be the loser
                pair_count++; // update +1 count to the paircount to tally the total number of pairs counted in this program
            }
        }
    }
    return;
}

void sort_pairs(void)
{
  // this while loop is set to "true (1)" and it'll run forever until an exit condition is met
  while (1)
  {
      int swapped = 0;  // counting variable to indicate if a swap has been currently performed in the bubble sort or not. this is set to 0 at the start of this while loop every time.
      pair temp;  // declaring a temp variable to store variables we want to swap in

      // loop through entire array of pairs[]. In a bubble sort , we need to -1 off of the pair_count being checked against. Because there's nothing to compare the last element to.
      for (int i = 0; i < pair_count -1; i++)
      {
          // check if the margin difference between the candidate.winner - the candidate.loser in [i] is < the margin difference between the candidate.winner - the candidate.loser in [i + 1]
          if (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] < preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i].loser][pairs[i].winner])
          {
              temp = pairs[i];  // take the data in pairs[i] and move it inside of temp
              pairs[i] = pairs[i + 1];  // take the data in pairs[i + 1] and move it to pairs[i]
              pairs[i + 1] = temp;  // take the data we stores in temp and move it into [i +1] to complete the swap.
              swapped = 1;  // update swapped to == 1 to indicate the full swap has been coomplete
          }
      }

      // break while loop if swapped equals "false"
      if (swapped == 0)
      {
          break;
      }
  }
}

// lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // forloop through pairs[], to get the pairs with the highest strengh of victory (starting with pairs[0])
    for (int i = 0; i < pair_count; i++)
    {
         // if check_cycle returns FALSE (if no cycle will be created calling check_cycles()) for the current .winner @ pairs[i] and .loser @ pairs[i], set locked(for this)[.winner][.loser] at pairs[i] to TRUE, drawing a line;
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        printf("Locked[i][j] %s \n", locked[pairs[i].winner][pairs[i].loser] ? "true" : "false");
    }
    return;
}

 // "int start" is "pairs[i].winner" & "int end" is the "pairs[i].loser"
bool check_cycle(int start, int end)
{
    // base case, if a path already exists between the ending node and starting node
    if (locked[end][start] == true)
    {
        return true; // return "true", indacating a edge exists between this starting node (candidate) and ending node (candidate)
    }

    // recursive case, that will track if an edge exists between any two nodes, & plot new startinh nodes, to see if a backedge exists between any 2 nodes in the graph
    // loop through all possible candidates[] in the graph
    for (int i = 0; i < candidate_count; i++)
    {
        // if a path already exists between the ending node at [i] and the orignal starting node
        if ((locked[i][start]) == true)
        {
            // pass in the ending node at [i] as the new starting node + check if a path already exists between it & the original ending node
            if (check_cycle(i, end) == true)
            {
                return true;
            }
        }
    }
    // else return FALSE if no edges can be found betweeb the two nodes
    return false;
 }

// print the winner of the election
void print_winner(void)
{
    bool winner;

    // nested outer loop, through all rows in locked[i][], checking for candidate [i]
    for (int i = 0; i < candidate_count; i++)
    {
        // set winner to TRUE on each passthrough of this loop
        winner = true;

        // nested inner loop, through all of the columns in locked[][] for candidate [j] with this inner nested loop
        for (int j = 0; j < candidate_count; j++)
        {
            // if at anyt point when looping through the columns of candidates in [j], if we find any candidate at j with an arrow pointing ot them from a candidate at [i]
            if (locked[j][i] == true)
            {
                winner = false;
            }
        }
        // if after looping through the entire locked[][] 2d array column by column, every index in locked [j][i] was set to "false"
        // determining candidate[j] has NO other candidates with an arrow pointing torwards them, winner is set to true
        if (winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
