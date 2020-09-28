#include <stdio.h>
#include <cs50.h>



int main(void)
{
    //We ask user for information of how tall we want the pyramid
    int number;
    do
    {
        number = get_int("Enter how tall your pyramid u want ");
       
    }
    while (number < 1 || number > 8);
    
    
    
    
    //for each level or floor 
    for(int level = 0; level < number; level++)
    {
        //we add spaces according to the number given by user - level as each level u need less spaces
        for(int spaces = 0; spaces < number - level - 1; spaces++)
        {
          printf(" ");
        }
        
      //for each level we print a certain amount of blocks (#)
       for(int blocks = -1; blocks < level; blocks++)
       {
           printf("#");
       }
       printf("\n");
       
    }
    
    
  
}