#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// global variables
char word[9];
char guess[9];
int guesses;
int wordsize;
int wordlist[LISTSIZE][9];
int wordcount;

// function prototypes
void load_words(void);
void generate_word(void);
void print_word(char [], int, int []);
int check_guess(char []);
bool is_valid_guess(char []);
void print_score(int [], int);

int main(int argc, string argv[])
{
    // check command-line argument
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    wordsize = atoi(argv[1]);

    if (wordsize < 5 || wordsize > 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // load words into memory
    load_words();

    // generate a random word of the chosen size
    generate_word();

    // print welcome message
    printf("This is WORDLE%d\n", wordsize);
    printf("You have 6 tries to guess the %d-letter word I'm thinking of\n", wordsize);

    // loop until the user runs out of guesses or they guess the word
    while (guesses < 6)
    {
        // get a valid guess from the user
        do
        {
            printf("Input a %d-letter word: ", wordsize);
            fgets(guess, sizeof(guess), stdin);
        }
        while (!is_valid_guess(guess));

        // check the guess and print the score
        int score[9] = { WRONG, WRONG, WRONG, WRONG, WRONG, WRONG, WRONG, WRONG };
        if (check_guess(score))
        {
            printf("Congratulations! You guessed the word in %d tries!\n", guesses);
            return 0;
        }
        else
        {
            print_score(score, wordsize);
        }

        guesses++;
    }

    printf("Sorry, you ran out of guesses. The word was %s\n", word);

    return 0;
}
