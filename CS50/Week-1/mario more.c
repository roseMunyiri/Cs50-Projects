#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, rows, columns, spaces;
    do
    {
        printf("enter height: ");
        scanf("%i", &height);
    }
    while(height >8 || height < 1);
    //for each row//

    for (rows=0; rows <  height ; rows++)
    {
        // print spaces before the hashes to make a left-aligned pyramid//
        for(spaces=0; spaces < height-rows-1; spaces++)
        {
            printf(" ");
        }
        //for each column increase the columns as long as they are less than rows//
        for(columns=0; columns<= rows; columns++)
            {
                 printf("#");
            }
            // print two spaces to separate the right-aligned and left-aligned pyramids//
            printf("  ");
            //rows are already accounted for in the FOR loop, so just print columns//
            for(columns=0; columns<= rows; columns++)
            {
                printf("#");
            }

            printf("\n");
     }
}



