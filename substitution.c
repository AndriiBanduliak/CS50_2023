#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int main(int argc, string argv[])
{
    // Check that the user provides exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];
    int key_len = strlen(key);

    // Check that the key has exactly 26 characters
    if (key_len != ALPHABET_SIZE)
    {
        printf("Key must contain %d characters.\n", ALPHABET_SIZE);
        return 1;
    }

    // Check that the key contains only alphabetical characters
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }
    }

    // Convert the key to uppercase for consistency
    for (int i = 0; i < key_len; i++)
    {
        key[i] = toupper(key[i]);
    }

    string plaintext = get_string("plaintext: ");
    int plaintext_len = strlen(plaintext);
    printf("ciphertext: ");

    // Iterate over each character in the plaintext
    for (int i = 0; i < plaintext_len; i++)
    {
        char c = plaintext[i];

        // If the character is alphabetical, apply the substitution cipher
        if (isalpha(c))
        {
            int shift = toupper(c) - 'A';
            char sub = key[shift];

            // Preserve the case of the original character
            if (isupper(c))
            {
                printf("%c", sub);
            }
            else
            {
                printf("%c", tolower(sub));
            }
        }
        else
        {
            // Non-alphabetical characters are printed unchanged
            printf("%c", c);
        }
    }

    printf("\n");

    return 0;
}
