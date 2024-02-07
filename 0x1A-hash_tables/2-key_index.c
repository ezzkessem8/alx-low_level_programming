#include "hash_tables.h"

/**
 * key_index - Gives you the index of a key
 * @key: The key
 * @size: The size of the array of the hash table
 * Return: The index at which the key/value pair should be stored
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    /* Use the hash_djb2 function to get the hash value */
    unsigned long int hash_value = hash_djb2(key);

    /* Calculate the index using the hash value and the size of the array */
    return (hash_value % size);
}

