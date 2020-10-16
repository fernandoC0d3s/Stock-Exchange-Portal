from cs50 import get_int


while True:
    number = get_int("Enter how tall you want your pryamid")
    if number < 1 or number > 8:
        break

blocks = -1
level=0
    
    
    
for level in range(number):
    for spaces in range(number - level -1):
        print(" ", end="")
        spaces += 1
        
    for blocks in range(level):
        print("#", end="")
        blocks+= 1
        
    print()    
        
        
        