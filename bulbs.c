#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get message from user
    string message = get_string("Message: ");

    // Print out each byte in binary
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        int byte = (int) message[i];
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = (byte >> j) & 1;
            print_bulb(bit);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
