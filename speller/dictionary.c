// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"


// Number of buckets in hash table
#define N 25601

// Dictionary pointer
FILE *fPtr;
int word_t = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    register char lword[(LENGTH + 1)];
    strcpy(lword, word);
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lword[i] = tolower(lword[i]);
    }
    unsigned int index = hash(lword);
    int x = 0;
    node *tmp = table[index];
    while (x == 0)
    {
        register char *ldic = malloc(sizeof(tmp->word));
        strcpy(ldic, tmp->word);
        if (strcmp(lword, ldic) == 0)
        {
            free(ldic);
            return true;
        }
        if (tmp->next != NULL)
        {
            tmp = tmp->next;
            free(ldic);
        }
        else
        {
            free(ldic);
            break;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) == 1)
    {
        return 0;
    }
    else
    {
        unsigned long hash = 5381;
        int c;
        while ((c = *word++))
        {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % 25599 + 1;
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = declare("/");
    }
    fPtr = fopen(dictionary, "r");
    if (fPtr == NULL)
    {
        return false;
    }
    else
    {
        int x = 0;
        int maximum_t = sizeof(char) * (LENGTH + 2);
        while (x == 0) // Equivalent of while(true)
        {
            char *new_word = malloc(maximum_t);
            if (fgets(new_word, (LENGTH + 2), fPtr) != NULL)
            {
                word_t++;
                new_word[strlen(new_word) - 1] = '\0';
                unsigned int index = hash(new_word);
                if (strcmp(table[index]->word, "/") == 0)
                {
                    strcpy(table[index]->word, new_word);
                }
                else
                {
                    lead(&table[index], new_word);
                }
            }
            else
            {
                free(new_word);
                break;
            }
            free(new_word);
        }
        return true;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_t;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }
    int success = fclose(fPtr);
    if (success == 0)
    {
        return true;
    }
    return false;
}


/**
 * Linked list library
 */

node *declare(char *value)
{
    node *n = malloc(sizeof(node));
    strcpy(n->word, value);
    n->next = NULL;
    return n;
}

void lead(node * (*list), char *value)
{
    node *n = declare(value);
    n->next = *list;
    *list = n;
}

void free_list(node *list)
{
    node *tmp = list;
    node *del;
    int x = 0;
    while (x == 0)
    {
        del = tmp;
        if (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        else
        {
            x++;
        }
        free(del);
    }
}

