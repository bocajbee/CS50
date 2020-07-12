#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// https://cs50.harvard.edu/x/2020/psets/5/speller/

// Represents a node in a hash table
typedef struct node
{
    // LENGH is defined in dictionary.h and by default is set to 45 for each node can store an array of up to 45 chars (string)
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 6240;

// Hash table, remember this is an array of pointers (each node contains a pointer to the head of each linked list at each bucket)!
node *table[N];

// global counter variable to keep track of the amount of nodes added into the linked list
int count_of_nodes = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_value = hash(word); // hash word from the users inputted text file to obtain a hash value
    node *tmp = table[hash_value]; // create a temp pointer pointing to the same index in table[] hash() returned after hashing the word

    // if the pointer at the current index of the hash table is not pointing to nothing
    if (tmp != NULL)
    {
        // every time when looping through the linked list at this index of table[], if the current node after the one tmp is sitting on isn't NULL
        while (tmp != NULL)
        {
            // compare the strings for the "word" the user is checking against in speller.c to the current word in the current node in the linked list from the dictionary. if strcasecmp() returns 0 indicating they match
            if (strcasecmp(word, tmp->word) == 0)
            {
                return true;  // confirm that these words match, and "word" in the users text file is spelled correctly.
            }
            tmp = tmp->next; // then migrate the temp pointer to the next node in the linked list
        }
    }
    return false;
}

/**
 * A case-insensitive implementation of the djb2 hash function.
 * Change NUM_BUCKETS to whatever your number of buckets is.
 * Adapted by Neel Mehta from: http://stackoverflow.com/questions/2571683/djb2-hash-function.
 */
unsigned int hash(const char* word)
{
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
       hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declare a pointer to somewhere in memory where a copied dictionary string in stored in memory will be and allocate it enough space of size LENGTH to fit a string
    char *ptr_wordmem = malloc(LENGTH + 1);
    // fopen() the dictionary file to be used, in this case, the file being pointed to by *dictionary declared in speller.c & passed into this function
    FILE *ptr_dictionary = fopen(dictionary, "r");

    // check to ensure "ptr_dictionary" is not returning a NULL value. If == NULL, the dictionary file does not exist, and will result in a seg fault.
    if (ptr_dictionary == NULL)
    {
        printf("Error, invalid dictionary used son\n!");
        return false;
    }

    // loop through each character in the string , while there are >= the LENGTH of characters, read each char from the dictionary into the memory ptr_wordmem is pointing to at a time
    while (fscanf(ptr_dictionary, "%s", ptr_wordmem) != EOF)
    {
        // malloc() "node 0" in memory + point our *n pointer to it
        node *n = malloc(sizeof(node));
        // saftey check to ensure n is not pointing to a NULL value in memory to avoid a seg fault
        if (n != NULL)
        {
            n->next = NULL;  // set the next field of the node our "*n" is currently pointing to: nothing
        }
        // copy the string in memory being pointed to by "word_in_mem" directly into n->word of this generated node
        strcpy(n->word, ptr_wordmem);
        // create an int called "bucket_index" to store our bucket number hash returns in our bucket_head int. This is also the index in the array of the hash representing each bucket
        int bucket_index = hash(n->word);

        // remember table is an array of pointers. if the pointer at the current bucket_index of table[] is not pointing to anything
        if (table[bucket_index] == NULL)
        {
            table[bucket_index] = n;  // set the current pointer at the index of the array of pointers to point to this node as the "start node" of the list, n
            n->next = NULL;  // set "n"->next to point to NULL.
            count_of_nodes++;  // update the total count of nodes in the linked list by 1
        }
        // if the pointer at the current bucket_index of table[] is pointing to a node already
        else
        {
            n->next = table[bucket_index]; //set -> next of "node n" to point to where -> next of the node the "head pointer" at the current bucket_index[] (first node) of table[] is pointing to (next node)
            table[bucket_index] = n; // now point the "head pointer" at the current bucket_index[] to this "new" "node n"
            count_of_nodes++;
        }
    }
    free(ptr_wordmem);
    fclose(ptr_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count_of_nodes;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // declare a pointer called "tep" that is anticipating to be pointed to something of type node & point it to the same place the pointer at table[i] is pointing to
        node *tmp = table[i];  
        // check if list is currently NULL, if so, the list is empty and we just return
        while (table[i] != NULL)
        {
            tmp = table[i];  // then, save the head of the linked list (table[i]) into a the tmp variable, which will be redeclared later
            table[i] = table[i]->next;  // then, set the "head" pointer to the linked list in table[i], to now be the ->next node in the linked list, table[i]->next, as the new head of the linked list that exists in table[i].
            free(tmp);  // safely free the node where the (tmp) variable is currently sitting at 1 node behind the new "head" node at table[i] now, repeat step 1
        }
    }
    return true;
}
