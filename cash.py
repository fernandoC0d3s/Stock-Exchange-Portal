from cs50 import get_float

while True:
    change = get_float("Change owed ")
    if change > 0.00:
        break
    
cents = round(100 * change)
coinCount  =0

while cents >=  25:
    cents -= 25
    coinCount += 1
while cents >= 10:
    cents -=10
    coinCount+=1
while cents >= 5:
    cents -= 5
    coinCount +=1
while cents >= 1:
    cents -=1
    coinCount +=1
print(f"Change {coinCount}")
    
    
    