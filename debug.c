#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask for your name and where you live
    string name = get_string("What is your name? ");
    string location = get_string("Where do you live? ");

    // Say hello
    printf("Hello, %s, from %s!\n", name, location);

    return 0;
}
