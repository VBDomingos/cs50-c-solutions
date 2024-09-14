#include <stdio.h>

int calculateQuarters(int cents)
{
    int quarters = cents / 25;
    return quarters;
}

int calculateDimes(int cents)
{
    int dimes = cents / 10;
    return dimes;
}

int calculateNickels(int cents)
{
    int nickels = cents / 5;
    return nickels;
}

int calculatePennies(int cents)
{
    int pennies = cents;
    return pennies;
}

int main(void)
{
    int cents;
    do
    {
        printf("How many cents?\n");
        scanf("%d", &cents);
    } while (cents < 0);

    int quarters = calculateQuarters(cents);
    cents = cents - quarters * 25;
   
    int dimes = calculateDimes(cents);
    cents = cents - dimes * 10;

    int nickels = calculateNickels(cents);
    cents = cents - nickels * 5;

    int pennies = calculatePennies(cents);
    cents = cents - pennies * 1;

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);
}
