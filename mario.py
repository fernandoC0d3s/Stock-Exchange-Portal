from cs50 import get_int

number = get_int("Enter how tall you want your pryamid")

blocks = -1
level=1
    
    
    
for level in range(number):
    for spaces in range(number - level -1):
        print(" ", end="")
        spaces += 1
        
    for blocks in range(level):
        print("#", end="")
        blocks+= 1
        
    print()    
        
        
        