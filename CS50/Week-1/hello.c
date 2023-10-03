#include <stdio.h>
/*a program that prompts the user for a name and prints hello, name*/
int main (void)
{
    char name[8];

    printf("what is your name?: ");

    scanf("%s", name);

    printf("hello, %s\n", name);
}