#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long cardnumber;
    int firsttwo_digits;
    int firstdigit;
    int total_sum = 0;
    int digit;
    int sum_1=0;
    int sum_2=0;
    int i = 1;
    int var;

    //ask for the cardnumber if the value is less than 0
    do
    {
        printf("Enter card number: ");
        scanf("%lld", &cardnumber);
    } while (cardnumber < 0);

    // Find the second last digits, multiply by two, then add the double digits together, start loop again
    long long cardnumber2 = cardnumber;
    while (cardnumber2 > 0)
    {
        digit = (cardnumber2 % 100) / 10 * 2;
        sum_1 = sum_1 + (digit % 10) + (digit / 10);
        cardnumber2 = cardnumber2 / 100;
    }
    // find last digit , add to sum 2, divide by 100 to start loop
    cardnumber2 = cardnumber;
    while (cardnumber2 > 0)
    {
        sum_2 = sum_2 + (cardnumber2 % 10);
        cardnumber2 = cardnumber2 / 100;
    }
    total_sum = sum_1 + sum_2;

    // find if total_sum is equal to 0, then print invalid if otherwise
    if (total_sum % 10 != 0)
    {
        printf("%s\n", "INVALID");
        return 0;
    }

    // check for AMEX (15 digits)
    firsttwo_digits = cardnumber / 10000000000000;
    if (firsttwo_digits == 34 || firsttwo_digits == 37)
    {
        printf("%s\n", "AMEX");
    }

    // Check for Mastercard (16 digits)
    firsttwo_digits = (cardnumber / 100000000000000);
    if (firsttwo_digits >= 51 && firsttwo_digits <= 55)
    {
        printf("%s\n", "MASTERCARD");
        return 0;
    }

    // check for VISA (13 / 16 digits) Here, check for first digit of the 16-digit card
    firstdigit = cardnumber / 1000000000000000;
    if (firstdigit == 4)
    {
        printf("%s\n", "VISA");
        return 0;
    }

    // check for first digit of 13-digit card

    else
    {
        firstdigit = cardnumber / 1000000000000;
        if (firstdigit == 4)
        {
         printf("%s\n", "VISA");
         return 0;
        }

    }
}



