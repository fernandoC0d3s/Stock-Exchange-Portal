// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
// initialise positive hash value using unsigned int 
unsigned int hash_value;
// initialise (positive) hash table word count 
unsigned int word_count;


// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    
    
    int key = hash(word);
    node* ptr = table[key];
    
    while (ptr != NULL)
    {
        if (strcasecmp(ptr -> word, word) ==0)
        {
            return true;
        }
        
        ptr = ptr -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}    

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //open dictiorary file
    FILE* file = fopen(dictionary, "r");
    //always check if it was sucessfull
    if(file == NULL)
    {
        printf("Could not open file %s",dictionary);
        return false;
    }    
    
    for(int i =0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    char tempWord[LENGTH +1]; //size of word basically
    
    while (fscanf(file,"%s\n", tempWord) != EOF)
    {
       node *t = malloc(sizeof(node)); // allocates memory of node
       
    
       strcpy(t -> word,tempWord);
       
       int hashValue = hash(tempWord);
       
       
       if(table[hashValue] == NULL)
       {
            t ->next = NULL;
            table[hashValue] = t;

       }
       else
       {
            t -> next = table[hashValue];
            table[hashValue] = t;
       }
       
       
       word_count++;
      
      
      
        
    }
     fclose(file);
     return true;
    
    
    //read strings from file one at a time
    //fscanf(reads the the scan )
    
    //while loop until fscanf == eof 
    
    //f(scanf(file, %s, word))
    
    
    //create a new node for each word
    
    //malloc check if null after 
    
    //hash word to obtain a hash value
    
    //node *list == malloc(sizeofNode(list))
    //
    
    //insert node into hash at the location
    //allocates memory
    //node*n = malloc(sizeof(node));
    //strcopy(n->word, "hello");
    // n-> next =null;
    //to insert to list(n -> next = list)
    // list =n
    
    
    
   
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODo
    // Check if there are any words
    return word_count;
    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    
   for(int i = 0;  i < N; i++)
   {
       node* nodePtr = table[i]; /// temporary node to table head
       while (nodePtr != NULL) // i am in linked ist of hash possible value
       {
         node* temp = nodePtr;    /// 
         nodePtr = nodePtr -> next;  // node leading to theend
         free(temp);
        
       }
       table[i] = NULL;
   }
    
    
    
    return false;
}
