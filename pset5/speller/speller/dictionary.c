/****
 * @author: William Bernal
 * @date: October 07, 2021
 * @email: bern0295@algonquinlive.com
 * @program: dictionary.c
 * @aim:  Implements a dictionary's functionality
 **** */
 
// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];


// Hashes word to a number
/*
 * djb2 hash function
 * "Written by Daniel J. Bernstein (also known as djb),
 * this simple hash function dates back to 1991"
 * source: https://theartincode.stanis.me/008-djb2/
 * visited: 2021-10-11
*/
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;  /* hash * 33 + c*/
    }

    return hash % N;
}

//Variable to keep the hash code retourned from the hash function
unsigned int hash_code = 0;

//number of words in dictionary
unsigned int count_dict_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_code = hash(word);
    node *nde_table = table[hash_code];

    while (nde_table != NULL)
    {
        if (strcasecmp(nde_table->word, word) == 0)
        {
            return true;
        }
        nde_table = nde_table->next;
    }

    // TODO
    return false;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char term[LENGTH + 1];
    FILE *dicFile = fopen(dictionary, "r");

    if (dicFile == NULL)
    {
        return false;
    }
    else
    {
        fscanf(dicFile, "%s", term);
        do
        {
            node *nde = malloc(sizeof(node));

            if (nde != NULL)
            {
                hash_code = hash(term);
                strcpy(nde->word, term);
                nde->next = table[hash_code];
                table[hash_code] = nde;
                count_dict_words ++;
            }
        }
        while (fscanf(dicFile, "%s", term) != EOF);

        fclose(dicFile);
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_dict_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    unsigned int i = 0;
    i = N;

    do
    {
        node *nde_table = table[N - i];

        while (nde_table)
        {
            node *nde2 = nde_table;
            nde_table = nde_table->next;
            free(nde2);
        }

        i--;

        if (i == 1 && nde_table == NULL)
        {
            return true;
        }

    }
    while (i > 0);

    return false;
}
