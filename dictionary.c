// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define XXH_INLINE_ALL
#include "xxHash-dev/xxhash.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 70000;
//143091

//key for hashing
const unsigned int key = 111;

unsigned int hash_number;

unsigned int word_count;

//Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    
    node *cursor = table[index];
    
    
    if(cursor == NULL)
    {
        return false;
    }
    
    
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        
        cursor = cursor->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char new_word[50];
    
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        new_word[i] = toupper(word[i]);
        
    }
    
    int standard = atoi(new_word);
    int *standardp = &standard;
    
    int length = sizeof(char)*(strlen(word));
    XXH64_hash_t hashed_key = XXH64(new_word, length, key);
    return hashed_key % N;
    
    
    // Hashes word to a number
    
    //unsigned long hash = 5381;
    //int c;
    //while ((c = toupper(*word++)))
    //{
    //    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    //}
    //return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    
    FILE *dict = fopen(dictionary, "r");
    
    if(dict == NULL)
    {
        return false;
    }
    
    char word[LENGTH + 1];
    

    while(fscanf(dict, "%s", word) != EOF)
    {
        
        node *new_node = calloc(1, sizeof(node));
        
        if(new_node == NULL)
        {
            return 1;
        }
        
        //set next pointer of new pointer to NULL, and copy current word into node
        strcpy(new_node->word, word);
        
        //call hash function and assign it into 
        hash_number = hash(word);
        
        
        //allocate memory for first node if it does not exist
        //if(table[hash_number] == NULL)
        //{
        //    table[hash_number] = calloc(1, sizeof(node));
        //    
        //    //check if memory allocation is successful, unload otherwise
        //    if(table[hash_number] == NULL)
        //    {
        //        fclose(dict);
        //        unload();
        //       return 1;
        //    }
        //    
        //}
        
        
        
        
        
        //point head pointer to start of hash table
        //node *head = table[hash_number];
        
        
        //collision - whilst the first node is not empty, connect new node to first to linked list

            //point new_node->next to what table is pointing at
            new_node->next = table[hash_number];
            
            table[hash_number] = new_node;
            
            word_count++;
            
            
    }
        
    
    //close dictionary
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    else
    
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //unload hash table
    for (int i = 0; i < N; i++)
    {
        //point cursor to start of list
        node *cursor = table[i];
    
        while(cursor)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
                
            //node *tmp = cursor;
            //free(tmp);
            //cursor = cursor->next;
        }
        
        if(i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
   
   
   return false;
}
