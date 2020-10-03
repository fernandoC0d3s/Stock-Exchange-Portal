#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool iskeyValid(string s);
int main(int argc, string argv[])
{
    if(argc != 2 || iskeyValid(argv[1]))
    {
       printf("Usage: ./caesar key");
       return 1;
    }
    int key = atoi(argv[1]);
    string regularText = get_string("plaintext: ");
    
    int lengthOfText = strlen(regularText);
    printf("ciphertext: ");
    
    for(int i = 0; i < lengthOfText;i++)
    {
        char c = regularText[i];
        
        if(isalpha(c))
        {
            char m = 'A';
            if(islower(c))
                m = 'a';
            
            printf("%c", (c - m + key) % 26 + m);
        }
        else
            printf("%c", c);
    }
    printf("\n");
    
}
bool iskeyValid(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if(!isdigit(s[i]))
        {
            return false;
        }    
        
        
          
    }
     return true; 
}