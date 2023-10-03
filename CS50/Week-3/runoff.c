#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
void swap(candidate *a, candidate *b);

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

    if(voter < 0 || voter >= voter_count || rank < 0 || rank >= candidate_count)
    {
        return false;
    }

    // Make sure the name entered matches the candidate name
    int i = 0;
    for(i = 0; i < candidate_count; i++)
    {
        if(strcasecmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int i = 0;
    int j = 0;
    // Reset votes to 0
    for(i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    for(i = 0; i < voter_count; i++)
    {
        for(j = 0; j < candidate_count; j++)
        {
            int candidate_rank = preferences[i][j];

            // If candidate is not eliminated, increment vote count
            if (!candidates[candidate_rank].eliminated)
            {
                candidates[candidate_rank].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Check if candidate has more than half of the votes
    int i = 0;
    for(i = 0; i < candidate_count; i++)
    {
        // Calculate more than half of the voters
        int more_votes = ((voter_count / 2) + 1);
        if(candidates[i].votes >= more_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
    }

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int i = 0;
    // Assume the first candidate has the lowest votes
    int min_votes = candidates[0].votes;

    for(i = 1; i < candidate_count; i++)
    {
        // Skip eliminated candidates and check if the rest of the candidates have lower votes than the first
        if(!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int i = 0;
    for(i = 0; i < candidate_count; i++)
    {
        // Skip eliminated candidates and check checks if all other candidates have the same votes
        if(!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    // Returns true if they all have matching votes
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    int i = 0;
    int j = 0;


    for(i = 0; i < candidate_count; i++)
    {
        // Skip already eliminated candidates and check if the candidate's votes match the least votes
        if(!candidates[i].eliminated && candidates[i].votes == min)
        {

            candidates[i].eliminated = true;
            candidate_count--;
        }
    }

    // Shift all the elements after the candidate with the least amount of votes one index to the left
    for(j = i; j < candidate_count; j++)
    {
        if(candidates[i].eliminated)
        {
            for(j = i; j < candidate_count-1; j++)
            {
                candidates[j] = candidates[j+1];
            }
            // Reduce i to place the new first candidate at the new first position
            i--;
        }
    }
    return;
}



