#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i, start, end, year;
    // TODO: Prompt for start size
    do
    {
            printf("enter start population: ");
            scanf("%i" , &start);
    }
    /*keep asking for the starting population while number is less than 9*/

    while(start < 9);

    // TODO: Prompt for end size

    do
    {
        printf("enter end population : ");
        scanf("%i", &end);
    }

    while (start >= end);

    // TODO: Calculate number of years until we reach threshold

    for (year=0; start < end; year++)
    {
        start=start+(start/3)-(start/4);
    }

   // TODO: Print number of years
        {
            printf("Years: %i\n", year);
        }

}




