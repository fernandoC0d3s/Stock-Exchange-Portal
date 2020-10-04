#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
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

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    
    }
    // TODO //check if the candidate has chosen the correct candiddate
    return false;
}

// Tabulate votes for non-eliminated candidates //here whe check with an if statement if the candidate is eliminated or not we continue to the next I
void tabulate(void)
{
     //sort of a repetive thatsays until vote not casted go to next preference but keeping in mind if they are all elimninated dont count sorr
     
     for (int voter = 0; voter < voter_count; voter++)
     {
        for (int preference = 0; preference < candidate_count; preference++)
        {
            int candidateNumber = preferences[voter][preference];
            if(candidates[candidateNumber].eliminated == false)
            {
                candidates[candidateNumber].votes++;
                break;
            }
                
        }
       
     
            
       
     }
    //return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int totalVotes = round(voter_count / 2);
    int winners =0;
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > totalVotes && candidates[i].eliminated == false)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
        
    }
    return false;
            
}

// Return the minimum number of votes any remaining candidate has //chek through all candidates votes return that quantity
int find_min(void)
{
    // TODO
    int min = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes <= min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int equals = 0;
    int candidateCountT = 0;
    // TODO /.just do the same as with the min
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidateCountT++;
            if(candidates[i].votes == min)
            {
                equals++;
            }
            if (equals > candidateCountT)
            {
                return true;
            }
            
            return false;
            
            
        }
        return false;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO    if min ==, that then change to preference
    //return;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
}
