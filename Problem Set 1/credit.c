#include <stdio.h>
#include <stdbool.h>

long getLong(void)
{
    long number;
    do
    {
        printf("Number: ");
        scanf("%ld", &number);
    } while (number < 0);

    return number;
}

bool luhnsAlgorithm(long number)
{
    int sum = 0;
    bool doubleDigit = false;

    while (number > 0) {
        int digit = number % 10;
        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit = (digit % 10) + 1;
            }
        }
        sum += digit;
        doubleDigit = !doubleDigit;
        number /= 10;
    }

    return (sum % 10) == 0;
}

void checkCardType(long number)
{
    int length = 0;
    long startDigits = number;

    while (startDigits >= 100) {
        startDigits /= 10;
        length++;
    }
    length += 2;

    if (length == 15 && (startDigits == 34 || startDigits == 37)) {
        printf("AMEX\n");
    }
    else if (length == 16 && (startDigits >= 51 && startDigits <= 55)) {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (startDigits / 10 == 4)) {
        printf("VISA\n");
    }
    else {
        printf("INVALID\n");
    }
}

int main(void)
{
    long number = getLong();
    if (luhnsAlgorithm(number)) {
        checkCardType(number);
    }
    else {
        printf("INVALID\n");
    }
}