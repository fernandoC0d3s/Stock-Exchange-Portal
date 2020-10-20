# TODO
from sys import exit,argv

from cs50 import SQL

if len(argv) != 2:
    print("incorrect bruv")
    exit(1)
    
db = SQL("sqlite:///students.db")   
entered = argv[1]


rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last,first", entered)

for row in rows:
    first, middle, last,birth = row["first"], row["middle"], row["last"], row["Year"]
    print(f"{first} {middle + ' ' if middle else ''} {last}, born {birth}")
    
