#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int count_letters(string text);
int count_words(string Text);
int count_sentences(string Text);
int main(void)
{
    char Text[1000];
    string input = get_string ("Text: ");
    strcpy(Text, input);


    int L = count_letters(Text);
    int W = count_words(Text);
    int S = count_sentences(Text);

    float index = 0.0588 * (100 * (float)L / (float)W) - 0.296 * (100 * (float)S / (float)W) - 15.8;
    if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if(index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }

}
int count_letters(string Text)
{
    int Letters = 0;
    int i;

    for(i = 0; i < strlen(Text); i++)
    {
        if(isalpha(Text[i]))
        {
            Letters++;
        }
    }
    return Letters;
}
int count_words(string Text)
{
    int words = 0;
    int j;
    for(j = 0; j < strlen(Text); j++)
    if(isspace(Text[j]))
    {
        words++;
    }
    return words + 1;
}
int count_sentences(string Text)
{
    int sentences = 0;
    int k;
    for(k = 0; k < strlen(Text); k++)
    {
      if(Text[k] == '!' ||Text[k] == '.' || Text[k] == '?')
      {
        sentences++;
      }
    }
    return sentences;
}
