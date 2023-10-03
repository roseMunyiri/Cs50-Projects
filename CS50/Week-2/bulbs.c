#include <cs50.h>
#include <stdio.h>
#include <string.h>


const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    //prompt the user for a message
    char message[1000];
    int i = 0;
    char rem[100];
    int binary;
    int array[BITS_IN_BYTE];

    string input = get_string("Enter your text: ");
    strcpy(message, input);

    //convert each character in the string to an integer
    for(i = 0; i < strlen(message); i++)
    {
        int ASCII  = (int) message[i];

        for(int j = 0;  j < BITS_IN_BYTE; j++)
        {
           int quotient = ASCII / 2;
           int remainder = ASCII % 2;
           ASCII = quotient;// the quotient becomes the new ASCII to start the process all over again
           array[j] = remainder;//creates an array to store the bits
        }
        for(int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
           print_bulb(array[j]);
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
