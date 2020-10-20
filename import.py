from sys import exit,argv
from cs50 import SQL
import csv

def cutNames(full_name):
    names = full_name.split()
    if len(names) >= 3:
        return names
    else:
        return[names[0],None, names[1]]
        



if len(argv) != 2:
    print("Did not use correct number of arguments")
    exit(1)


db = SQL("sqlite:///students.db")

csv_path = argv[1]
with open(csv_path) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        names = cutNames(row["name"])
        db.execute("INSERT INTO students(first,middle,last,house,birth) VALUES(?,?,?,?,?)"), names[0], names[1], names[2],row["house"],row["birth"]