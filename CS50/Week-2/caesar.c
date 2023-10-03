#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char*rotate(int key, char*plaintext, char*ciphertext);
int main(int argc, string argv[])
{
    char ciphertext[1000] = {0};
    char plaintext[1000];

    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
//check if the string has a digit
    for(int i = 0; i < strlen(argv[1]); i++)
    {
       if(!isdigit(argv[1][i]))
       {
        printf("Usage: %s key\n", argv[0]);
        return 0;
       }

    }
//convert the string to an integer
    int key = atoi(argv[1]);
    if(key < 0)
    {
        return 1;
    }

//copy input to plaintext(char*-reads blanks and symbols)
    printf("plaintext: ");
    string input = get_string("");
    strcpy(plaintext, input);

    printf("ciphertext: %s\n", rotate(key, plaintext, ciphertext));
}
char*rotate(int key, char*plaintext, char*ciphertext)
{
    for(int i = 0; i < strlen(plaintext); i++)
    {
        //check the case, convert to integer position, then convert back to letter
        if(isupper(plaintext[i]))
        {
            ciphertext[i] = (((plaintext[i]) - 'A' + key) % 26 + 'A');
        }
        else if(islower(plaintext[i]))
        {
            ciphertext[i] = (((plaintext[i]) - 'a' + key) % 26 + 'a');
        }

        else
        {
            ciphertext[i] = plaintext [i];
        }
    }
    return ciphertext;
}