// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Define linked list library
node *declare(char *value);
void lead(node * (*list), char *value);
void free_list(node *list);

#endif // DICTIONARY_H
