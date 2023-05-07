//prints a mirrored right triangle

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Enter the height:\n");  //user input from 1-8 (both inclusive)
    }
    while (height < 1 || height > 8);
    if ((height >= 1) && (height <= 8))
    {
        // for loops specifying number of spaces and hashes per line
        int i, j;
        for (i = 1; i <= height; i++)
        {
            for (j = 0; j < (height - i); j++)
            {
                printf(" ");
            }
            for (j = 1; j <= i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
        i++;
    }
    return 0;
}