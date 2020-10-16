from cs50 import get_int


while True:
    number = get_int("Enter how tall you want your pryamid? ")
    if number >= 1 and number <= 8:
        break

blocks = -1
for level in range(number+1):
    for spaces in range(number - level ):
        print(" ", end="")
        spaces += 1
        
    for blocks in range(level):
        print("#", end="")
        blocks+= 1
        
    print()    
        
        
        