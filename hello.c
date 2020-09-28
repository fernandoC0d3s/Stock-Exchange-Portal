#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //Asks user for input of name
    string name = get_string("What is your name?\n");
    //takes input and says hello based on input
    printf("Hello world %s", name);

}