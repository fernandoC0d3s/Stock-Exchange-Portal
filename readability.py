from cs50 import get_string

letterCount = 0
space =0
sentence =0

prompt = get_string("Enter prompt to analyze readability ").strip()

for i in range(len(prompt)):
    for c in prompt:
        if c.isalpha():
            letterCount+=1
        elif c == " ":
            space+=1
        elif c == '!' or c == '.' or c == '?':
            sentence+=1
    
words = space +1 
averageL =letterCount / words * 100
averageS = sentence/words * 100

index = round(0.0588 * averageL - 0.296 * averageS - 15.8)


if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
