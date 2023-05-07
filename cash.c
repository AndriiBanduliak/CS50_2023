#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    int cents = get_cents();
    int coins = calculate_quarters(cents) + calculate_dimes(cents) + calculate_nickels(cents) + calculate_pennies(cents);
    printf("%i\n", coins);
    return 0;
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    return cents / 25;
}

int calculate_dimes(int cents)
{
    cents = cents % 25;
    return cents / 10;
}

int calculate_nickels(int cents)
{
    cents = cents % 25;
    cents = cents % 10;
    return cents / 5;
}

int calculate_pennies(int cents)
{
    cents = cents % 25;
    cents = cents % 10;
    cents = cents % 5;
    return cents;
}
