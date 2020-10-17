from sys import argv, exit
import csv
from cs50 import get_string

def get_max(s, sub):
    
    ans= [0] * len(s)
    for i in range(len(s) - len(sub), -1, -1):
        if s[i: i+ len(sub)] == sub:
            if i + len(sub) > len(s) -1:
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]
    return max(ans)
    
def match(reader,actual):
    for line in reader:
        person = line[0]
        values = [int(value)for value in line[1:]]
        if values == actual:
            print(person)
            return
    
    print("No match")
    
    

def main():
    
    if len(argv) != 3:
        print("Not enough arguments")
        exit(1)
        
    csv_path = argv[1]
    with open(csv_path) as csv_file:
        reader = csv.reader(csv_file)
        
        allSequences= next(reader)[1:]
        
        txt_path = argv[2]
        with open(txt_path) as txt_file:
            s = txt_file.read()
            actual = [get_max(s,seq) for seq in allSequences]
        
        match(reader, actual)    
       
    
        
        

main()
        
        

        
    