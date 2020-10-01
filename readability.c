#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
#include <ctype.h>


int main(void)
{
    string prompt;
    int lengthOfPrompt = 0;
    int letterCount = 0;
    int space = 0;
    int sentence = 0;
    //We ask user until it has a prompt
    do
    {
        prompt = get_string("Enter prompt to analyze the readibility \n");
        lengthOfPrompt = strlen(prompt);
    }
    while (lengthOfPrompt <= 0);
    for (int i = 0; i < lengthOfPrompt; i++)
    {
        if (isalpha(prompt[i])) //CHECK FOR RANGES A-Z as letters are not being counted properly
        {
            letterCount++;
        }
        else if (prompt[i] == 32)
        {
            space++;                                //Spaces is accurate therefore words are
        }
        else if (prompt[i] == 33 || prompt[i] == 46 || prompt[i] == 63)
        {
            sentence++;                             //no way sentences are being counted properly as letters are a complete messs
        }

    }
    //space + 1 indicates the ability to count the words as the assumption is sentence does not end in space
    int words = space + 1;
    //we get average of both to plug into the formula after
    double averageL = 100 * ((float)letterCount / (float)words);
    float averageS = 100 * ((float) sentence / (float) words)
    
    int index = (int) round(((0.0588 * averageL) - (0.296 * averageS) - 15.8));
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    



}