//Idris Sylvester
//pset 5
//Dictionary.c
/**
 * Implements a dictionary's functionality.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"
char entry[LENGTH+1];
//define node structure
typedef struct node
{
    char *entry;
    struct node *next;
}
node;
//determine how many words were taken from dictionary
int numberofwords=0;

//create hashtable
node *hashtable[2000000];
//Implement hashfunction from Dan Bernstein.
int hashfunction( const char *entry)
{
    int hash = 0;
    int c;

    while ((c = *entry++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    hash=hash%2000000;
    return hash;
}
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //open dictionary
    FILE *words=fopen(dictionary, "r");
    //check if dictionary is null
    if(words==NULL)
    {
    fclose(words);
    return false;
    }
    //go through dictionary
    while(fscanf(words,"%s",entry)!=EOF)
    {
        //create new node
        node *newentry=malloc(sizeof(node));
        //check to see if node is null
        if(newentry==NULL)
        {
            return false;
        }
        //create pointer
        newentry->entry=malloc(strlen(entry)+1);
        //give word a pointer
        strcpy(newentry->entry,entry);
        //put word through hashfunction
        int hashnumber=hashfunction(entry);
        //if word is first in hashtable bucket put first
        if(hashtable[hashnumber]==NULL)
        {
            hashtable[hashnumber]=newentry;
            newentry->next=NULL;
        }
        //if not put it after
        else
        {
            newentry->next=hashtable[hashnumber];
            hashtable[hashnumber]=newentry;
        }
       
         numberofwords++;
    }
    fclose(words);
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *entry)
{
    //search through dictionary
    node *search=malloc(sizeof(node));
    //find section where word is supposed to be 
    int section=hashfunction(entry);
    //find out if word is in hashtable
    search=hashtable[section];
    while(search!=NULL)
    {   if (strcasecmp(search->entry, entry)==0)
        {
        return true;
        }
        search=search->next;
    }
    
    return false;
    
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int size(void)
{
    return numberofwords;
}
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //iterate through hashtable
    for (int i=0; 2000000; i++) 
    {
        //create a pointer for deleating lists
        node *deleter=hashtable[i];
        //iterate through list until at end
        while(deleter!=NULL)
        {
            //detete each element one by one in linked list
            node *tmp=deleter;
            deleter=deleter->next;
            free(tmp);
            return true;
        }
    
    }
    return false;
}
