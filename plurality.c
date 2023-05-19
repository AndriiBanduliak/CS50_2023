#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Implement a program that runs a plurality election, per the below.

// $ ./plurality Alice Bob Charlie
// Number of voters: 4
// Vote: Alice
// Vote: Bob
// Vote: Charlie
// Vote: Alice
// Alice

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
    // vote takes a single argument, a string called name, representing the name
    // of the candidate who was voted for. If name matches one of the names of the
    // candidates in the election, then update that candidate’s vote total

    int voteCount = 0;

    bool result = false;

    for (int i = 0; i < candidate_count; i++)
    {
        // if blank name return invlaid immediately
        if (strlen(name) == 0)
        {
            result = false;
            return result;
        }
        // if candidate exists and not a extra vote update the vote total
        if (strcmp(name, candidates[i].name) == 0 && voteCount <= candidate_count)
        {
            candidates[i].votes += 1;
            voteCount += 1;
            result = true;
            return result;
        }
        else  // return invalid and don't update vote total
        {
            result = false;
        }
    }
    return result;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    // Pprint out the name of the candidate who received the most votes in the election
    // and then print a newline.
    // It is possible that the election could end in a tie if multiple candidates each
    // have the maximum number of votes. In that case, you should output the names of
    // each of the winning candidates, each on a separate line.

    int highVoteCount = 0;

    // find highest vote
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes > highVoteCount)
        {
            highVoteCount = candidates[i].votes;
        }
    }

    // print highest votes, can be a tie
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].name != 0  && candidates[i].votes != 0 && candidates[i].votes >= highVoteCount)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}