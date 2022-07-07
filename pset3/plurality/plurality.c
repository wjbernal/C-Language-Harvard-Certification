/****
 * @author: William Bernal
 * @date: June 10, 2020
 * @email: bern0295@algonquinlive.com
 * @program: plurality.c
 * @aim:  simulate a ballot process using the simplest way to hold an election
 **** */
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //walk the candidates array to know if there is a candidate with such name
    // if so add a vote for that candidate
    // else return vote error
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // increments the number of votes for that candidate
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // array that will hold the list of winner
    // it could be just one candidate or more than one tied candidates
    string winners[MAX];
    winners[0] = candidates[0].name;
    int MaxVotes = candidates[0].votes;
    int k = 0;

    // walk through the candidates array.
    // if the next candidate has a higher vote numbers, replace its name in the winners array
    for (int i = 1; i <= candidate_count; i++)
    {

        if (MaxVotes <  candidates[i].votes)
        {
            for (int p = 0; p < MAX; p++)
            {
                winners[p] = "";
            }
            k = 0;
            MaxVotes = candidates[i].votes;
            winners[k] = candidates[i].name;
        }
        // if both candidates with higher vote number has the same quantity, both went to the winners array
        else if (MaxVotes ==  candidates[i].votes)
        {
            k++;
            winners[k] = candidates[i].name;
        }
    }

    // walk the winners array to print all of them
    for (int j = 0; j <= k; j++)
    {
        printf("%s\n", winners[j]);
    }
    return;
}

