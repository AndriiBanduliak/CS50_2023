#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Prompt user for text input
    string text = get_string("Text: ");

    // Count number of letters, words, and sentences
    int letters = 0;
    int words = 1;
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calculate average number of letters and sentences per 100 words
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // Calculate Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print reading level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
