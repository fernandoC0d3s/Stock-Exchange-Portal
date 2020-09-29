#include <stdio.h>
#include <cs50.h>
#include <math.h> 

int main(void)
{
    float change;
    do
    {
        change = get_float ("Change owed: ");
    }while (change < 0.00);
     
    int cents = round (100 * change);
    int coinCount = 0;
    while(cents >= 25)
    {
        cents -= 25;
        coinCount++;
    }
    while(cents >= 10)
    {
        cents = cents - 10;
        coinCount++;
    }
    while(cents >= 5)
    {
        cents = cents - 5;
        coinCount++;
    }
    while(cents >= 1)
    {
        cents = cents - 1;
        coinCount++;
    }
    
    printf("Change %i", coinCount);
}