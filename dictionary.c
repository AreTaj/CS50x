// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>   // for fscanf
#include <stdlib.h>  // for malloc
#include <string.h>  // for strlen
#include <strings.h> // for strcasecmp

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 46; // Reduced collisions in the case of upper and lowercase letters

// Hash table
node *table[N];

// Declare variables to be initialized later
unsigned int hash_value;
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Return false if word is null
    if (word == NULL)
    {
        return false;
    }
    hash_value = hash(word);
    // Makes cursor node that points to the head of the hash table
    node *cursor = table[hash_value];
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number (hash value).
// Considers upper and lower letters, numbers/digits, and hopefully reduces collsions for faster dictionary lookups.
unsigned int hash(const char *word)
{
    unsigned long total = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalnum(word[i])) {  // Check for alphanumeric characters
            total += tolower(word[i]);  // Convert to lowercase for consistency
        }
    }
    return total % N;   // Calculate final hash value
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Read each word in the file and add each word to the hash table
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
        // Error handling
        if (ferror(file))
        {
            fclose(file);
            return false;
        }
    }

    // Close the dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
