/****
 * @author: William Bernal
 * @date: June 12, 2020
 * @email: bern0295@algonquinlive.com
 * @program: Tideman.c
 * @aim:  simulate a ballot process implementing Tideman, which is a ranked-choice voting system
 **** */
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
int checkCycle(int originalWinner, int wnr, int lsr);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //walk the candidates array to know if there is a candidate with such name
    // if so add a vote for that candidate
    // else return vote error
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // record the voter preference
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;



}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int p = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[p].winner = i;
                    pairs[p].loser = j;
                    pair_count++;
                    p++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[p].winner = j;
                    pairs[p].loser = i;
                    pair_count++;
                    p++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair aux_pairs[1];
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                aux_pairs[0].winner = pairs[i].winner;
                aux_pairs[0].loser = pairs[i].loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = aux_pairs[0].winner;
                pairs[j].loser = aux_pairs[0].loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int wnr = pairs[i].winner;
        int lsr = pairs[i].loser;
        
        //if there is a checkCycle return a zero, then the pair will be locked otherwise it won't be locked
        if (checkCycle(wnr, wnr, lsr) == 0) // No cycle, so lock the pairs winner & loser
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
    return;
}

// verify in a recursive function if there are ancestors who bet the current winner
int checkCycle(int originalWinner, int wnr, int lsr)
{
    int result = 0;

    for (int k = 0; k < candidate_count; k++)
    {

        if (locked[lsr][k])
        {
            // if k (which is the current loser) is = to the original winner
            // there is a cycle
            if (k == originalWinner)
            {
                result = 1;
            }
            else
            {
                // if the current locked pair = True, verify if the current loser have beaten the original winner before
                //if there are ancestors who bet the current winner
                if (checkCycle(originalWinner, lsr,  k) == 1)
                {
                    result = 1;

                }
            }

        }

    }
    return result;
}



// Print the winner of the election
void print_winner(void)
{
    int aux_top_Trues = 0;
    int candidate_winner = 99;
    int aux_source;

    for (int i = 0; i < candidate_count; i++)
    {
        aux_source = 0;

        // verify if a current winner in the locked matrix has another source.
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                aux_source++;
            }
        }

        // if there is not any source, so it is the winner
        if (aux_source == 0)
        {
            candidate_winner = i;
        }
    }

    // prints the winner of the election
    printf("%s\n", candidates[candidate_winner]);

    return;


}

