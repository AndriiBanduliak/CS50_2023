#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the key from string to int
    int k = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Iterate over each character of the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // If character is uppercase
        if (isupper(plaintext[i]))
        {
            // Apply the Caesar cipher formula
            printf("%c", ((plaintext[i] - 'A') + k) % 26 + 'A');
        }
        // If character is lowercase
        else if (islower(plaintext[i]))
        {
            // Apply the Caesar cipher formula
            printf("%c", ((plaintext[i] - 'a') + k) % 26 + 'a');
        }
        // If character is not a letter
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");

    return 0;
}
